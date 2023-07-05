#pragma once

#include "encoder.h"

namespace pid {
  
float currT = 0;
float deltaT = 0;
float prevT = 0;
float prevE = 0; 
float errorDerivative = 0;
float errorIntegral = 0;
int PWM_p = 0;
bool key = 1;


const float kp = 0.3; 
const float ki = 0.005; 
const float kd = 20; 

int goal; //desire angle
  
   int targetPosition(){
  
     while(key){ 

      if (Serial.available()==1){
        
        goal = Serial.parseInt();

        Serial.println(goal);

        key = 0;
        
        }
          
      } 
      
    }


   void calculatePID(){
    
      currT = micros();
      
      deltaT = ((float)(currT - prevT)) / 1.0e6 ; 

      prevT = currT;

      errorValue = goal-encoder::position;

      errorDerivative =  (errorValue - prevE)/deltaT;

      errorIntegral = errorIntegral + (errorValue * deltaT); //Riemann sum

      PWM_p = kp*errorValue + kd*errorDerivative + ki*errorIntegral;

      prevE = errorValue; 

      encoder::PWM_send_past = encoder::PWM_send;

      //Debugging

      //Serial.print("Position:");
      
      //Serial.print(encoder::position);

      //Serial.print(",");

      //Serial.println(digitalRead(A0));

      //Serial.println(errorValue);

      //Serial.println(PWM_p);

      //Serial.println(encoder::PWM_send);

      //Serial.println(encoder::PWM_send_past);
         
    }

    void graph(){
      
      //Serial.print("Constant:");
      
      Serial.print(goal);

      Serial.print(",");

      //Serial.print("Position:");
      
      Serial.print(encoder::position);

      Serial.println(",");
      
      }

 
}
