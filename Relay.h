#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
  private:
    int pin_signal;
    bool norm_open;
  public:
    Relay(int signal_pin, bool normally_open);
    void on();
    void off();
};

#endif
