void lcdUpdater(float t1[]){

  Serial.println("Printing LCD");
    for(int i =0; i < one_wire_devices_count; i++){
      Serial.print("Printing line: ");
      Serial.println(i);
      String floatTemp = String(t1[i]);
      lcd.setCursor(13,i);
      lcd.print("      ");
      lcd.setCursor(0, i);
      lcd.print(addressToString(allDevices[i]).substring(0,12));
      Serial.print("FloatTemo-7: ");
      Serial.print(floatTemp.length()-7);
      Serial.print(", FloatTempSize: ");
      Serial.println(floatTemp.length());
      for(int i = 0; i < 7-floatTemp.length(); i++){
        lcd.print(" ");
      }
      lcd.print(floatTemp);
      lcd.print((char)223);
    }
}


String formatTemp(float tempTemp){

return String(tempTemp);
  
}

