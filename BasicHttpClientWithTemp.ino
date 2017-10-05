/*
    #### INCLUDES ####
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
#include "RTClib.h"
#include "Thermo.h"

/*
    #### DEFINITIONS ####
*/
#define ONE_WIRE_BUS 10
#define TEMPERATURE_PRECISION 9
#define SD_CS 3
#define LCD_BUS 0x27

/*
    ##### CONSTRUCTORS ####
*/
ESP8266WiFiMulti WiFiMulti;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress allDevices[128];
LiquidCrystal_I2C lcd(LCD_BUS, 20, 4);
File myFile;
RTC_DS1307 rtc;

/*
   #### GLOBAL VARIABLES ####
*/

String sdtemp;
String mapTemp;
char* ssid;
char* pass;
String path = "http://josie.magic-mouse.dk/index.php/Welcome/log_temp?sensor=%1&temp=%2";
int one_wire_devices_count;
Thermo tempMap[128];

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight

  if (!SD.begin(SD_CS)) {
    Serial.println("initialization failed!");
    return;
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  printTimeToSerial(rtc.now());

  confFromSD();
  getIt(sdtemp);

  mapsFromSD();
  mapSD(mapTemp);

  //Dallas Temperature IC Control Library Demo
  sensors.begin();
  one_wire_devices_count = sensors.getDeviceCount();

  for (int i = 0; i < one_wire_devices_count; i++) {
    sensors.getAddress(allDevices[i], i);
    sensors.setResolution(allDevices[i], TEMPERATURE_PRECISION);
  }

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(ssid, pass);

}

void loop() {

  checkSelfStatus();

  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  float tempC = sensors.getTempC(allDevices[0]);
  
  static const unsigned long REFRESH_INTERVAL = 1000 * 20; // ms
  static unsigned long lastRefreshTime = 0;

  if (millis() - lastRefreshTime >= REFRESH_INTERVAL) {



    lcd.setCursor(0, 0);
    lcd.print(addressToString(allDevices[0]));
    lcd.print(" ");
    lcd.print(String(tempC));
    lcd.print((char)223);
  
    lcd.setCursor(0,1);
    lcd.print("                    ");
  
    lcd.setCursor(0,2);
    lcd.print("                    ");
  
    lcd.setCursor(0,3);
    lcd.print("                    ");

    
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      lastRefreshTime += REFRESH_INTERVAL;

      for (int i = 0; i < one_wire_devices_count; i++) {
        float temperature = sensors.getTempC(allDevices[i]);
        if(temperature < -100){
          updateTotalError();
          Serial.println("Error in temperature reading skipping HTTP");
          continue;
        }
        HTTPClient http;


        Serial.print("[HTTP] begin...\n");

        

        Serial.print("Temperature from: ");
        Serial.print(addressToString(allDevices[i]));
        Serial.print(" , Temperature: ");
        Serial.println(String(temperature));

        path.replace("%1", addressToString(allDevices[i]));
        path.replace("%2", String(temperature));
        Serial.print(path);

        http.begin(path); //HTTP

        logTemperatureToDisk(addressToString(allDevices[i]), temperature, rtc.now());

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
          }

        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
      }
    }
  }


  delay(1000);
}


