/*
 * adc.h
 *
 * Created: 28/08/2016 15:34:48
 *  Author: Nestor
 */ 

uint8_t low, high;

#define ADC_startConversion		ADCSRA|= _BV(ADSC)
#define ADC_restart				ADCSRA|= _BV(ADIF)

void ADC_init(void);
unsigned int ADC_read(unsigned char ch);