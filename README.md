# ESE218 MEMS Pressure Sensor Lab 

## Parts Required
- 1 x NodeMCU 8266
- 1 x [BMP388](https://www.adafruit.com/product/3966)

## Connections
I2C used to read in data.
|BMMP288 | NodeMCU|
|:------:|:------:|
|  Vin   |  3.3V  |
|  GND   |  GND   |
|  SCK   |  D1    |
|  SDI   |  D2    |
 
## Setup Instructions
1. Download or clone the github repo to your computer.
2. Follow [these instructions](https://docs.google.com/document/d/10YX97TspXGyPbyejvhkQ6DBXMTv6j4jiCOdM5Ycglfs/edit) to get Blynk setup. If you already have BLYNK setup, create a new template on the web dashboard and add the NodeMCU as a new device. **MAKE SURE THAT YOU REPLACE LINES 21, 22, 23 WITH YOUR TEMPLATE INFORMATION** 
3. In the Arduino IDE, install the following libraries:
    - Adafruit BMP3XX Library 
    - Click on "Install All" to install all the dependencies
    ![image](https://user-images.githubusercontent.com/13370293/141351346-d3e8db05-a1d7-424b-ae94-4cfede99bd67.png)

4. Flash the code in this repo onto the NodeMCU. You can do this by opening up ese_lab6_7.ino in the ese218_lab6_7 folder.
5. 6 Datastreams will need to be created on the web dashboard. Refer to the Blynk installation document.
  ![image](https://user-images.githubusercontent.com/13370293/141309947-42253f87-ee3b-43ba-bb3f-e73c3878c798.png)
6. On the web dashboard, create the following widgets. Assign the datastreams accordingly.
    - 1 x SuperChart widget (Datastream V0)
    - 1 x Gauge widget (Datastream V1)
    - 3 x Label widgets (Datastream V0, V2, V3)
  ![image](https://user-images.githubusercontent.com/13370293/141311223-81f55f72-dbc3-41c0-a2a9-d1feed8fe014.png)
7. On the mobile dashboard/app, create the following widgets. Assign the datastreams accordingly.
    - 1 x SuperChart (Datastream V0)
      To configure the SuperChart, after dragging it to your template. Double tap on it to modify the settings. Click on the circled button in the image below to select Datastream V0.
      ![IMG_AED375BEBFC3-1](https://user-images.githubusercontent.com/13370293/141351956-4db96baa-94cc-45ed-99bb-2f171682482c.jpeg)
    - 1 x Gauge (Datastream V1)
    - 3 x Label Value (Datastreams V0, V2, V3)
    - 2 x Button (Datastreams V4, V5)
      - Datastream V4 Button Configurations
        - Mode: SWITCH
        - ON label is "Stop"
        - OFF label is "Start"
      - Datastream V5 Button Configurations
        - Mode: PUSH
        - ON label is "Off"
        - OFF label is "Reset"
     ![IMG_C1468CF87758-1](https://user-images.githubusercontent.com/13370293/141312667-2ab3030f-7c16-48b0-9c44-8a35586f2756.jpeg)
8. Press start on the mobile app to start the timer.

Written by Kim Luong.
