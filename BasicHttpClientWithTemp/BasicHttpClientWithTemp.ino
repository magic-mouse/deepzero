/* 
 *  #### INCLUDES ####
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 

/* 
 *  #### DEFINITIONS ####
 */
#define ONE_WIRE_BUS 10
#define TEMPERATURE_PRECISION 9
#define SD_CS 3
#define LCD_BUS 0x27

/* 
 *  ##### CONSTRUCTORS ####
 */
ESP8266WiFiMulti WiFiMulti;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress allDevices[15];
LiquidCrystal_I2C lcd(LCD_BUS, 20, 4);
File myFile;

/* 
 * #### GLOBAL VARIABLES ####
 */
String ssid;
String passwd;
String sdtemp;

char* ssidc;
char* passc;

int one_wire_devices_count;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.clear();

  if (!SD.begin(SD_CS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("conf.txt");
  if (myFile) {
    while (myFile.available()) {
      float pass = myFile.read();
      char passchr = pass;
      sdtemp += passchr;
    }
    myFile.close();
  } else {
    Serial.println("error opening file");
  }

  getIt(sdtemp);

  //Dallas Temperature IC Control Library Demo
  sensors.begin();

  detectDevices();



  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

}

void loop() {

  checkSelfStatus();
  Serial.print("OWDC: ");
  Serial.println(one_wire_devices_count);
  
 float tempC[one_wire_devices_count];

  Serial.println("Print temps");
  for(int i =0; i < one_wire_devices_count; i++){  
    tempC[i] = sensors.getTempC(allDevices[i]);
    Serial.print("Index: ");
    Serial.print(String(i));
    Serial.print(", address: ");
    Serial.print(addressToString(allDevices[i]));
    Serial.print(", temp: ");
    Serial.println(tempC[i]);
  }
  
  lcdUpdater(tempC);
 

  delay(1000);
}


