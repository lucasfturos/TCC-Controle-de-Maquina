/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "UART.h"
#include "lcd.h"
#include "step.h"

#define MESSAGE_TYPE_LCD 'L'
#define MESSAGE_TYPE_LED '1'
#define MESSAGE_TYPE_MOTOR 'M'
#define MESSAGE_TYPE_STEPER 'S'

void setupConfigs() {
    // UART
    UART_Init(9600); // Inicializa a comunicação serial
    // Motor de passo
    stepper_Delay(72, 2);
    stepper_setSequence(FullStep);
    // Motor DC
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;
    // LED
    TRISCbits.TRISC1 = 0; // Define a porta D0 como saída (LED)
    PORTCbits.RC1 = 1;    // Inicialmente, desliga o LED
    // LCD
    LCD_Init();
}

void showLCD() {
    LCD_Clear();
    LCD_SetCursor(2, 1);
    //    char str[17]; // Para armazenar uma string de até 16 caracteres +
    //    terminador nulo UART_Read_Text(str); // Lê a string da comunicação
    //    serial
    LCD_WriteString("Ola Mundo"); // Escreve a string no LCD
}

void showLED() {
    char data = UART_Read(); // Lê o byte recebido pela porta serial
    if (data == '1') {
        PORTCbits.RC1 = 0; // Liga o LED
        UART_Write('L');   // Envia uma confirmação de recebimento
    } else if (data == '0') {
        PORTCbits.RC1 = 1; // Desliga o LED
        UART_Write('M');   // Envia uma confirmação de recebimento
    }
}

void runMotorDC() {
    char data = UART_Read();
    if (data == 'D') {
        PORTCbits.RC4 = 1;
        UART_Write('D');
    } else if (data == 'C') {
        PORTCbits.RC4 = 0;
        UART_Write('D');
    }
}

void main(void) {
    setupConfigs();
    showLCD();

    while (1) {
        stepper_Step(RIGHT);
        //        char message_type = UART_Read();
        //        switch (message_type) {
        //            case MESSAGE_TYPE_LCD:
        //                break;
        //            case MESSAGE_TYPE_LED:
        //                showLED();
        //                break;
        //            case MESSAGE_TYPE_MOTOR:
        //                runMotorDC();
        //                break;
        //            default:
        //                // Mensagem não reconhecida, enviar resposta de erro
        //                UART_Write('E');
        //                break;
        //        }
    }
}
