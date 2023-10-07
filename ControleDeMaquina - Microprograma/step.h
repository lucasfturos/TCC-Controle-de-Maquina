/*
 * File:   step.h
 * Author: LucasTuros
 *
 * Created on 19 de Agosto de 2023, 13:02
 */

#ifndef STEP_H
#define STEP_H

#include "setup.h"

// Configura a sa�da do motor de passo
#define IN1 RB7
#define IN2 RB6
#define IN3 RB5
#define IN4 RB4

// Configura a dire��o dos pinos
#define IN1_DIR TRISBbits.TRISB7
#define IN2_DIR TRISBbits.TRISB6
#define IN3_DIR TRISBbits.TRISB5
#define IN4_DIR TRISBbits.TRISB4

// Dire��o do eixo
#define LEFT 1
#define RIGHT 0

char FullStep[] = {4, 0x03, 0x06, 0x0C, 0x09}; // Passos

// Declara��o das fun��es
void Stepper_Step(uint8_t dir);
void Stepper_Delay(unsigned nsteps, char rpm);

#endif /* STEP_H */
