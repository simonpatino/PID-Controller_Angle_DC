#pragma once

#include <AFMotor.h>

#include "PID.h"

float errorValue = 0;

namespace encoder {
  

AF_DCMotor motor(4);

#define ENCA_ONE A0
#define ENCA_TWO 2

float position = 0;
volatile int pos_i = 0;
int PWM_send = 0;
bool key = 1;
int PWM_send_past =1000;


  void Encoder_Motor_Setup() {
  
    pinMode(INPUT, ENCA_ONE);
    pinMode( INPUT, ENCA_TWO);
    motor.setSpeed(0);
  
  }
  
  
  void readEncoder() {

    int state = digitalRead(ENCA_ONE);
    
    int increment = 0;
  
    if (state > 0) {
  
      increment = 1;
  
    } else {
  
      increment = -1;
  
    }

    pos_i = pos_i + increment;
  
    //position = pos_i * 0.46875;

    position = pos_i * 0.4411;
  
  }
  
  
  void Interrupt() {
  
    attachInterrupt(digitalPinToInterrupt(ENCA_TWO), readEncoder, RISING);
  
  }
  
  
  void setMotorSpeed(int PWM_p) {
    
  //direction
  
    if (PWM_p < 0){ 
   
      motor.run(BACKWARD);
      
    } 
    
    else if (PWM_p > 0){
      
      motor.run(FORWARD);
      
    }
    
    else {
      
      motor.setSpeed(0);

      key = 0;
      
    }


     PWM_send = (int)abs(PWM_p);  //fabs() = floating point absolute value
     
  //velocity: capping the PWM signal - 8 bit


    if ((PWM_send +PWM_send_past)/2  < 8){
      
      motor.setSpeed(0);  

      //Serial.println("im here");
      
      }

    else if (PWM_send > 255){ 
    
      motor.setSpeed(255); 

      //Serial.println("im here");
      
    }
  
    else if (PWM_send < 0 ){
      
      motor.setSpeed(0);

      //Serial.println("im here");
      
    }

    else if (PWM_send < 120 && errorValue != 0 ){
      
      motor.setSpeed(120);

      //Serial.print("im here");
      
      }
  
    else {
      
      motor.setSpeed(PWM_send);

      //Serial.println("im here");
      
      }
 
  
  }
  
}
