#include "step.h"

// Função que define um atraso entre os passos do motor de passo com base na RPM
// e no número de passos.

void Stepper_Delay(unsigned nsteps, char rpm) {
    // Configurar o Timer 1 como temporizador de 16 bits
    T1CON = 0x01; // Ativar o Timer 1 com prescaler 1:1

    // Calcula o valor de contagem para o atraso com base na RPM e no número de
    // passos.
    unsigned int delayCount = (unsigned int) ((float) (60000) / (nsteps * rpm));

    // Configura o valor inicial do Timer 1
    TMR1H = delayCount >> 8; // Parte alta
    TMR1L = delayCount; // Parte baixa

    // Aguarda a interrupção do Timer 1
    while (!TMR1IF);

    // Limpa a flag de interrupção do Timer 1
    TMR1IF = 0;
}

// Função que realiza um passo do motor de passo na direção especificada.

void Stepper_Step(uint8_t dir) {
    static int step_count = 0;
    char value = "";
    int len = sizeof (FullStep) / sizeof (FullStep[0]);

    // Incrementa ou decrementa o contador de passos com base na direção.
    if (dir == RIGHT) {
        step_count++;
        if (step_count >= len - 1) {
            step_count = 0; // Volta para o início da sequência
        }
        value = FullStep[step_count + 1];
        IN4 = (value & 0x01) ? 1 : 0;
        IN3 = (value & 0x02) ? 1 : 0;
        IN2 = (value & 0x04) ? 1 : 0;
        IN1 = (value & 0x08) ? 1 : 0;
    } else if (dir == LEFT) {
        step_count--;
        if (step_count < 0) {
            step_count = len - 1; // Vai para o final da sequência
        }
        value = FullStep[step_count + 1];
        IN1 = (value & 0x01) ? 1 : 0;
        IN2 = (value & 0x02) ? 1 : 0;
        IN3 = (value & 0x04) ? 1 : 0;
        IN4 = (value & 0x08) ? 1 : 0;
    }
}
