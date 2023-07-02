/* 
 * File:   UART.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:40
 */

#ifndef UART_H
#define	UART_H

#include "setup.h"

void UART_Init(const long int baundrate);

void UART_Write(char data);

char UART_Read();

#endif	/* UART_H */

