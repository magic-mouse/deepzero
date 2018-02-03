void getIt(String getIt){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(getIt);
  
  if (!root.success()) {
      Serial.print("getIt : ");
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
  Serial.println(mapSD);
  Serial.println("====================");
  
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& tempArr = jsonBuffer.parseObject(mapSD);
  if(!tempArr.success()){
    Serial.print("sdMap : ");
    Serial.println("parseObject() failed");
    return;
  }

int autoIndex = 0;
for (auto kv : tempArr) {
    Serial.println(kv.key);
    Serial.println(kv.value.as<char*>());
    tempMap[autoIndex] = {kv.key, kv.value.as<char*>()};
    autoIndex++;
}

  tempMapSize = autoIndex;

  Serial.println("===========");
  Serial.println("===========");
}

