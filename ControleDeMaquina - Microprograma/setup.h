/* 
 * File:   setup.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:34
 */
#ifndef SETUP_H
#define	SETUP_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#pragma config FOSC = HS   // Oscilador externo de alta velocidade
#pragma config WDTE = OFF  // Desabilitar Watchdog Timer
#pragma config PWRTE = OFF // Desabilitar Power-Up Timer
#pragma config BOREN = OFF // Desabilitar Brown-out Reset
#pragma config LVP = OFF   // Desabilitar Low-Voltage Programming

#define _XTAL_FREQ 8000000  // Frequência do oscilador (8MHz)
#define BAUD_RATE 9600      // Taxa de transmissão serial (bps)

// Header
#include "lcd.h"

#endif	/* SETUP_H */