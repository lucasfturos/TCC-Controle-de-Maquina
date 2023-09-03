#include "step.h"

// Função para configurar a sequência de pinos para o motor de passo.
void Stepper_SetSequence(char *type_) {
    IN1_DIR = 0;
    IN2_DIR = 0;
    IN3_DIR = 0;
    IN4_DIR = 0;
    type = type_;
}

// Função que define um atraso entre os passos do motor de passo com base na RPM
// e no número de passos.
void Stepper_Delay(unsigned nsteps, char rpm) {
    // Configurar o Timer 1 como temporizador de 16 bits
    T1CON = 0x01; // Ativar o Timer 1 com prescaler 1:1

    // Calcula o valor de contagem para o atraso com base na RPM e no número de
    // passos.
    unsigned int delayCount = (unsigned int)((float)(60000) / (nsteps * rpm));

    // Configura o valor inicial do Timer 1
    TMR1H = delayCount >> 8; // Parte alta
    TMR1L = delayCount;      // Parte baixa

    // Aguarda a interrupção do Timer 1
    while (!TMR1IF);

    // Limpa a flag de interrupção do Timer 1
    TMR1IF = 0;
}

// Função que realiza um passo do motor de passo na direção especificada.
void Stepper_Step(uint8_t dir) {
    static unsigned step_count =
        0;              // Contador de passos, mantém o estado atual do motor.
    char len = type[0]; // Obtém o comprimento da sequência do motor.
    char value = type[(step_count % len) + 1];

    // Incrementa ou decrementa o contador de passos com base na direção.
    dir == RIGHT ? step_count++ : step_count--;

    IN4 = (value & 0x01) ? 1 : 0;
    IN3 = (value & 0x02) ? 1 : 0;
    IN2 = (value & 0x04) ? 1 : 0;
    IN1 = (value & 0x08) ? 1 : 0;
}
