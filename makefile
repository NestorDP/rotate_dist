#1  avr-gcc -gdwarf-2 -Os -mmcu=atmega8 -c COM-serial.c
#2  avr-gcc -gdwarf-2 -mmcu=atmega8 -o umaChave.elf COM-serial.o
#3  avr-objcopy -j .text -j .data -O ihex prog31.elf prog31.hex




daq : main.o lcd.o uart.o adc.o
	@echo
	avr-gcc -gdwarf-2 -mmcu=atmega8 -o daq.elf main.o lcd.o uart.o adc.o
	@echo
	avr-objcopy -j .text -j .data -O ihex daq.elf daq.hex
	@echo
	avr-size -C --mcu=atmega8 daq.elf

main.o : ../main.c ../defines.h
	avr-gcc -gdwarf-2 -Os -Wall -mmcu=atmega8 -c ../main.c

uart.o : ../uart.c ../uart.h ../defines.h
	avr-gcc -gdwarf-2 -Os -Wall -mmcu=atmega8 -c ../uart.c

lcd.o : ../lcd.c ../lcd.h ../defines.h
	avr-gcc -gdwarf-2 -Os -Wall -mmcu=atmega8 -c ../lcd.c

adc.o : ../adc.c ../adc.h ../defines.h
	avr-gcc -gdwarf-2 -Os -Wall -mmcu=atmega8 -c ../adc.c


avrdude:
	avrdude -c usbasp -p m8 -P usb -U flash:w:daq.hex:i

clean :
	rm main.o uart.o lcd.o adc.o
