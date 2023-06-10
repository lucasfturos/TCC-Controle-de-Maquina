/* 
 * File:   UART.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 20:40
 */

#ifndef UART_H
#define	UART_H

#include "setup.h"

void UART_Init() {
    TRISCbits.TRISC6 = 0; // Define o pino RC6 como saída (TX)
    TRISCbits.TRISC7 = 1; // Define o pino RC7 como entrada (RX)

    SPBRG = (_XTAL_FREQ / (16 * BAUD_RATE)) - 1; // Configuração do registrador SPBRG para a taxa de transmissão desejada
    TXSTA = 0b00100100; // Configuração do registrador TXSTA (baixa velocidade de transmissão, habilita transmissão)
    RCSTA = 0b10010000; // Configuração do registrador RCSTA (habilita porta serial, habilita recepção contínua)
}

void UART_Write(char data) {
    while (!TXIF) { // Aguarda o buffer de transmissão estar vazio
        continue;
    }
    TXREG = data; // Envia o byte pela porta serial
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

#endif	/* UART_H */

