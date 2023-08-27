#include "step.h"

void Stepper_SetSequence(char *type_) {
    IN1_DIR = 0;
    IN2_DIR = 0;
    IN3_DIR = 0;
    IN4_DIR = 0;
    type = type_;
}

void Stepper_Delay(unsigned nsteps, char rpm) {
    // Configurar o Timer 1 como temporizador de 16 bits
    T1CON = 0x01; // Ativar o Timer 1 com prescaler 1:1

    // Calcula o valor de contagem para o atraso
    unsigned int delayCount = (unsigned int) ((float) (60000) / (nsteps * rpm));

    // Configura o valor inicial do Timer 1
    TMR1H = delayCount >> 8; // Parte alta
    TMR1L = delayCount; // Parte baixa

    // Aguarda a interrupção do Timer 1
    while (!TMR1IF);

    // Limpa a flag de interrupção do Timer 1
    TMR1IF = 0;
}

void Stepper_Step(char dir) {
    static unsigned step_count = 0;
    char len = type[0];
    char value = type[(step_count % len) + 1];

    dir == 0 ? step_count++ : step_count--;

    IN4 = (value & 0x01) ? 1 : 0;
    IN3 = (value & 0x02) ? 1 : 0;
    IN2 = (value & 0x04) ? 1 : 0;
    IN1 = (value & 0x08) ? 1 : 0;
}