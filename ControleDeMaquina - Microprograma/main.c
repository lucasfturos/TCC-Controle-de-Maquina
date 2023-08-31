/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "UART.h"
#include "lcd.h"
#include "step.h"

#define MESSAGE_TYPE_LCD '!'
#define MESSAGE_TYPE_LED '1'
#define MESSAGE_TYPE_TEXT 'T'
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

void showLED() {
    char data = UART_Read(); // Lê o byte recebido pela porta serial
    if (data == '1') {
        PORTCbits.RC1 = 0; // Liga o LED
        UART_Write('O'); // Envia uma confirmação de recebimento
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
    char lcdText[16]; // Para armazenar o texto do LCD
    uint8_t lcdTextIndex = 0; // Índice para o próximo caractere no lcdText
    uint8_t lcdTextMode = 0; // Variável para indicar quando inserir texto no LCD

    while (1) {
        if (UART_Data_Ready()) {
            char receivedChar = UART_Read();
            // Verifica o tipo de mensagem recebida
            switch (receivedChar) {
                case MESSAGE_TYPE_LCD:
                    UART_Write_Text("LCD");
                    lcdTextMode = 1; // Ativa o modo de inserção de texto no LCD
                    lcdTextIndex = 0; // Reinicia o índice do texto do LCD
                    LCD_Clear(); // Limpa o LCD
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
                    lcdTextMode = 0; // Desativa o modo de inserção de texto no LCD
                    runStepper();
                    break;
                case MESSAGE_TYPE_TEXT:
                    lcdTextMode = 1; // Ativa o modo de inserção de texto no LCD
                    lcdTextIndex = 0; // Reinicia o índice do texto do LCD
                    break;
                default:
                    // Verifica se o modo de inserção de texto no LCD está ativado
                    if (lcdTextMode && lcdTextIndex < sizeof (lcdText) - 1) {
                        if (lcdTextIndex == 0 && receivedChar == '!') {
                            lcdTextIndex = 0; // Reseta o índice do texto do LCD
                        } else {
                            lcdText[lcdTextIndex++] = receivedChar; // Adiciona o caractere ao buffer
                            lcdText[lcdTextIndex] = '\0'; // Adiciona o terminador de string
                            LCD_Clear(); // Limpa o LCD
                            LCD_SetCursor(1, 1); // Move o cursor para a primeira posição
                            LCD_WriteString(lcdText); // Escreve o texto no LCD
                        }
                    }
                    break;
            }
        }
    }
}