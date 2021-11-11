/***************************************************************************
  This is a library for the BMP3XX temperature & pressure sensor. Designed specifically to work with the Adafruit BMP388 Breakout ----> http://www.adafruit.com/products/3966
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required to interface. Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries. BSD license, all text above must be included in any redistribution
 ***************************************************************************/

// Complete project details: https://RandomNerdTutorials.com/esp8266-nodemcu-bmp388-arduino/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define BMP_SCK 14
#define BMP_MISO 12
#define BMP_MOSI 13
#define BMP_CS 15

#define BLYNK_PRINT Serial /* Comment this out to disable prints and save space */
#define BLYNK_TEMPLATE_ID "TMPLBgeMqc0l"
#define BLYNK_DEVICE_NAME "Kim test 2"
#define BLYNK_AUTH_TOKEN "LXaBN8aRKf9d1aRnBcxTotufpLOlXduK"



#define SEALEVELPRESSURE_HPA (1013.25)

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AirPennNet-Device";
char pass[] = "penn1740wifi";

float t;
float p;
float a;

int start_timer = 0;
int start_time = 0;
int saved_time = 0;
int reset_timer = 0;

Adafruit_BMP3XX bmp;
BlynkTimer timer;

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
 // Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
 // Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  //Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void sendSensor()
{

   if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  t = bmp.temperature;
  p = bmp.pressure / 100.0;  // in hPa
  a = bmp.readAltitude(SEALEVELPRESSURE_HPA);

  if(start_timer)
  {
    saved_time = (millis()-start_time)/1000;
  }
  if(reset_timer)
  {
    saved_time = 0;
    reset_timer = 0;
  }
 /*  
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(p);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(a);
  Serial.println(" m");

  Serial.println();
 */ 
  Blynk.virtualWrite(V0, p); //V0 
  Blynk.virtualWrite(V1, t); //V1 
  Blynk.virtualWrite(V2,a); //V2
  Blynk.virtualWrite(V3,saved_time);
}

void setup() {
 // Serial.begin(115200);
 Serial.begin(9600);
  while (!Serial);
   Serial.println(" ");
  Serial.println("Adafruit BMP388 / BMP390 test");
 Blynk.begin(auth, ssid, pass);
 Serial.println("BLYNK Start");
  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
  //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode  
  //if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

// Start/Stop Timer
BLYNK_WRITE(V4) {
  int start = param.asInt();
  reset_timer = 0;
  if(start)
  {
    start_timer = 1;
    Blynk.virtualWrite(V3, 0);
    start_time = millis();
  }
  else
  {
    start_timer = 0;
  }
}

// Reset Timer
BLYNK_WRITE(V5) {
  Blynk.virtualWrite(V3,0);
  reset_timer = 1;
//  int up = param.asInt();
//  digitalWrite(16, up);
}
void loop() {
   Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
