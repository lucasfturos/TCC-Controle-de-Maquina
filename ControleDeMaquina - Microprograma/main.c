/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "UART.h"
#include "lcd.h"
#include "step.h"

// Macros do motor DC e LED
#define LED_INIT TRISCbits.TRISC1
#define MOTOR_INIT TRISCbits.TRISC4
#define LED_REG RC1
#define MOTOR_REG RC4

// Macros das mensagens
#define MESSAGE_TYPE_LCD '!'
#define MESSAGE_TYPE_LED '1'
#define MESSAGE_TYPE_MOTOR 'M'
#define MESSAGE_TYPE_STEPER 'S'

// Função para as configurações iniciais

void setupConfigs() {
    // UART
    UART_Init(9600); // Baudrate 9600
    // Motor de passo
    T1CON = 0x01;
    IN1_DIR = IN2_DIR = IN3_DIR = IN4_DIR = 0;
    // Motor DC
    MOTOR_INIT = 0; // Define a porta D0 como saída (Motor)
    MOTOR_REG = 0; // Inicialmente, desliga o Motor
    // LED
    LED_INIT = 0; // Define a porta D0 como saída (LED)
    LED_REG = 1; // Inicialmente, desliga o LED
    // LCD
    LCD_Init(); // Inicializa o display
    LCD_Clear();
}

// Função para controle do LED

void showLED() {
    char data = UART_Read(); // Lê o byte recebido pela porta serial
    if (data == '1') {
        LED_REG = 0; // Liga o LED
        UART_Write('O'); // Envia uma confirmação de recebimento
    } else if (data == '0') {
        LED_REG = 1; // Desliga o LED
        UART_Write('M'); // Envia uma confirmação de recebimento
    }
}

// Função para controle do Motor DC

void runMotorDC() {
    char data = UART_Read();
    if (data == 'D') {
        MOTOR_REG = 1; // Liga o Motor
        UART_Write('D'); // Envia uma confirmação de recebimento
    } else if (data == 'C') {
        MOTOR_REG = 0; // Desliga o Motor
        UART_Write('D'); // Envia uma confirmação de recebimento
    }
}

// Função para controle do Motor de Passo

void runStepper() {
    char data = UART_Read();
    if (data == 'L') {
        Stepper_Step(LEFT);
        Stepper_Delay(32, 1);
        UART_Write('L');
    } else if (data == 'R') {
        Stepper_Step(RIGHT);
        Stepper_Delay(32, 1);
        UART_Write('R');
    }
}

void main(void) {
    char response, text[33], line1[17], line2[17];
    uint8_t textIndex, onDisplay = 0, cmdLCD = 0;

    setupConfigs(); // Configurações iniciais
    LCD_Clear();
    LCD_SetCursor(1, 1);
    LCD_Write_Text("Bem vindo!");
    while (1) {
        if (UART_Data_Ready()) { // Verifica se há dados prontos para leitura no
            // UART
            response = UART_Read(); // Lê o caractere recebido
            if (response == MESSAGE_TYPE_LCD) {
                // Se o caractere '!' for recebido, ative o modo de comando do LCD
                onDisplay = 1;
                cmdLCD = 1;
                textIndex = 0;
                text[0] = '\0'; // Limpa o buffer de texto
                line1[0] = '\0'; // Limpa a primeira linha
                line2[0] = '\0'; // Limpa a segunda linha
                UART_Write_Text("LCD");
            } else if (onDisplay && response == ';') {
                // Se ';' for recebido, desative o modo de comando do LCD e escreva o texto no LCD
                onDisplay = 0;
                cmdLCD = 0;
                text[textIndex] = '\0'; // Encerra o texto
                LCD_Clear();
                LCD_SetCursor(1, 1);
                LCD_Write_Text(text); // Escreve o texto no LCD
                if (line2[0] != '\0') {
                    LCD_SetCursor(2, 1);
                    LCD_Write_Text(line2);
                }
            } else if (onDisplay) {
                // Se o modo de comando do LCD estiver ativado, adicione o caractere ao buffer de texto
                if (textIndex < 32) {
                    text[textIndex++] = response;
                    if (textIndex == 16) {
                        text[textIndex] = '\0'; // Encerra a primeira linha
                        uint8_t i = 0;
                        while (text[i] != '\0') {
                            line1[i] = text[i];
                            i++;
                        }
                        line1[16] = '\0'; // Encerra a primeira linha
                        line2[0] = '\0'; // Limpa a segunda linha
                    } else if (textIndex > 16) {
                        line2[textIndex - 17] = response;
                        line2[textIndex - 16] = '\0'; // Encerra a segunda linha
                    }
                }
            }
            switch (response) {
                case MESSAGE_TYPE_LED:
                    UART_Write_Text("LED"); // Envia confirmação do LED
                    showLED();
                    break;
                case MESSAGE_TYPE_MOTOR:
                    UART_Write_Text("DC"); // Envia confirmação do Motor DC
                    runMotorDC();
                    break;
                case MESSAGE_TYPE_STEPER:
                    UART_Write_Text("Step"); // Envia confirmação do Motor de Passo
                    runStepper();
                    break;
                default:
                    // Mensagem de erro se o comando for desconhecido
                    UART_Write_Text("Erro");
                    RCREG = 0;
                    break;
            }
        }
    }
}