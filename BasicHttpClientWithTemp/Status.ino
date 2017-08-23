
//#define ERROR_THREASHOLD 10
//
//int curent_loop_error;
int total_error = 0;
//
void checkSelfStatus(){
  
// current_loop_error = 1;
//  if(current_loop_error > ERROR_THREASHOLD){
    // Try to reset machine
//  }

  checkSDConnection();

  checkWiFi();
  Serial.println("check Thermometer");
  checkThermometer();
}

void checkSDConnection(){
  
}

void checkWiFi(){
  
}

void checkThermometer(){
  sensors.begin();
Serial.print("oneWireDevicesCount: ");
Serial.print(one_wire_devices_count);
Serial.print(" sensor.getDevices(): ");
Serial.println(sensors.getDeviceCount());

  if(one_wire_devices_count != sensors.getDeviceCount()){
      lcd.clear();
      detectDevices();
  }
  
}

