/*
 * This is a very simple servo control algorithm, designed to use the Motor shield library
 * but easily portable to other situations. (but serously consider a PID loop...)
 * It uses two "stages" to better control a servo. The first stage quickly moves the servo
 * close to the setpoint, then the second stage finishes moving it to the exact point.  
 */

#include <AFMotor.h>

AF_DCMotor servo(1);

// in case servo is wired backwards
#define SV_DECREASE BACKWARD
#define SV_INCREASE FORWARD

// stage-specific settings
#define DEADZONE_1 100
#define DEADZONE_2 5
#define VEL_1 170
#define VEL_2 60

#define DEBUG 0

int target = 500;

String inString = "";

void setup() {
  // put your setup code here, to run once:
    pinMode(A6, INPUT);
    Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
#if DEBUG
    Serial.println(analogRead(A6));
#endif    
    serial_parse();
    stupid_simple_servo_ctrl();
}

// serial parser code picked from arduino website
void serial_parse() { 
    // Read serial input:
    while (Serial.available() > 0) {
        int inChar = Serial.read();
        if (isDigit(inChar)) {
            // convert the incoming byte to a char and add it to the string:
            inString += (char)inChar;
        }
        // if you get a newline, print the string, then the string's value:
        if (inChar == '\n') {
            target = inString.toInt();
            inString = "";
        }
    }
}

void stupid_simple_servo_ctrl() {
    int svPos = analogRead(A6);
    byte deadzone;

    // Change to stage 2 if CV is within DEADZONE_1 of SP
    if (abs(svPos - target) > DEADZONE_1) {
        deadzone = DEADZONE_1;
        servo.setSpeed(VEL_1);
    }
    else {
        deadzone = DEADZONE_2;
        servo.setSpeed(VEL_2);
    }

    // Move back or forward when needed
    if (svPos > target + deadzone) {
        servo.run(SV_DECREASE);
    }
    else if (svPos < target - deadzone) {
        servo.run(SV_INCREASE);
    }
    else servo.run(RELEASE);
}

