/*
 * UART.c
 *
 * Created: 25/09/2014 13:03:31
 *  Author: Nestor
 */ 

#define F_CPU 8000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/setbaud.h>
#include <stdio.h>



void UART_init(void) {
	UCSRC = _BV(UCSZ1) | _BV(UCSZ0); 			/* 8-bit data */
	UCSRB = _BV(RXEN) | _BV(TXEN) | _BV(RXCIE); /* Enable RX and TX */

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	
}

void UART_putchar(char c, FILE *stream) {
	if (c == '\n') {
		UART_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
}

char UART_getchar(FILE *stream) {
	loop_until_bit_is_set(UCSRA, RXC);
	return UDR;
}