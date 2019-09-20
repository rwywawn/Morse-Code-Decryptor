
#include <Stepper.h>
#include <Wire.h> 

const float steps_per_rev = 32; 
const float gear_rev = 64;
const float steps_per_out_rev = steps_per_rev * gear_rev;
unsigned long signal_len,t1,t2;   
int input_pin = 2;                 
int led_pin = 4;                   
String code = "";                
int steps_required;
 
Stepper stepper_motor(steps_per_rev, 8, 10, 9, 11);

void setup()
{
  Serial.begin(9600);
  pinMode(input_pin, INPUT_PULLUP);
  pinMode(led_pin,OUTPUT);
}
 
void loop()
{
   
  steps_required  =  steps_per_out_rev ; 
  stepper_motor.setSpeed(1000);   
  stepper_motor.step(steps_required);

}
