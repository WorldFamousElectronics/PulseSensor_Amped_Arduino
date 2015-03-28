![logo](https://avatars0.githubusercontent.com/u/7002937?v=3&s=200)

## Pulse Sensor Arduino Code
1. Blinks an LED to User's Live Heartbeat   
2. Fades an LED to User's Live HeartBeat
3. Determines BPM
4. Prints All of the Above to Serial

## Screen Shot
![ScreenShot](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/ScreenCapArduino.png) 


## Installing
1. Download ZIP on this page: 
![Download](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/download.png)
2. Take the **PulseSensor_Amped_Arduino-master.zip** file, and move it to your **Documents/Arduino** folder.
3. **Unzip** PulseSensor_Amped_Arduino-master.zip in your **Documents/Arduino** folder.  
**This properly installs your files**

4.  
  * Double-click on **PulseSensorAmped_Arduino_1dot2.ino** ![filesys](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/filesys.png)

  *  **Or,** 0pen project in **Arduino via *File > Sketchbook > PulseSensor_Arduino-Master > PulseSensorAmped_Arduino_1dot2.ino**
 ![sketchbook](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/ArduinoSketch.png)


## Pulse Sensor Hook-up
Arduino Pin   | Pulse Sensor Cable Color
------------- | -------------
RED           | 5V or 3V   
BLACK         | GND (GROUND)
PURPLE        | ANALOG 0 (Zero)

![cablehookup](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/cablehookup.png)


## Ear-Clip or Finger-Strap Config
![Picture](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer/blob/master/EarClip.png)
![Picture](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer/blob/master/FingerStrap.png)


##Variables to Note
Variable Name     | What it does
------------------| -------------
Signal            | **Int** that holds **raw Analog Input data on **Pin 0**, the Pulse Sensor's **Purple Cable**. It's updated every 2mS.
BPM               | **Int** that holds the **heart-rate value**, derived every beat, from averaging **previous 10 IBI values**. 
IBI               | **Int** that holds the **time interval between beats**! Must be seeded! 
Pulse             | **Boolean** that is **true when a heartbeat is sensed**. It's **false** other times.  It **controls LED Pin 13**.
QS                | **Boolean** that is **true whenever Pulse is found and BPM** is updated. User must reset. 


## Works with Pulse Sensor Apps
This Arduion App works with:
* Works with our **Processing App** <a href="https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer"> "Processing Visualizer"</a>
*  Works with our **Pulse Sensor Mac App** <a href="https://itunes.apple.com/us/app/pulse-sensor/id974284569?ls=1&mt=12"> "Pulse Sensor Mac App"</a>
* Works with **any** third-party serial reader.



## ASCII Serial Monitor Visuals 
See the User's Pulse & BPM without leaving Arduino.  Open the serial monitor for this ASCII visualization.
* To Open Serial Monitor: `Arduino >> Tools >> Serial Monitor`
![asciiviz](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/asciiviz.png)

To Turn On ASCII Visualizer:

```
// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default. 

```
too:
```
// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Re-set to 'true' to do ASCII Visual Pulse  : ) 

```
That's it's!   Upload and open your Arduino Serial Monitor. 



## (Advanced) Timer Interrupt Notes / PWM on Pin 3 & 11
There is a tab in the Arduino code called Timer_Interrupt_Notes. This page describes how to set up the Timer interrupt depending on which version of Arduino you are using, and what other things you may want to do with your sketch. Please read it carefully!

PWM on pins 3 and 11 will not work when using this code, because we are using Timer 2!


## The Video
<a href="https://vimeo.com/123008578"> "The Pulse Sensor in 60 Seconds"</a>
