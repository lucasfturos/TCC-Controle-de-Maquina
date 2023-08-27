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
    UART_Init(9600); // Baudrate 9600
    // Motor de passo
    Stepper_SetSequence(FullStep);
    // Motor DC
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;
    // LED
    TRISCbits.TRISC1 = 0; // Define a porta D0 como saída (LED)
    PORTCbits.RC1 = 1; // Inicialmente, desliga o LED
    // LCD
    LCD_Init();
    LCD_Clear();
}

void showLCD() {
    LCD_Clear();
    LCD_SetCursor(1, 1);

    while (UART_Read() != '\0') {
        LCD_WriteChar(UART_Read()); // Lê a string da comunicação serial
    }
}

void showLED() {
    char data = UART_Read(); // Lê o byte recebido pela porta serial
    if (data == '1') {
        PORTCbits.RC1 = 0; // Liga o LED
        UART_Write('L'); // Envia uma confirmação de recebimento
    } else if (data == '0') {
        PORTCbits.RC1 = 1; // Desliga o LED
        UART_Write('M'); // Envia uma confirmação de recebimento
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

void runStepper() {
    Stepper_Step(RIGHT);
    Stepper_Delay(32, 1);
}

void main(void) {
    setupConfigs();

    while (1) {
        char message_type = UART_Read();
        switch (message_type) {
            case MESSAGE_TYPE_LCD:
                UART_Write_Text("LCD");
                showLCD();
                break;
            case MESSAGE_TYPE_LED:
                UART_Write_Text("LED");
                showLED();
                break;
            case MESSAGE_TYPE_MOTOR:
                UART_Write_Text("DC");
                runMotorDC();
                break;
            case MESSAGE_TYPE_STEPER:
                UART_Write_Text("Step");
                // Baixa volta: SSSSSSSS
                // Média volta: SSSSSSSSSSSSSSSS
                // Alta volta: SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
                runStepper();
                break;
            default:
                // Mensagem não reconhecida
                UART_Write_Text("Erro");
                break;
        }
    }
}