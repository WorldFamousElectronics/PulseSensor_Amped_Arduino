volatile int rate[61];                    // array to hold last 61 IBI values
volatile unsigned long sampleCounter = 0; // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;  // used to find IBI
volatile int P = 512;                     // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 525;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM
volatile int successiveRRDeltas[60];      // used to track differences between successive RR values
      
void interruptSetup(){     
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER 
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED      
} 


// THIS IS THE TIMER 2 INTERRUPT SERVICE ROUTINE. 
// Timer 2 makes sure that we take a reading every 2 miliseconds

ISR(TIMER2_COMPA_vect){                     // triggered when Timer2 counts to 124
  cli();                                      // disable interrupts while we do this
  Signal = analogRead(pulsePin);              // read the Pulse Sensor 
  sampleCounter += 2;                         // keep track of the time in mS with this variable
  int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

  //  find the peak and trough of the pulse wave
  if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
    if (Signal < T){                          // T is the trough
      T = Signal;                             // keep track of lowest point in pulse wave 
    }
  }

  if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
    P = Signal;                               // P is the peak
  }                                           // keep track of highest point in pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (N > 250){                                   // avoid high frequency noise
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
      Pulse = true;                               // set the Pulse flag when we think there is a pulse
      digitalWrite(blinkPin,HIGH);                // turn on pin 13 LED
      IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
      lastBeatTime = sampleCounter;               // keep track of time for next pulse

      int i;
      if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
        secondBeat = false;                  // clear secondBeat flag
        for(i=0; i<=60; i++){                // seed the running total to get a realisitic BPM at startup
          rate[i] = IBI;    
        }
        for( i=0; i<59; i++){                // seed the successiveRRDeltas array with 0s
          successiveRRDeltas[i] = 0;
        }
      }

      if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
        firstBeat = false;                   // clear firstBeat flag
        secondBeat = true;                   // set the second beat flag
        sei();                               // enable interrupts again
        return;                              // IBI value is unreliable so discard it
      }   

      for( i=0; i<=59; i++){                 // update rate array. shift data
        rate[i] = rate[i+1];                 // and drop the oldest IBI value 
      }
      rate[60] = IBI;                        // add the latest IBI in the rate array
      
      // calculate a running total of the last 10 IBI values
      word runningTotal = 0;                 // clear the runningTotal variable    
      for( i=51; i<=60; i++ )
      {
        runningTotal += rate[i];
      }
      runningTotal /= 10;                     // average the last 10 IBI values 
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
      QS = true;                              // set Quantified Self flag 
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR

      // HRV Analysis
      // https://en.wikipedia.org/wiki/Heart_rate_variability#HRV_analysis

      for( i=0; i<=58; i++){                 // update successive RR difference array. shift data
        successiveRRDeltas[i] = successiveRRDeltas[ i + 1 ];
      }
      successiveRRDeltas[59] = rate[ 60 ] - rate[ 59 ]; // set the newest RR difference as the last entry in the array
           
      RRDelta = successiveRRDeltas[59];      // store the newest RR difference
      
      // SDNN: the standard deviation of NN (RR) intervals.
      // alternate calculation method for stdDev without a second loop may be possible:
      // https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
      double tVal = 0;                     // temp utility variable to be re-used in loops
      double aveRR = 0;                    // calculate the average RR value.

      for( i=1; i<=60; i++){               // add up the last 60 RR values and divide by 60
        aveRR += rate[ i ];                // (Don't include the first entry or you'll add 61 values)
      }
      aveRR /= 60;
      
      for( i=1; i<=60; i++){               // calculate the standard devation of RR intervals
        tVal = aveRR - rate[ i ];          // using the average that was just calculated
        SDNN += tVal * tVal;
      }
      SDNN = sqrt( SDNN / 60 );

      // SDSD: standard deviation of successive differences 
      // The standard deviation of the successive differences between adjacent NNs (RRs).
      SDSD = 0;
      int aveRRDelta;
      for(int i=0; i<=59; i++)            // find the average of successive differences
      {
        aveRRDelta = successiveRRDeltas[ i ]; 
      }
      aveRRDelta /= 60;

      for(int i=0; i<=59; i++)            // calculate the standard deviation of successive differences
      {                                   // using the average that was just calculated
        tVal = aveRRDelta - successiveRRDeltas[ i ];
        SDSD += tVal * tVal;         
      }
      SDSD = sqrt( SDSD / 60 );

      // RMSSD: root mean square of successive differences
      // The square root of the mean of the squares of the successive differences between adjacent NNs (RRs).
      RMSSD = 0;

      for(int i=0; i<=59; i++)            // square each successive RR difference
      {                                   // take the sum of all the values
        tVal =  successiveRRDeltas[ i ];  // divide by the total sample size to get the mean
        RMSSD += tVal * tVal;             // and take the square root
      }
      RMSSD = sqrt( RMSSD / 60 );
      
      LN20RMSSD = 20 * log( RMSSD );      // take the natural log of RMSSD
                                          // then scale the result so the range is linear and values 
                                          // fall approximately on the scale of 0-100.      
   
      // NN50: the number of pairs of successive NNs (RRs) that differ by more than 50 ms.
      NN50 = 0;                           // add all the successive differences that are greater than 50ms
      for(int i=0; i<=59; i++)
      {
        if( abs( successiveRRDeltas[ i ] ) > 50 )
        {
          NN50 ++; 
        }
      }

      // pNN50: the proportion of NN50 divided by total number of NNs (RRs).
      PNN50 = NN50 / 60;                  // divide the total number of successive differences greater than 50s
                                          // that were found and divide by the total sample size to get the 
                                          // percent of successive differences greater than 50s.
      
    }                       
  }

  if (Signal < thresh && Pulse == true){   // when the values are going down, the beat is over
    digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
    Pulse = false;                         // reset the Pulse flag so we can do it again
    amp = P - T;                           // get amplitude of the pulse wave
    thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
    P = thresh;                            // reset these for next time
    T = thresh;
  }

  if (N > 2500){                           // if 2.5 seconds go by without a beat
    thresh = 512;                          // set thresh default
    P = 512;                               // set P default
    T = 512;                               // set T default
    lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
    firstBeat = true;                      // set these to avoid noise
    secondBeat = false;                    // when we get the heartbeat back
  }

  sei();                                   // enable interrupts when youre done!
}// end isr





