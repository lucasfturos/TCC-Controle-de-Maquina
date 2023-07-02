/*
 * File:   UART.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:48
 */

#include "UART.h"

void UART_Init(const long int baundrate) {
    TRISCbits.TRISC6 = 0; // Define o pino RC6 como sa�da (TX)
    TRISCbits.TRISC7 = 1; // Define o pino RC7 como entrada (RX)

    SPBRG = (_XTAL_FREQ / (16 * baundrate)) - 1; // Configura��o do registrador SPBRG para a taxa de transmiss�o desejada
    TXSTA = 0b00100100; // Configura��o do registrador TXSTA (baixa velocidade de transmiss�o, habilita transmiss�o)
    RCSTA = 0b10010000; // Configura��o do registrador RCSTA (habilita porta serial, habilita recep��o cont�nua)
}

void UART_Write(char data) {
    while (!TXIF) { // Aguarda o buffer de transmiss�o estar vazio
        continue;
    }
    TXREG = data; // Envia o byte pela porta serial
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