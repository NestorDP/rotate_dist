

void LCD_command( unsigned char cmnd );
void LCD_char( unsigned char data );
void LCD_init (void);

FILE lcd_str = FDEV_SETUP_STREAM(LCD_char, NULL, _FDEV_SETUP_WRITE);
