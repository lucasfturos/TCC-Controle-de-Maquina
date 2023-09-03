/*
 * File:   UART.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:48
 */

#include "UART.h"

// Fun��o de inicializa��o do protocolo UART
void UART_Init(unsigned int baudrate) {
    // Configura��o dos pinos TX e RX
    TRISCbits.TRISC6 = 0; // Define o pino RC6 como sa�da (TX)
    TRISCbits.TRISC7 = 1; // Define o pino RC7 como entrada (RX)

    // Configura��o do registrador de taxa de transmiss�o
    SPBRG = (_XTAL_FREQ / (16 * (unsigned int)baudrate)) - 1;
    // Configura��o do registrador TXSTA (baixa velocidade de transmiss�o,
    // habilita transmiss�o)
    TXSTA = 0x24;
    // Configura��o do registrador RCSTA (habilita porta serial, habilita
    // recep��o cont�nua)
    RCSTA = 0x90;
}

// Fun��o de escrita de um caractere na porta serial UART para confirma��o
void UART_Write(char data) {
    while (!TXIF); // Aguarda o buffer de transmiss�o estar vazio
    TXREG = data;  // Envia o byte pela porta serial
}

// Fun��o de escrita de uma string na porta serial UART
void UART_Write_Text(char *str) {
    while (*str) {
        UART_Write(*str++);
    }
}

// Fun��o que l� um caractere da porta serial UART
char UART_Read() {
    if (OERR) {   // Verifica se houve erro de overflow
        CREN = 0; // Limpa o erro de overflow
        CREN = 1; // Reabilita a recep��o
    }
    while (!RCIF) { // Aguarda a recep��o de dados
        continue;
    }
    return RCREG; // Retorna o byte recebido
}

// Fun��o que verifica se h� dados prontos para leitura na porta serial UART
char UART_Data_Ready() {
    return RCIF; // Retorna verdadeiro se dados estiverem prontos para leitura
}

// Fun��o que l� texto da porta serial UART at� encontrar um caractere de nova
// linha '\n'
void UART_Read_Text(char *str) {
    char c;
    while (c != '\n') {
        c = UART_Read(); // L� um caractere da UART
        *str += c;       // Adiciona o caractere � string de destino
    }
}
