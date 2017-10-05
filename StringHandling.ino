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
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonArray& tempArr = jsonBuffer.parseArray(mapSD);
  if(!tempArr.success()){
    Serial.print("sdMap : ");
    Serial.println("parseObject() failed");
    return;
  }


  for(int i = 0; i < tempArr.size(); i++) {
      tempMap[i] = {tempArr[i]["id"], tempArr[i]["name"]};
  }




  Serial.println("===========");
  //Serial.println(hello);
  Serial.println("===========");
}

