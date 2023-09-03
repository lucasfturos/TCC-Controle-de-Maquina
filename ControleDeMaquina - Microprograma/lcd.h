/*
 * File:   lcd.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:39
 */

#ifndef LCD_H
#define LCD_H

#include "setup.h"

#define LCD_RS RE0 // Pino RS do LCD (Registro de Seleção)
#define LCD_RW RE1 // Pino RW do LCD (Registro de Escrita)
#define LCD_EN RE2 // Pino EN do LCD (Habilitação)

#define DATA_PORT TRISD // Define porta de dados
#define CTRL_PORT TRISE // Define porta de controle

// Declaração de funções
void init();
void LCD_Enable();
void LCD_Init();
void LCD_Clear();
void LCD_Write_Char(char c);
void LCD_Write_Text(char *s);
static void LCD_SendCMD(uint8_t cmd);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif /* LCD_H */
