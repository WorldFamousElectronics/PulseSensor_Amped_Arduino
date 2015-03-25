# PulseSensor_Amped_Arduino
Pulse Sensor Amped Arduino Code

Take the entire file 'PulseSensorAmped_Arduino_1dot1' into your
Documents/Arduino
folder. Then start, or restart Arduino IDE and find the code in your Sketch folder.


### Pulse Sensor Colored Cable Hook-up
--  
OPTIONAL LED HOOK-UP
BLINK LED:  PIN 13 & GROUND
FADE LED:  PIN 5


###Variables to Note
-- 
Signal :    int that holds the analog signal data straight from the sensor. updated every 2mS.
IBI  :      int that holds the time interval between beats. 2mS resolution.
BPM  :      int that holds the heart rate value, derived every beat, from averaging previous 10 IBI values.
QS  :       boolean that is made true whenever Pulse is found and BPM is updated. User must reset.
Pulse :     boolean that is true when a heartbeat is sensed then false in time with pin13 LED going out.


##NOTE 
--
There is a tab in the Arduino code called Timer_Interrupt_Notes. This page describes how to set up the Timer interrupt depending on which version of Arduino you are using, and what other things you may want to do with your sketch. Please read it carefully!
