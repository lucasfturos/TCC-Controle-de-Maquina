/*
 * File:   UART.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:48
 */

#include "UART.h"

// Fun��o de inicializa��o do protocolo UART
void UART_Init(const long int baudrate) {
    unsigned long x = (_XTAL_FREQ / (16 * baudrate)) - 1;
    SPBRG = x;
    TRISC7 = 1;
    TRISC6 = 1;
    TXSTAbits.BRGH = 1; // REQUIRED FOR HIGH BAUD RATE
    TXSTAbits.SYNC = 0; // For Asynchronous communication
    RCSTAbits.SPEN = 1; // Habilita UART
    RCSTAbits.CREN = 1; // Habilita RX continuo
    TXSTAbits.TXEN = 1; // Habilita TX
}

// Fun��o de escrita de um caractere na porta serial UART para confirma��o
void UART_Write(char data) {
    while (!TXIF)
        ;         // Aguarda o buffer de transmiss�o estar vazio
    TXREG = data; // Envia o byte pela porta serial
}

// Fun��o de escrita de uma string na porta serial UART
void UART_Write_Text(char *str) {
    while (*str) {
        UART_Write(*str++);
    }
}

// Fun��o que l� um caractere da porta serial UART
char UART_Read() {
    while (!RCIF)
        ;
    return RCREG;
}

// Fun��o que verifica se h� dados prontos para leitura na porta serial UART
char UART_Data_Ready() {
    return RCIF; // Retorna verdadeiro se dados estiverem prontos para leitura
}
