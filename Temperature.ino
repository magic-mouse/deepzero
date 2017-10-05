String addressToString(DeviceAddress deviceAddress)
{
  String out = "";
  for (uint8_t i = 0; i < 8; i++)
  {
    out.concat(String(deviceAddress[i], HEX));
  }
  return out;
}
