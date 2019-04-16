#ifndef LimitSwitch_h
#define LimitSwitch_h

#include "Arduino.h"

class LimitSwitch{
  private:
    int pin_port;
  public:
    LimitSwitch(int port_pin);
    bool is_pressed();
};

#endif
