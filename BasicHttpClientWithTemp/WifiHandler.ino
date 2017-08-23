 
 void wifiSetup(const char* ssidc,const char* passc){
    for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

   //WiFiMulti.addAP("Grannen3", "simma4hoppa11");
   WiFiMulti.addAP(ssidc, passc);
 }
 
 void handleWiFi(float tempC[]){
  static const unsigned long REFRESH_INTERVAL = 1000 * 20; // ms
  static unsigned long lastRefreshTime = 0;

  if(millis() - lastRefreshTime >= REFRESH_INTERVAL){
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    lastRefreshTime += REFRESH_INTERVAL;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    String path = "http://josie.magic-mouse.dk/index.php/Welcome/log_temp?sensor=%1&temp=%2";
    path.replace("%1", addressToString(allDevices[0]));
    path.replace("%2",String(tempC[0]));
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
    path2.concat(addressToString(allDevices[1]));
    path2.concat("&temp=");
    path2.concat(String(tempC[1]));
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
    path3.concat(addressToString(allDevices[2]));
    path3.concat("&temp=");
    path3.concat(String(tempC[2]));

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
  }
  }
