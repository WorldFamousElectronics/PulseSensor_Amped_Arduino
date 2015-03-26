![logo](https://avatars0.githubusercontent.com/u/7002937?v=3&s=200)

## Pulse Sensor Arduino Code
1. Blinks an LED to User's Live Heartbeat   
2. Fades an LED to User's Live HeartBeat
3. Determines BPM
4. Prints All of the Above to Serial

## Screen Shot
![ScreenShot](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/ScreenCapArduino.png) 


## To Use:
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

##Variables to Note
Variable Name     | What it does
------------------| -------------
Signal            | **Int** that holds **raw Analog Input data on **Pin 0**, the Pulse Sensor's **Purple Cable**. It's updated every 2mS.
BPM               | **Int** that holds the **heart-rate value**, derived every beat, from averaging **previous 10 IBI values**. 
IBI               | **Int** that holds the **time interval between beats**! Must be seeded! 
Pulse             | **Boolean** that is **true when a heartbeat is sensed**. It's **false** other times.  It **controls LED Pin 13**.
QS                | **Boolean** that is **true whenever Pulse is found and BPM** is updated. User must reset. 



## Serial Monitor Visualizer Output
![asciiviz](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/pics/asciiviz.png)
See the User's Pulse & BPM without leaving Arduino.  Open the serial monitor for this ASCII visualization. 
To Open Serial Monitor: `Arduino >> Tools >> Serial Monitor`



## Serial to Processing, our Mac App, or a third-party serial reader
To talk to other App's via serial you need to disable the Serial Monitor Visualizer. 

Change:
```
// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'true' by Default.  Re-set to 'false' to sendDataToSerial instead. : ) 
```
too:
```
// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'true' by Default.  Re-set to 'false' to sendDataToSerial instead. : ) 
```

That's it!.
The serial Data can be used/viewed:
* In the Arduino Serial Monitor  `Arduino >> Tools >> Serial Monitor`
* With our <a href="https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer"> "Processing Visualizer"</a>
* In our native Mac App (TBA Spring 2015) 
* Any any third-party serial reader.



## (Advanced) Timer Interrupt Notes / PWM on Pin 3 & 11
There is a tab in the Arduino code called Timer_Interrupt_Notes. This page describes how to set up the Timer interrupt depending on which version of Arduino you are using, and what other things you may want to do with your sketch. Please read it carefully!

PWM on pins 3 and 11 will not work when using this code, because we are using Timer 2!


## The Video
<a href="https://vimeo.com/123008578"> "The Pulse Sensor in 60 Seconds"</a>
