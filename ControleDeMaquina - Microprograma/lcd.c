/*
 * File:   lcd.c
 * Author: LucasTuros
 *
 * Created on 14 de Junho de 2023, 21:51
 */

#include "lcd.h"

// Inicializa o m�dulo LCD
void init() {
    ADCON1 = 0x07;    // Configura os pinos anal�gicos como digitais
    RA1 = 1;          // Define o pino RA1 como sa�da
    CTRL_PORT = 0x00; // Configura a porta de controle como sa�da
    DATA_PORT = 0x00; // Configura a porta de dados como sa�da
}

// Habilita o LCD
void LCD_Enable() {
    LCD_RS = 0x00;    // Define RS como comando
    LCD_RW = 0x00;    // Define RW como escrita
    LCD_EN = 0x00;    // Desativa o pino Enable
    __delay_us(5000); // Atraso de 0.005s antes de ativar o pino Enable
    LCD_EN = 0x01;    // Ativa o pino Enable para executar o comando
}

// Inicializa o LCD
void LCD_Init() {
    init();       // Inicializa os pinos e configura��es necess�rias
    PORTD = 0x01; // Envia comando de limpeza inicial
    LCD_Enable();
    PORTD = 0x38; // Envia comando de inicializa��o
    LCD_Enable();
    PORTD = 0x0E; // Configura o LCD para exibir e piscar o cursor
    LCD_Enable();
    PORTD =
        0x06; // Configura o cursor para se mover para a direita ap�s a escrita
    LCD_Enable();
    PORTD = 0x80; // Define a posi��o inicial do cursor
    LCD_Enable();
}

// Limpa o conte�do do LCD
void LCD_Clear() {
    PORTD = 0x01;  // Envia comando de limpeza
    LCD_RS = 0x00; // Define RS como comando
    LCD_RW = 0x00; // Define RW como escrita
    LCD_EN = 0x00; // Desativa o pino Enable
    __delay_us(5000);
    LCD_EN = 0x01; // Ativa o pino Enable para executar o comando
}

// Envia um comando para o LCD.
static void LCD_SendCMD(uint8_t cmd) {
    PORTD = cmd;   // Envia o comando para o LCD
    LCD_RS = 0x00; // Define RS como comando
    LCD_RW = 0x00; // Define RW como escrita
    LCD_Enable();
}

// Escreve um caractere no LCD
void LCD_Write_Char(char c) {
    PORTD = c;     // Envia o caractere para o LCD
    LCD_RS = 0x01; // Define RS como dado
    LCD_RW = 0x00; // Define RW como escrita
    LCD_EN = 0x00; // Desativa o pino Enable
    __delay_us(5000);
    LCD_EN = 0x01; // Ativa o pino Enable para executar o comando
}

// Escreve uma string no LCD
void LCD_Write_Text(char *s) {
    while (*s) {
        LCD_Write_Char(*s++); // Escreve cada caractere da string
    }
}

// Define a posi��o do cursor no LCD
void LCD_SetCursor(uint8_t row, uint8_t col) {
    if ((row == 1 || row == 2) && (col >= 1 && col <= 16)) {
        uint8_t address = (row - 1) * 0x40 +
                          (col - 1); // Calcula o endere�o de mem�ria do LCD
        LCD_SendCMD(
            0x80 | address); // Envia o comando para definir a posi��o do cursor
    }
}
