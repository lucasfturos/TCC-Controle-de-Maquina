/*
 * File:   lcd.c
 * Author: LucasTuros
 *
 * Created on 14 de Junho de 2023, 21:51
 */
#include "lcd.h"

void LCD_Port(char a) {
    LCD_D4 = (a >> 4) & 0x01;
    LCD_D5 = (a >> 5) & 0x01;
    LCD_D6 = (a >> 6) & 0x01;
    LCD_D7 = (a >> 7) & 0x01;
}

void LCD_CMD(char a) {
    LCD_RS = 0;
    LCD_EN = 1;
    LCD_Port(a);
    LCD_EN = 0;
    __delay_ms(1);
}

void LCD_Clear() {
    LCD_CMD(0);
    LCD_CMD(1);
}

void LCD_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        LCD_CMD(z);
        LCD_CMD(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        LCD_CMD(z);
        LCD_CMD(y);
    }
}

void LCD_Init() {
    TRISE = 0x00;
    TRISD = 0x00;

    LCD_Port(0x00);
    __delay_ms(20);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(11);
    LCD_CMD(0x03);

    LCD_CMD(0x02);
    LCD_CMD(0x02);
    LCD_CMD(0x08);
    LCD_CMD(0x00);
    LCD_CMD(0x0C);
    LCD_CMD(0x00);
    LCD_CMD(0x06);
}

void LCD_Write_Char(char a) {
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    LCD_RS = 1;
    LCD_Port(y >> 4);
    LCD_EN = 1;
    __delay_us(40);
    LCD_EN = 0;
    LCD_Port(temp);
    LCD_EN = 1;
    __delay_us(40);
    LCD_EN = 0;
}

void LCD_Write_String(char* a) {
    while (*a) {
        LCD_Write_Char(a++);
    }
}