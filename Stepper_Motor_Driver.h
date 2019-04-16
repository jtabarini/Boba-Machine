//stepper motor driver class
//no microstepping currently supported

#ifndef Stepper_Motor_Driver_h
#define Stepper_Motor_Driver_h

#include "Arduino.h"

class Stepper_Motor_Driver {
  private:
    int pin_step, pin_dir, pin_enable;
    void step_motor(int num_steps, bool clockwise);

  public:
    Stepper_Motor_Driver(int step_pin, int dir_pin, int enable_pin);
    void step_clockwise(int num_steps);
    void step_counter_clockwise(int num_steps);
};

#endif
