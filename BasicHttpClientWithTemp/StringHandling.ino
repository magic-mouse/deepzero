  
char* findSSID(String sdTemp, long pass){
  if (sdtemp.startsWith("ssid: ") && pass == 13) {
    ssid = sdtemp.substring(sdtemp.indexOf(32) + 1, sdtemp.length());
    ssidc = new char[ssid.length()];
    ssid.toCharArray(ssidc, ssid.length() + 1);
  }
  return ssidc;
}

//if (sdtemp.startsWith("password: ")) {
//  passwd = sdtemp.substring(sdtemp.indexOf(32) + 1, sdtemp.length());
//  Serial.print("passwd length: ");
//  Serial.println(passwd.length());
//  passc = new char[passwd.length()];
//  Serial.println(sizeof(passc));
//  passwd.toCharArray(passc, ssid.length() + 1);
//}

void getIt(String getIt){
   
  int pointer = 0;

  int firstPointer = getIt.indexOf("\n");
  String firstString = getIt.substring(pointer, firstPointer);
  int secondPointer = getIt.indexOf("\n", firstPointer+1);
  String secondString = getIt.substring(firstPointer+1, secondPointer);
  String thirdString = getIt.substring(secondPointer+1, getIt.length());
}


