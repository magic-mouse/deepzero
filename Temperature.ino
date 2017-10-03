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
