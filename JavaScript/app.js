var rate = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
      sampleCounter = 0,
      lastBeatTime = 0,
      P = 512,
      T = 512,
      thresh = 525,
      amp = 100,
      firstBeat = true,
      secondBeat = false,
      IBI = 600,
      Pulse = false,
      BPM,
      Signal,
      QS = false;

var five = require('johnny-five'),
      board, sensor;
board = new five.Board();

board.on('ready', function() {
      sensor = new five.Sensor({
          pin: "A0",
          freq: 2
      });

      sensor.scale([0,1024]).on('read', function() {
          Signal = this.scaled;
          calculate_bpm();

          if(QS === true) {
              console.log('BPM : ', BPM);
              QS = false;
          }
      });
});

function calculate_bpm() {

            sampleCounter += 2;
            N = sampleCounter - lastBeatTime;

            if(Signal < thresh && N > (IBI/5)*3) {
                  if (Signal < T) {
                        T = Signal;
                  }
            }

            if(Signal > thresh && Signal > P) {
                  P = Signal;
            }


            if (N > 250) {

              if ((Signal > thresh) && (Pulse === false) && (N > (IBI/5)*3)) {
                  Pulse = true;
                  IBI = sampleCounter - lastBeatTime;
                  lastBeatTime = sampleCounter;

                  if(secondBeat) {
                      secondBeat = false;
                      for(var i=0; i<=9; i++){
                          rate[i] = IBI;
                      }
                  }

                  if(firstBeat) {
                      firstBeat = false;
                      secondBeat = true;
                      return;
                  }


                  var runningTotal = 0;

                  for(var i=0; i<=8; i++) {
                      rate[i] = rate[i+1];
                      runningTotal += rate[i];
                  }

                  rate[9] = IBI;
                  runningTotal += rate[9];
                  runningTotal /= 10;
                  BPM = 60000/runningTotal;
                  QS = true;
              }
          }

          if (Signal < thresh && Pulse === true){
              Pulse = false;
              amp = P - T;
              thresh = amp/2 + T;
              P = thresh;
              T = thresh;
          }

          if (N > 2500) {
              thresh = 512;
              P = 512;
              T = 512;
              lastBeatTime = sampleCounter;
              firstBeat = true;
              secondBeat = false;
          }
}
