/*
 * File:   UART.c
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:48
 */

#include "UART.h"

// Função de inicialização do protocolo UART
void UART_Init(unsigned int baudrate) {
    // Configuração dos pinos TX e RX
    TRISCbits.TRISC6 = 0; // Define o pino RC6 como saída (TX)
    TRISCbits.TRISC7 = 1; // Define o pino RC7 como entrada (RX)

    // Configuração do registrador de taxa de transmissão
    SPBRG = (_XTAL_FREQ / (16 * (unsigned int)baudrate)) - 1;
    // Configuração do registrador TXSTA (baixa velocidade de transmissão,
    // habilita transmissão)
    TXSTA = 0x24;
    // Configuração do registrador RCSTA (habilita porta serial, habilita
    // recepção contínua)
    RCSTA = 0x90;
}

// Função de escrita de um caractere na porta serial UART para confirmação
void UART_Write(char data) {
    while (!TXIF); // Aguarda o buffer de transmissão estar vazio
    TXREG = data;  // Envia o byte pela porta serial
}

// Função de escrita de uma string na porta serial UART
void UART_Write_Text(char *str) {
    while (*str) {
        UART_Write(*str++);
    }
}

// Função que lê um caractere da porta serial UART
char UART_Read() {
    if (OERR) {   // Verifica se houve erro de overflow
        CREN = 0; // Limpa o erro de overflow
        CREN = 1; // Reabilita a recepção
    }
    while (!RCIF) { // Aguarda a recepção de dados
        continue;
    }
    return RCREG; // Retorna o byte recebido
}

// Função que verifica se há dados prontos para leitura na porta serial UART
char UART_Data_Ready() {
    return RCIF; // Retorna verdadeiro se dados estiverem prontos para leitura
}

// Função que lê texto da porta serial UART até encontrar um caractere de nova
// linha '\n'
void UART_Read_Text(char *str) {
    char c;
    while (c != '\n') {
        c = UART_Read(); // Lê um caractere da UART
        *str += c;       // Adiciona o caractere à string de destino
    }
}
