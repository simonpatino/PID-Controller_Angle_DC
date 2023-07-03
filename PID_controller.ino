//PID control 

#include "PID.h"
#include "encoder.h"


void setup() {
  
  Serial.begin(9600);

  encoder::Encoder_Motor_Setup();
  
  encoder::Interrupt();

  delay(1000);
  
}

void loop() {

  //PID::targetPosition();
  
     pid::calculatePID();
     
     encoder::setMotorSpeed(errorValue);

     pid::graph();

      
}
