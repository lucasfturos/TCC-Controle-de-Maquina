/*
 * File:   UART.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:48
 */

#include "UART.h"

void UART_Init(unsigned int baudrate) {
    TRISCbits.TRISC6 = 0; // Define o pino RC6 como saída (TX)
    TRISCbits.TRISC7 = 1; // Define o pino RC7 como entrada (RX)

    // Configuração do registrador SPBRG para a taxa de transmissão desejada
    SPBRG = (_XTAL_FREQ / (16 * (unsigned int) baudrate)) - 1;
    // Configuração do registrador TXSTA (baixa velocidade de transmissão,
    // habilita transmissão)
    TXSTA = 0x24;
    // Configuração do registrador RCSTA (habilita porta serial, habilita
    // recepção contínua)
    RCSTA = 0x90;
}

void UART_Write(char data) {
    while (!TXIF)
        ; // Aguarda o buffer de transmissão estar vazio
    TXREG = data; // Envia o byte pela porta serial
}

void UART_Write_Text(char *str) {
    while (*str) {
        UART_Write(*str++);
    }
}

char UART_Read() {
    if (OERR) { // Verifica se houve erro de overflow
        CREN = 0; // Limpa o erro de overflow
        CREN = 1; // Reabilita a recepção
    }
    while (!RCIF) { // Aguarda a recepção de dados
        continue;
    }
    return RCREG; // Retorna o byte recebido
}

char UART_Data_Ready() {
    return RCIF;
}

void UART_Read_Text(char *str) {
    char c;
    while (c != '\n') {
        c = UART_Read();
        *str += c;
    }
}
