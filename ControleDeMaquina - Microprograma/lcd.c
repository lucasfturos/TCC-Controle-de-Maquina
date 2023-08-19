/*
 * File:   lcd.c
 * Author: LucasTuros
 *
 * Created on 14 de Junho de 2023, 21:51
 */
#include "lcd.h"

void init() {
    ADCON1 = 0x07;
    RA1 = 1;
    CTRL_PORT = 0x00;
    DATA_PORT = 0x00;
}

void LCD_Enable() {
    LCD_RS = 0;                     
	LCD_RW = 0;                     
	LCD_EN = 0;                      
    __delay_us(5000);
	LCD_EN = 1;  
}

void LCD_Init() {
    init();
    PORTD = 0X1;
    LCD_Enable();
    PORTD = 0X38;
    LCD_Enable();
    PORTD = 0X0e;
    LCD_Enable();
    PORTD = 0X06;
    LCD_Enable();
    PORTD = 0X80;
    LCD_Enable();
}

void LCD_Clear() {
    PORTD = 0x01;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    __delay_us(5000);
    LCD_EN = 1;
}

static void LCD_SendCommand(uint8_t cmd) {
    PORTD = cmd;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_Enable();
}

void LCD_WriteChar(char c) {
   PORTD = c;                   
	LCD_RS = 1;                      
	LCD_RW = 0;                      
	LCD_EN = 0;                       
    __delay_us(5000);
	LCD_EN = 1;   
}

void LCD_WriteString(char *s) {
    while(*s){
        LCD_WriteChar(*s++);
    }
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    if ((row == 1 || row == 2) && (col >= 1 && col <= 16)) {
        uint8_t address = (row - 1) * 0x40 + (col - 1);
        LCD_SendCommand(0x80 | address);
    }
}