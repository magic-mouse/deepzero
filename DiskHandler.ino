void confFromSD(){
  myFile = SD.open("conf.txt");
  if (myFile) {
    while (myFile.available()) {
      sdtemp += (char)myFile.read();
    }
    myFile.close();
  } else {
    Serial.println("error opening file");
  }
}

void mapsFromSD(){
  myFile = SD.open("tempmap.txt");
  if (myFile){
    while (myFile.available()){
      mapTemp += (char)myFile.read();
    }
    myFile.close();
  }else {
    Serial.println("error opening file");
  }
}

void logTemperatureToDisk(String id, float temp, DateTime ace){
  myFile = SD.open("log.txt", FILE_WRITE);
  if(myFile){
    myFile.print(id);
    myFile.print(",");
    myFile.print(String(temp));
    myFile.print(",");
    myFile.print(ace.year(), DEC);
    myFile.print('/');
    myFile.print(ace.month(), DEC);
    myFile.print('/');
    myFile.print(ace.day(), DEC);
    myFile.print(",");
    myFile.print(ace.hour(), DEC);
    myFile.print(':');
    myFile.print(ace.minute(), DEC);
    myFile.print(':');
    myFile.println(ace.second(), DEC);
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening log.txt");
  }
}

