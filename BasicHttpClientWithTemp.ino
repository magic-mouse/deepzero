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

LiquidCrystal_I2C lcd(0x27, 20, 4);


#define ONE_WIRE_BUS 10
#define TEMPERATURE_PRECISION 9
#define SD_CS 3



ESP8266WiFiMulti WiFiMulti;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer, outsideThermometer;
DeviceAddress sideThermometer;
//WifiSensorLoop wsl;

File myFile;
String ssid, passwd, sdtemp;
int one_wire_devices_count;

char* ssidc;
char* passc;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 



  Serial.print("Initializing SD card...");
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

  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();


  one_wire_devices_count = sensors.getDeviceCount();
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");
  if (!sensors.getAddress(sideThermometer, 2)) Serial.println("Unable to find address for Device 1");


  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(outsideThermometer);
  Serial.println();

  Serial.print("Device 2 Address: ");
  printAddress(sideThermometer);
  Serial.println();

  // set the resolution to 9 bit
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(sideThermometer, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(outsideThermometer), DEC);
  Serial.println();

  Serial.print("Device 2 Resolution: ");
  Serial.print(sensors.getResolution(sideThermometer), DEC);
  Serial.println();

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

     WiFiMulti.addAP("Grannen3", "simma4hoppa11");

  Serial.print("ssid: ");
  Serial.println(ssidc);
  Serial.print("passc: ");
  Serial.println(passc);

 // WiFiMulti.addAP(ssidc, passc);

}

void loop() {

//  checkSelfStatus();

  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    float tempC = sensors.getTempC(insideThermometer);
    float tempC2 = sensors.getTempC(outsideThermometer);
    float tempC3 = sensors.getTempC(sideThermometer);

  lcd.setCursor(0, 0);
  lcd.print("temp1: ");
  lcd.print(String(tempC));
  lcd.print((char)223);
  lcd.setCursor(0, 1);
  lcd.print("temp2: ");
  lcd.print(String(tempC2));
  lcd.print((char)223);
  lcd.setCursor(0, 2);
  lcd.print("temp3: ");
  lcd.print(String(tempC3));
  lcd.print((char)223);


    String path = "http://josie.magic-mouse.dk/index.php/Welcome/log_temp?sensor=";
    path.concat(addressToString(insideThermometer));
    path.concat("&temp=");
    path.concat(String(tempC));

    Serial.print(path);

    http.begin(path); //HTTP

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

    String path2 = "http://josie.magic-mouse.dk/index.php/Welcome/log_temp?sensor=";
    path2.concat(addressToString(outsideThermometer));
    path2.concat("&temp=");
    path2.concat(String(tempC2));

    Serial.print(path2);

    http.begin(path2); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode2 = http.GET();

    // httpCode will be negative on error
    if (httpCode2 > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode2);

      // file found at server
      if (httpCode2 == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode2).c_str());
    }

    http.end();


    String path3 = "http://josie.magic-mouse.dk/index.php/Welcome/log_temp?sensor=";
    path3.concat(addressToString(sideThermometer));
    path3.concat("&temp=");
    path3.concat(String(tempC3));

    Serial.print(path3);

    http.begin(path3); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode3 = http.GET();

    // httpCode will be negative on error
    if (httpCode3 > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode3);

      // file found at server
      if (httpCode3 == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode3).c_str());
    }

    http.end();
  }



  delay(1000 * 20); //60*30);
}


