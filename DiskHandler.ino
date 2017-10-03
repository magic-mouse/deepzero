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

