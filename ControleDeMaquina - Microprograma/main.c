/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "UART.h"
//#include "lcd.h"

void uart_show() {
    TRISDbits.TRISD0 = 0; // Define a porta D0 como saída (LED)
    PORTDbits.RD0 = 0; // Inicialmente, desliga o LED
    
    UART_Init(); // Inicializa a comunicação serial

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

//void lcd_show() {
//    LCD_Init();
//    while (1) {
//        LCD_Clear(); // Limpa o display
//        LCD_Set_Cursor(1, 1); // Define a posição do cursor na primeira linha, primeira coluna
//        LCD_Write_String("LCD Library for");
//        __delay_ms(2000);
//        LCD_Clear(); // Limpa o display novamente
//        LCD_Set_Cursor(1, 1); // Define a posição do cursor na primeira linha, primeira coluna
//        LCD_Write_String("Developed By");
//        LCD_Set_Cursor(2, 1); // Define a posição do cursor na segunda linha, primeira coluna
//        LCD_Write_String("Lucas");
//        __delay_ms(2000);
//
//    }
//}

void main(void) {
    uart_show();
}
