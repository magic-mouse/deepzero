void getIt(String getIt){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(getIt);
  
  if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
  }
  const char* tempSsid = root["ssid"];
  const char* tempPass = root["pass"];
  ssid = const_cast<char*>(tempSsid);
  pass = const_cast<char*>(tempPass);
}

void mapSD(String mapSD){
  Serial.println("MapSD");
  StaticJsonBuffer<200> jsonBuffer;
  JsonArray& tempMap = jsonBuffer.parseArray(mapSD);
  if(!tempMap.success()){
    Serial.println("parseObject() failed");
    return;
  }

  const char* hello = tempMap[0];




  Serial.println("===========");
  Serial.println(hello);
  Serial.println("===========");
}

