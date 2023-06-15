/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "UART.h"
#include "lcd.h"

void uart_show() {
    TRISBbits.TRISB1 = 0; // Define a porta B1 como saída (LED)
    PORTBbits.RB1 = 0; // Inicialmente, desliga o LED

    UART_Init(); // Inicializa a comunicação serial

    while (1) {
        char data = UART_Read(); // Lê o byte recebido pela porta serial
        if (data == '1') {
            PORTBbits.RB1 = 1; // Liga o LED
            UART_Write('led1'); // Envia uma confirmação de recebimento
        } else if (data == '0') {
            PORTBbits.RB1 = 0; // Desliga o LED
            UART_Write('led0'); // Envia uma confirmação de recebimento
        }
    }
}

void main(void) {
    unsigned int a;
    LCD_Init();
    while (1) {
        LCD_Clear();
        LCD_Set_Cursor(1, 1);
        LCD_Write_String("LCD Library for");
        __delay_ms(2000);
        LCD_Clear();
        LCD_Set_Cursor(1, 1);
        LCD_Write_String("Developed By");
        LCD_Set_Cursor(2, 1);
        LCD_Write_String("Lucas");
        __delay_ms(2000);
    }
}
