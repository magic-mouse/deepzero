void lcdUpdater(float t1, float t2, float t3){
  
  lcd.setCursor(0, 0);
  lcd.print(addressToString(allDevices[0]));
  lcd.print(" ");
  lcd.print(String(t1));
  lcd.print((char)223);
  
  lcd.setCursor(0, 1);
  lcd.print(addressToString(allDevices[1]));
  lcd.print(" ");
  lcd.print(String(t2));
  lcd.print((char)223);
  lcd.setCursor(0, 2);
  lcd.print(addressToString(allDevices[2]));
  lcd.print(" ");
  lcd.print(String(t3));
  lcd.print((char)223);
  lcd.setCursor(0,3);
}

