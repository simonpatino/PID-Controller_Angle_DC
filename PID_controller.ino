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

     pid::targetPosition();
  
     pid::calculatePID();
     
     encoder::setMotorSpeed(pid::PWM_p);

     pid::graph();
  
}
