/*
 * Can only be used for input
 * A0 - turntable_motor_reset_switch
 * A1 - 
 * A2 - 
 * A3 - 
 * A4 - 
 * A5 - 
 * 
 * PORTS 0 and 1 i think can't be used during operation because of
 *  serial communication over the usb
 *  
 * Digital Write/Read pins
 * 2 - pump1
 * 4 - pump2
 * 7 - milk_pump_relay
 * 8 - turntable_stepper step
 * 12 - turntable_stepper dir
 * 13 - flavor_push_motor in1
 * 
 * PWM pins
 * 3 - turntable_stepper enable
 * 5 - flavor_push_motor in2
 * 6 - flavor_push_motor pin_enable
 * 10 - 
 * 11 - 
 */

/*
 * 1 stepper driver
 * 3 relays
 * 1 H-Bridge port
 * 3 LimitSwitches
 */
#include "Relay.h"
#include "DC_Motor_Driver.h"
#include "Stepper_Motor_Driver.h"
#include "LimitSwitch.h"

#define EMPTY 69
#define MILK_PUMP_TIME 2 * 1000
#define PUMP_TIME 8*1000
#define FLAVOR_PUSH_TIME 7*2*1000 
#define MOTOR_SPEED 255
#define WAIT_TIME 5*1000

//Relay *pumps[2];
Relay pump1(2, true);
Relay pump2(4, true);
Relay milk_pump_relay(7, true);

Stepper_Motor_Driver turntable_stepper(8, 12, 3);
LimitSwitch turntable_reset_switch(A0);

DC_Motor_Driver flavor_push_motor(13, 5, 6);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    String token = Serial.readStringUntil('\n');
    if (token.equals("Tea_Distribution:0")) {
      pump1.on();
      delay(PUMP_TIME);
      pump1.off();

      delay(WAIT_TIME);

      Serial.println("Tea_Distributed");
    }

    if (token.equals("Tea_Distribution:1")) {
      pump2.on();
      delay(PUMP_TIME);
      pump2.off();

      delay(WAIT_TIME);

      Serial.println("Tea_Distributed");
    }

    if (token.equals("Flavor_Distribution:0")) {      
        dispense_flavors();
        /*flavor_push_motor.drive_clockwise(MOTOR_SPEED);
        delay(FLAVOR_PUSH_TIME); //time to get off limit_switch
        flavor_push_motor.drive_counter_clockwise(MOTOR_SPEED);
        delay(FLAVOR_PUSH_TIME);*/
        Serial.println("Flavor_Distributed");
    }

    if (token.equals("Reset_Actuator")) {
        flavor_push_motor.drive_counter_clockwise(MOTOR_SPEED);
        delay(FLAVOR_PUSH_TIME);

        Serial.println("Reset");
    }

    if (token.equals("Milk_Distribution")) {
        dispense_milk();

        Serial.println("Milk_Distributed");
    }
  }
}

void dispense_flavors() {
  //home motor first
  //reset_turntable_motor();
    push_flavor_start();
  //turntable_stepper.step_clockwise(100);
  for(int i = 0; i < 1; i++) {
    push_flavor_middle();
  }
    push_flavor_end();
  //reset_turntable_motor();
}

void push_flavor_start() {
    int FLAVOR_PUSH_TIME_UP = 5*1000;
    int FLAVOR_PUSH_TIME_DOWN = 14*1000;
    flavor_push_motor.drive_clockwise(MOTOR_SPEED);
    delay(FLAVOR_PUSH_TIME_DOWN); //time to get off limit_switch
    flavor_push_motor.drive_counter_clockwise(MOTOR_SPEED);
    delay(FLAVOR_PUSH_TIME_UP);
}
void push_flavor_middle(){
    int FLAVOR_PUSH_TIME_UP = 5*1000;
    int FLAVOR_PUSH_TIME_DOWN = 5*1000;
    flavor_push_motor.drive_clockwise(MOTOR_SPEED);
    delay(FLAVOR_PUSH_TIME_DOWN); //time to get off limit_switch
    flavor_push_motor.drive_counter_clockwise(MOTOR_SPEED);
    delay(FLAVOR_PUSH_TIME_UP);
}
void push_flavor_end(){
    int FLAVOR_PUSH_TIME_UP = 14*1000;
    int FLAVOR_PUSH_TIME_DOWN = 5*1000;
    flavor_push_motor.drive_clockwise(MOTOR_SPEED);
    delay(FLAVOR_PUSH_TIME_DOWN); //time to get off limit_switch
    flavor_push_motor.drive_counter_clockwise(MOTOR_SPEED);
    delay(FLAVOR_PUSH_TIME_UP);
}

void reset_turntable_motor() {
  Serial.print("Before reset");
  while(turntable_reset_switch.is_pressed() == false) {
    turntable_stepper.step_counter_clockwise(1);  
  }
  Serial.print("turntable_reset");
}

void dispense_milk() {
  milk_pump_relay.on();
  delay(MILK_PUMP_TIME);
  milk_pump_relay.off();
  delay(WAIT_TIME);
}
