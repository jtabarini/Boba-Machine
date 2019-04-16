/*
 * Can only be used for input
 * A0 - tea_stop
 * A1 - flavor_stop
 * A2 - boba_stop
 * A3 - end_stop
 * A4 - reset_stop
 * A5 - cup_sensor
 * 
 * PORTS 0 and 1 i think can't be used during operation because of
 *  serial communication over the usb
 *  
 * Digital Write/Read pins
 * 2 - assembly_line_motor in1
 * 4 - assembly_line_motor in2
 * 7 - cup_holder_filled
 * 8 - 
 * 12 - 
 * 13 - 
 * 
 * PWM pins
 * 3 - assembly_line_motor en
 * 5 - 
 * 6 - 
 * 10 - 
 * 11 - 
 */

#include "Relay.h"
#include "DC_Motor_Driver.h"
#include "Stepper_Motor_Driver.h"
#include "LimitSwitch.h"

#define MOTOR_SPEED 150

DC_Motor_Driver assembly_line_motor(2,4,3);

LimitSwitch tea_stop(A0);
LimitSwitch flavor_stop(A1);
LimitSwitch boba_stop(A2);
LimitSwitch end_stop(A3);
LimitSwitch reset_stop(A4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /*
   * add a cup holder start limit switch to beginning
   * add a cup holder end limit switch to end
   */
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    String token = Serial.readStringUntil('\n');
    if (token.equals("Start_To_Tea")) {      
      go_to_dest(tea_stop);

      Serial.println("Pour_Tea");

    } else if(token.equals("Tea_To_Flavor")) {
      go_to_dest(flavor_stop);   
      
      Serial.println("Pour_Flavor");
         
    } else if(token.equals("Flavor_To_Boba")) {
      go_to_dest(boba_stop);
              
      Serial.println("Pour_Boba");

    } else if(token.equals("Boba_To_End")) {
      go_to_dest(end_stop);

      Serial.println("Mdon't say picked_up");

    } else if(token.equals("Picked_Up")) {
      //do NOT use go_to_dest function here it needs to go backwards
      assembly_line_motor.drive_counter_clockwise(MOTOR_SPEED);
      Serial.print(analogRead(A4));
      while(reset_stop.is_pressed() == false) {

      //while(true) {
      }
      assembly_line_motor.brake_motor();

      Serial.println("Reset_Complete");
    }
  }
}

void go_to_dest(LimitSwitch stop_switch) {
  assembly_line_motor.drive_clockwise(MOTOR_SPEED);
  while(stop_switch.is_pressed() == false && end_stop.is_pressed() == false) {
  }
  
  assembly_line_motor.brake_motor();
}
