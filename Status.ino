
#define ERROR_THREASHOLD 10
//
//int curent_loop_error;
int total_error = 0;
//

void updateTotalError(){
  total_error++;
}

void updateTotalErrorTolerance(){
  if(total_error == 0){
    return;
  }
  total_error--;
}

void checkSelfStatus(){
  
// current_loop_error = 1;
  if(total_error > ERROR_THREASHOLD){
    Serial.println("The device should reset now, but it dont since this is just a message");
  }
  updateTotalErrorTolerance();

  checkSDConnection();

  checkWiFi();

  checkThermometer();
}

void checkSDConnection(){
  
}

void checkWiFi(){
  
}

void checkThermometer(){
  
}

void printTimeToSerial(DateTime ace ){
    Serial.print(ace.year(), DEC);
    Serial.print('/');
    Serial.print(ace.month(), DEC);
    Serial.print('/');
    Serial.print(ace.day(), DEC);
    Serial.print(",");
    Serial.print(ace.hour(), DEC);
    Serial.print(':');
    Serial.print(ace.minute(), DEC);
    Serial.print(':');
    Serial.println(ace.second(), DEC);

}

