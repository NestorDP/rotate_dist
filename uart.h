/*
 * uart.h
 *
 * Created: 25/09/2014 13:04:43
 *  Author: Nestor
 */ 
#include <stdio.h>


void UART_putchar(char c, FILE *stream);		//Protótipo das função de envio e recebimento
char UART_getchar(FILE *stream);				//da porta UART
void UART_init(void);							//Configuração inicial da UART

FILE uart_output = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, UART_getchar, _FDEV_SETUP_READ);

