void detectDevices(){
  one_wire_devices_count = sensors.getDeviceCount();

  lcd.setCursor(0,0);
  lcd.print("Found devices: ");
  lcd.print(one_wire_devices_count);
  delay(1000);
  
  for(int i = 0; i < one_wire_devices_count; i++){
    sensors.getAddress(allDevices[i],i);
  }

  for(int i = 0; i < one_wire_devices_count; i++){
    String introText = "########## Running setup on device %1 ##########";
    introText.replace("%1", String(i));
    Serial.println(introText);
    String a = "Device %1 Address: ";
    a.replace("%1",String(i));
    Serial.print(a);
    printAddress(allDevices[i]);
    Serial.println();
    Serial.println("Setting resolution");
    sensors.setResolution(allDevices[i], TEMPERATURE_PRECISION);
    String b = "Device %1 Resolution: ";
    b.replace("%1",String(i));
    Serial.print(b);
    Serial.print(sensors.getResolution(allDevices[1]), DEC);
    Serial.println();
  }
}


// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

String addressToString(DeviceAddress deviceAddress)
{
  String out = "";
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    out.concat(String(deviceAddress[i], HEX));
  }
  return out;
}
