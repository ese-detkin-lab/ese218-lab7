/***************************************************************************
 * Creator: Kim Luong, 2021-11-10
  All instructions are on the github repo. https://github.com/ese-detkin-lab/ese219-lab7
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include "Adafruit_Sensor/Adafruit_Sensor.h"
#include "Adafruit_BMP3XX.h"

// If using SPI, replace the pin numbers appropriately
#define BMP_SCK 14
#define BMP_MISO 12
#define BMP_MOSI 13
#define BMP_CS 15

#define BLYNK_PRINT Serial 

//************************************************************
// REPLACE THE 3 LINES BELOW WITH YOUR OWN TEMPLATE INFORMATION
#define BLYNK_TEMPLATE_ID "TemplateID"
#define BLYNK_DEVICE_NAME "devicename"
#define BLYNK_AUTH_TOKEN "somethingsecrethere"
//***********************************************************

#define SEALEVELPRESSURE_HPA (1013.25)

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "AirPennNet-Device";
char pass[] = "penn1740wifi";

// Variables
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
}

void sendSensor()
{

  if (! bmp.performReading()) 
  {
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

  // Uncomment the following if you wish to print to serial monitor.
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
  
  // Send information to blynk app
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
}
void loop() {
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
