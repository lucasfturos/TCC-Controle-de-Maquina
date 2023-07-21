/* 
 * File:   lcd.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:39
 */

#ifndef LCD_H
#define LCD_H

#include "setup.h"

#define LCD_RS RE0
#define LCD_RW RE1
#define LCD_EN RE2

#define DATA_PORT  TRISD // Define porta de dados
#define CTRL_PORT  TRISE // Define porta de controle

void init();
void LCD_Init();
void LCD_Clear();
void LCD_Enable();
void LCD_Linha1();
void LCD_Linha2();
void LCD_WriteChar(char c);
void LCD_WriteString(char *s);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif	/* LCD_H */
