/* 
 * File:   lcd.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:39
 */

#ifndef LCD_H
#define	LCD_H

#include "setup.h"

#define LCD_RS         RE0
#define LCD_RW         RE1
#define LCD_EN         RE2

#define LCD_D4         RD4
#define LCD_D5         RD5
#define LCD_D6         RD6
#define LCD_D7         RD7

#define DATA_PORT_DIR  TRISD // Define porta de dados
#define CTRL_PORT_DIR  TRISE // Define porta de controle

void LCD_Init();
void LCD_Clear();
void LCD_CMD(char a);
void LCD_Port(char a);
void LCD_Write_Char(char a);
void LCD_Write_String(char *a);
void LCD_Set_Cursor(char a, char b);

#endif	/* LCD_H */