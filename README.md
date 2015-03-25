![alt text][logo]
[logo]: https://avatars0.githubusercontent.com/u/7002937?v=3&s=200 "Logo Title Text 1"

## Pulse Sensor Arduino Code
1. Blinks an LED to User's Live Heartbeat   
2. Fades an LED to User's Live HeartBeat
3. Determines BPM
4. Prints All of the Above to Serial

## To Use:
1. Take the entire file 'PulseSensorAmped_Arduino_1dot1' into your Documents/Arduino.
2. Then start, or restart Arduino IDE and find the code in your Sketch folder.


## Pulse Sensor Hook-up
Arduino Pin   | Pulse Sensor Cable Color
------------- | -------------
RED           | 5V or 3V   
BLACK         | GND (GROUND)
PURPLE        | ANALOG IN 0

##Variables to Note
1. Signal :    int that holds the analog signal data straight from the sensor. updated every 2mS.
2. IBI  :      int that holds the time interval between beats. 2mS resolution.
3. BPM  :      int that holds the heart rate value, derived every beat, from averaging previous 10 IBI values.
4. QS  :       boolean that is made true whenever Pulse is found and BPM is updated. User must reset.
5. Pulse :     boolean that is true when a heartbeat is sensed then false in time with pin13 LED going out.


## Note 
There is a tab in the Arduino code called Timer_Interrupt_Notes. This page describes how to set up the Timer interrupt depending on which version of Arduino you are using, and what other things you may want to do with your sketch. Please read it carefully!

## The Video
<a href="https://vimeo.com/123008578"> "The Pulse Sensor in 60 Seconds"</a>
