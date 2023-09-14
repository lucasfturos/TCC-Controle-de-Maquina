/*
 * File:   UART.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:40
 */

#ifndef UART_H
#define UART_H

#include "setup.h"

// Declaração das funções
char UART_Read();
char UART_Data_Ready();
void UART_Write(char data);
void UART_Write_Text(char *text);
void UART_Init(const long int baudrate);

#endif /* UART_H */
