#define F_CPU 8000000		/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <avr/interrupt.h>
#include <util/delay.h>		/* Include Delay header file */

#include <stdio.h>

#include "lcd.h"
#include "uart.h"
#include "adc.h"



char input;
int num = 2;
int var;
char str1[10];

int main()
{
	LCD_init();			
	UART_init();
	ADC_init();

    stdout = &uart_output;		//Atribui uma nova stream de saida para a saida padrão
    stdin  = &uart_input;		//Atribui uma nova stream de entrada para a entrada padrão
	stderr = &lcd_str;			//Atribui uma nova stream de saída para a saída de erro padrão 

	//fprintf(stderr, "Hello!%u", ADC_read(0)); //Envia mensagem para o display através da stream de erro padrão
	
	LCD_command(0x01);		

	fprintf(&lcd_str, "Leticia Linda"); //Envia mesagem para o LCD direto da stream criada para isso 

	while(1) {
        printf("Hello mundo!z\n");
        input = getchar();
        scanf("%s", str1);

        LCD_command(0xC0);	
        fprintf(stderr, "You wrote %s\n", str1);
        //fprintf(stderr, "You wrote %d\n", var);
        //fprintf(stderr, "You wrote %c\n", input); 
        //printf("escopo do trabalho com robo movel* Objetivo Geral: \nDesenvolver uma plataforma didatica para o estudo de robotica movel, \nutilizando a placa tivaC da texas e chassi comercial de baixo custo.\n");


        //LCD_command(0x80);
        //fprintf(stderr, "Hello mundo! %u", (ADC_read(0) * 150)/307 ); 
        _delay_ms(500);     
    }

	while(1);
}