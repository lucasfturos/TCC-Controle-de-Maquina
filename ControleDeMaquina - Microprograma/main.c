/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "lcd.h"
#include "UART.h"


void uart_show() {
    TRISDbits.TRISD0 = 0; // Define a porta D0 como saída (LED)
    PORTDbits.RD0 = 0; // Inicialmente, desliga o LED

    UART_Init(9600); // Inicializa a comunicação serial

    while (1) {
        char data = UART_Read(); // Lê o byte recebido pela porta serial
        if (data == '1') {
            PORTDbits.RD0 = 1; // Liga o LED
            UART_Write('L'); // Envia uma confirmação de recebimento
        } else if (data == '0') {
            PORTDbits.RD0 = 0; // Desliga o LED
            UART_Write('M'); // Envia uma confirmação de recebimento
        }
    }
}

void lcd_show() {
    LCD_Init();
    LCD_Clear(); // Limpa o display
    LCD_SetCursor(2,6);
    LCD_WriteString("Hello, LCD!"); // Escreve uma string no LCD
    while (1) {

    }
}

void main(void) {
    //uart_show();
    lcd_show();
}
