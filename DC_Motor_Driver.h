//https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/

#ifndef DC_Motor_Driver_h
#define DC_Motor_Driver_h

#include "Arduino.h"

class DC_Motor_Driver {
  private:
    int pin_in1, pin_in2, pin_enable;

  public:
    DC_Motor_Driver(int in1_pin, int in2_pin, int enable_pin);
    void drive_clockwise(int motor_speed);
    void drive_counter_clockwise(int motor_speed);
    void stop_motor();
    void brake_motor();
};

#endif
