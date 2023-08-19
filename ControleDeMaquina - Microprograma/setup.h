/* 
 * File:   setup.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:34
 */
#ifndef SETUP_H
#define	SETUP_H

#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>
#include <stdint.h>

#pragma config FOSC = HS   // Oscilador externo de alta velocidade
#pragma config WDTE = OFF  // Desabilitar Watchdog Timer
#pragma config PWRTE = OFF // Desabilitar Power-Up Timer
#pragma config BOREN = OFF // Desabilitar Brown-out Reset
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON
#pragma config LVP = OFF   // Desabilitar Low-Voltage Programming
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000  // Frequência do oscilador (4MHz)

#endif	/* SETUP_H */