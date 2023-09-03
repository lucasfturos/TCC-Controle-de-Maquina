/*
 * File:   main.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:32
 */

#include "UART.h"
#include "lcd.h"
#include "step.h"

// Macros das mensagens
#define MESSAGE_TYPE_LCD '!'
#define MESSAGE_TYPE_LED '1'
#define MESSAGE_TYPE_MOTOR 'M'
#define MESSAGE_TYPE_STEPER 'S'

// Função para as configurações iniciais
void setupConfigs() {
    // UART
    nRBPU = 0;
    UART_Init(9600); // Baudrate 9600
    // Motor de passo
    Stepper_SetSequence(FullStep); // Define a sequência de passos completo
    // Motor DC
    TRISCbits.TRISC4 = 0; // Define a porta D0 como saída (Motor)
    PORTCbits.RC4 = 0;    // Inicialmente, desliga o Motor
    // LED
    TRISCbits.TRISC1 = 0; // Define a porta D0 como saída (LED)
    PORTCbits.RC1 = 1;    // Inicialmente, desliga o LED
    // LCD
    LCD_Init(); // Inicializa o display
    LCD_Clear();
}

// Função para controle do LED
void showLED() {
    char data = UART_Read(); // Lê o byte recebido pela porta serial
    if (data == '1') {
        PORTCbits.RC1 = 0; // Liga o LED
        UART_Write('O');   // Envia uma confirmação de recebimento
    } else if (data == '0') {
        PORTCbits.RC1 = 1; // Desliga o LED
        UART_Write('M');   // Envia uma confirmação de recebimento
    }
}

// Função para controle do Motor DC
void runMotorDC() {
    char data = UART_Read();
    if (data == 'D') {
        PORTCbits.RC4 = 1; // Liga o Motor
        UART_Write('D');   // Envia uma confirmação de recebimento
    } else if (data == 'C') {
        PORTCbits.RC4 = 0; // Desliga o Motor
        UART_Write('D');   // Envia uma confirmação de recebimento
    }
}

// Função para controle do Motor de Passo
void runStepper() {
    Stepper_Step(RIGHT);
    Stepper_Delay(32, 1);
}

void main(void) {
    char response, text[33], line1[17], line2[17];
    uint8_t textIndex, onDisplay = 0, cmdLCD = 0;

    setupConfigs(); // Configurações iniciais
    while (1) {
        if (UART_Data_Ready()) { // Verifica se há dados prontos para leitura no
                                 // UART
            response = UART_Read(); // Lê o caractere recebido
            if (MESSAGE_TYPE_LCD == response) {
                if (!onDisplay) { // Se o display não estiver ativado, ativa e
                                  // inicializa
                    onDisplay = 1;
                    cmdLCD = 1;
                    UART_Write_Text("LCD"); // Envia confirmação para o UART
                    LCD_Clear();
                    LCD_SetCursor(1, 1); // Posiciona o cursor na primeira
                                         // linha, primeira coluna
                    textIndex = 0;
                    text[0] = '\0';  // Limpa o buffer de texto
                    line1[0] = '\0'; // Limpa a primeira linha
                    line2[0] = '\0'; // Limpa a segunda linha
                }
            } else if (cmdLCD) { // Se o display estiver ativado
                if (response ==
                    ';') {         // Caractere ';' indica o final do comando
                    onDisplay = 0; // Desativa o display
                    cmdLCD = 0;
                    text[textIndex] = '\0'; // Encerra o texto
                    LCD_Clear();

                    // Escreve o texto completo no LCD, dividindo-o entre as
                    // duas linhas
                    if (textIndex <= 32) {
                        LCD_Write_Text(line1); // Escreve a primeira linha
                        LCD_SetCursor(2,
                                      1); // Move o cursor para a segunda linha
                        LCD_Write_Text(line2); // Escreve a segunda linha
                    }
                } else {
                    if (textIndex < 32) { // Evita estouro de buffer
                        text[textIndex++] =
                            response; // Adiciona o caractere ao buffer de texto
                        if (textIndex == 16) {
                            text[textIndex] = '\0'; // Encerra a primeira linha
                            strcpy(line1, text);    // Copia a primeira linha
                            line1[16] = '\0';       // Encerra a primeira linha
                            line2[0] = '\0';        // Limpa a segunda linha
                        } else if (textIndex > 16) {
                            line2[textIndex - 17] =
                                response; // Adiciona o caractere à segunda
                                          // linha
                            line2[textIndex - 16] =
                                '\0'; // Encerra a segunda linha
                        }
                        LCD_Write_Char(response); // Escreve o caractere no LCD
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
                UART_Write_Text(
                    "Erro"); // Mensagem de erro se o comando for desconhecido
                break;
            }
        }
    }
}
