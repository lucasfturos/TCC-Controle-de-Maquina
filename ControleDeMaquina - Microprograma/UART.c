/*
 * File:   UART.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:48
 */

#include "UART.h"

void UART_Init(unsigned int baudrate) {
    TRISCbits.TRISC6 = 0; // Define o pino RC6 como sa�da (TX)
    TRISCbits.TRISC7 = 1; // Define o pino RC7 como entrada (RX)

    // Configura��o do registrador SPBRG para a taxa de transmiss�o desejada
    SPBRG = (_XTAL_FREQ / (16 * (unsigned int) baudrate)) - 1;
    // Configura��o do registrador TXSTA (baixa velocidade de transmiss�o,
    // habilita transmiss�o)
    TXSTA = 0x24;
    // Configura��o do registrador RCSTA (habilita porta serial, habilita
    // recep��o cont�nua)
    RCSTA = 0x90;
}

void UART_Write(char data) {
    while (!TXIF)
        ; // Aguarda o buffer de transmiss�o estar vazio
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
        CREN = 1; // Reabilita a recep��o
    }
    while (!RCIF) { // Aguarda a recep��o de dados
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
