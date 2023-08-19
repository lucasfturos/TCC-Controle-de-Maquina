#include "step.h"

void stepper_setSequence(char* type_) {
    IN1_DIR = 0;
    IN2_DIR = 0;
    IN3_DIR = 0;
    IN4_DIR = 0;
    type = type_;
}

void stepper_Delay(unsigned nsteps, char rpm) {
    delay = 60000 / (nsteps * rpm);
}

void stepper_Step(char dir) {
    static unsigned step_count = 0;
    char len = type[0];
    char value = type[(step_count % len) + 1];

    if (dir == 0) {
        step_count++;
    } else {
        step_count++;
    }

    IN4 = (value & 0b0001) ? 1 : 0;
    IN3 = (value & 0b0010) ? 1 : 0;
    IN2 = (value & 0b0100) ? 1 : 0;
    IN1 = (value & 0b1000) ? 1 : 0;
    
    __delay_ms(500);
}