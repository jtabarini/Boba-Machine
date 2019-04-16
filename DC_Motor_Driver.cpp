//Enable pin has to be pwm!!!

#include "Arduino.h"
#include "DC_Motor_Driver.h"

DC_Motor_Driver::DC_Motor_Driver(int in1_pin, int in2_pin, int enable_pin){
  pinMode(enable_pin, OUTPUT);
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);

  pin_enable = enable_pin;
  pin_in1 = in1_pin;
  pin_in2 = in2_pin;

  //set motor to off
  analogWrite(pin_enable, 0);
}

void DC_Motor_Driver::drive_counter_clockwise(int motor_speed){
  //motor_speed needs to be 0-255
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);

  analogWrite(pin_enable, motor_speed);
}

void DC_Motor_Driver::drive_clockwise(int motor_speed) {
  //motor_speed needs to be 0-255
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);

  analogWrite(pin_enable, motor_speed);
}

void DC_Motor_Driver::brake_motor() {
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, LOW);

  digitalWrite(pin_enable, HIGH);
}

void DC_Motor_Driver::stop_motor() {
  digitalWrite(pin_enable, LOW);  
}
