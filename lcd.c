#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>		/* Include Delay header file */
#include <stdio.h>

#define LCD_Dir  DDRB		/* Define LCD data port direction */
#define LCD_Port PORTB		/* Define LCD data port */
#define RS PB1				/* Define Register Select pin */
#define RW PB2		
#define EN PB3 

/*===================================================
LISTA DE COMANDOS USADOS PELO LCD
===================================================*/
#define     _LCD_LIMPA       0x01     //Limpa o lcd
#define     _LCD_CUR_LIGA    0x0E     //Liga o cursor necessário para escrever qualquer mesagem
#define     _LCD_CUR_DESLIGA 0x0C     //Desliga o cursor
#define     _LCD_CUR_DES_ESQ 0x10     //Desloca o cursor para esquerda
#define     _LCD_CUR_DES_DIR 0x14     //Desloca o cursor para direita
#define     _LCD_CUR_HOME    0x02     //Cursor na primeira posição da primeira linha
#define     _LCD_CUR_PISCA   0x0D     //Efeito de pisca-pisca no cursor
#define     _LCD_CUR_ALTER   0x0F     //Alternancia entre os cursores
#define     _LCD_CUR_C_ESQ   0x04     //Sentido deslocamento do cursor ao entrar caracter - para esquerda
#define     _LCD_CUR_C_DIR   0x06     //Sentido deslocamento do cursor ao entrar caracter - para direita
#define     _LCD_MSG_C_ESQ   0x07     //Deslocamento da mensagem ao entrar com caracter - para esquerda
#define     _LCD_MSG_C_DIR   0x05     //Deslocamento da mensagem ao entrar com caracter - para esquerda
#define     _LCD_MSG_ESQ     0x18
#define     _LCD_MSG_DIR     0x1C
#define     _LCD_LINHA1_1    0x80
#define     _LCD_LINHA1_2    0x81
#define     _LCD_LINHA1_3    0x82
#define     _LCD_LINHA1_4    0x83
#define     _LCD_LINHA1_5    0x84
#define     _LCD_LINHA1_6    0x85
#define     _LCD_LINHA1_7    0x86
#define     _LCD_LINHA1_8    0x87
#define     _LCD_LINHA1_9    0x88
#define     _LCD_LINHA1_10   0x89
#define     _LCD_LINHA1_11   0x8A
#define     _LCD_LINHA1_12   0x8B
#define     _LCD_LINHA1_13   0x8C
#define     _LCD_LINHA1_14   0x8D
#define     _LCD_LINHA1_15   0x8E
#define     _LCD_LINHA1_16   0x8F
#define     _LCD_LINHA2      0xC0





void LCD_command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_char( unsigned char data )
{
	LCD_Port  = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port  = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_init (void)		/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	LCD_Port &= ~(1<<RW);
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_command(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_command(0x28);      /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_command(0x0c);      /* Display on cursor off*/
	LCD_command(0x06);      /* Increment cursor (shift cursor to right)*/
	LCD_command(0x01);      /* Clear display screen*/
	_delay_ms(2);
}


