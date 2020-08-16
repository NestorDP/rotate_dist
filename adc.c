/*
 * ADC.c
 *
 * Created: 28/08/2016 15:42:33
 *  Author: Nestor
 */ 
#include <avr/io.h>
#include "adc.h"

void ADC_init(void)
{	
	//configuração do ADMUX = ADC Multiplexer Selection Register
	//AVcc with external capacitor at AREF pin
	//---------------------------------------------------------
	//REFS1	| REFS0 | Voltage Reference Selection
	//  0   |   0	| AREF, internal Vref turned off
	//  0   |   1   | AVcc with external capacitor at AREF pin
	//  1   |   1   | Internal 1.1V voltage reference with external capacitor ant AREF pin
	//---------------------------------------------------------
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	
	//Configuração do ADCSRA = ADC Control and Status Register A
	//ADEN -> ADC Enable
	//---------------------------------------------------------
	//ADPS2 | ADPS1 | ADPS0 | Divisor Factor
	//  1   |   1   |   1   | 128
	//  1   |   0   |   1   | 32
	//---------------------------------------------------------
	ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	//ADCSRA &= ~_BV(ADPS1);
}






unsigned int ADC_read(unsigned char ch)
{
	//Configura o pino PC0 como entrada e sem resistor de pull-up
	DDRC &= ~_BV(ch);
	
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//ADCSRA = ADC Control and Status Register A
	//ADSC	-> ADC Start Conversion
	ADCSRA|= _BV(ADSC);
	
	//ADCSRA = ADC Control and Status Register A
	//ADIF  -> ADC Interrupt Flag
	while(!(ADCSRA & (1<<ADIF)));			//Wait for conversion to complete

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!

	ADCSRA|= _BV(ADIF);
	
	low  = ADCL;
	high = ADCH;

	return (high << 8) | low;
}