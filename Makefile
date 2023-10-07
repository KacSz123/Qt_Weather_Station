MCU=atmega328p #uC name
F_CPU=16000000UL#clock frequency
CC=avr-gcc#EXAMPLE OF MAKEFILE
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
INCPATH += inc/
FLOAT_STRING=-Wl,-u,vfprintf -lprintf_flt -lm
CFLAGS=-std=c99 -g -mmcu=${MCU} -DF_CPU=${F_CPU} -F -pedantic -Wall -Os -I${INCPATH}
PATHS=-I${INCPATH}
CFLAGSNOCPU=-std=c99 -pedantic -Wall -Os -I./inc

TARGET=led	#output name 
SRCS=led.c  #source file
OUT=WeatherStationApp
SRCPATH=src/
bold:=$(shell tput bold)
sgr0:=$(shell tput sgr0)
directory=$(test -d OBJ)

all: cleanO freeLines1 OBJ/i2c.bin OBJ/usart.bin OBJ/bmp180.bin OBJ/adc.bin OBJ/weather_station.bin OBJ/main.bin freeLines2
	
	@echo "Consolidation: ${OUT}.bin file"
	${CC} ${CFLAGS} ${FLOAT_STRING} OBJ/main.bin OBJ/usart.bin OBJ/bmp180.bin OBJ/i2c.bin OBJ/adc.bin OBJ/weather_station.bin -o OBJ/${OUT}.bin
	@echo ""
	@echo "Creating output hex file: ${OUT}.hex!!!"
	${OBJCOPY} -j .text -j .data -O ihex  OBJ/${OUT}.bin ${OUT}.hex

OBJ/main.bin: 
	@echo "Compilation of main.bin file!! "
	${CC} -c -I${INCPATH} ${CFLAGS} ${FLOAT_STRING} -o OBJ/main.bin ${SRCPATH}main.c
	@echo ""

OBJ/i2c.bin:
	@echo "Compilation of i2c.bin file!! "
	${CC} -c ${CFLAGS} ${SRCPATH}i2c.c -o OBJ/i2c.bin
	@echo ""

OBJ/usart.bin:
	@echo "Compilation of usart.bin file!! "
	${CC} -c ${CFLAGS} ${SRCPATH}usart.c -o OBJ/usart.bin
	@echo ""

OBJ/bmp180.bin: OBJ/usart.bin OBJ/i2c.bin
	@echo "Compilation of bmp180.bin file!! "
	${CC} -c ${CFLAGS} ${SRCPATH}bmp180.c -o OBJ/bmp180.bin
	@echo ""

OBJ/adc.bin:
	@echo "Compilation of adc.bin file!! "
	${CC} -c ${CFLAGS} ${SRCPATH}adc.c -o OBJ/adc.bin
	@echo ""

OBJ/weather_station.bin:
	@echo "Compilation of weather_station.bin file!! "
	${CC} -c ${CFLAGS} ${SRCPATH}weather_station.c -o OBJ/weather_station.bin
	@echo ""


flash:
		avrdude -p ${MCU} -c usbasp -U flash:w:${OUT}.hex:i  -F -P usb

clean:
		@echo "$(bold) Cleaning workspace $(sgr0)"
		rm -f OBJ/*.bin OBJ/*.hex

cleanO: 
	@echo "$(bold) Cleaning workspace $(sgr0)"
	@echo "Removing old $(bold) *.bin$(sgr0) files"
	@echo ""
	@if test -d OBJ; then echo "$(bold)OBJ $(sgr0)directory found"; else echo "$(bold)OBJ $(sgr0) not found... creating directory $(bold)OBJ $(sgr0)" && mkdir OBJ; fi;
	@[ -f OBJ/bmp180.bin ] && rm OBJ/bmp180.bin && echo "rm $(bold) bmp180.bin$(sgr0)" || echo no  " **$(bold) bmp180.bin doesn't exist$(sgr0) **"
	@[ -f OBJ/i2c.bin ] && rm OBJ/i2c.bin && echo "rm $(bold) i2c.bin$(sgr0)" || echo no  " **$(bold) i2c.bin doesn't exist$(sgr0) **"
	@[ -f OBJ/usart.bin ] && rm OBJ/usart.bin && echo "rm $(bold) usart.bin$(sgr0)" || echo no  " **$(bold) usart.bin doesn't exist$(sgr0) **"
	@[ -f OBJ/adc.bin ] && rm OBJ/adc.bin && echo "rm $(bold) adc.bin$(sgr0)" || echo no  " **$(bold) adc.bin doesn't exist$(sgr0) **"
	@[ -f OBJ/weather_station.bin ] && rm OBJ/weather_station.bin && echo "rm $(bold) weather_station.bin$(sgr0)" || echo no  " **$(bold) weather_station.bin doesn't exist$(sgr0) **"
	@[ -f OBJ/main.bin ] && rm OBJ/main.bin && echo "rm $(bold) main.bin$(sgr0)" || echo no  " **$(bold) main.bin doesn't exist$(sgr0) **"
	@[ -f OBJ/${OUT}.bin ] && rm OBJ/${OUT}.bin && echo "rm $(bold) ${OUT}.bin$(sgr0)" || echo no  " **$(bold) ${OUT}.bin doesn't exist$(sgr0) **"
	@[ -f ${OUT}.hex ] && rm ${OUT}.hex && echo "rm $(bold) ${OUT}.hex$(sgr0)" || echo no  " **$(bold) ${OUT}.hex doesn't exist$(sgr0) **"
	

memory:
		avr-size -C --mcu=${MCU} OBJ/${OUT}.bin


freeLines1:
	@echo ""
	@echo ""
	@echo ""

freeLines2:
	@echo ""
	@echo ""
	@echo ""
		

