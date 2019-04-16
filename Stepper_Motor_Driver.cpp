//stepper motor driver class
//no microstepping currently supported

#include "Arduino.h"
#include "Stepper_Motor_Driver.h"

Stepper_Motor_Driver::Stepper_Motor_Driver(int step_pin, int dir_pin, int enable_pin){
    //hook up MS1, MS2, GND to ground
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);
    digitalWrite(enable_pin, HIGH);

    pin_step = step_pin;
    pin_dir = dir_pin;
    pin_enable = enable_pin;
}

void Stepper_Motor_Driver::step_motor(int num_steps, bool clockwise){
  digitalWrite(pin_dir, clockwise); //Pull direction pin low to move "forward"
  for(int x= 1; x<num_steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(pin_step,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(pin_step,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

void Stepper_Motor_Driver::step_clockwise(int num_steps){
  step_motor(num_steps, true);
}

void Stepper_Motor_Driver::step_counter_clockwise(int num_steps){
  step_motor(num_steps, false);
}
