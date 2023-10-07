
#include <avr/io.h>		// Contains all the I/O Register Macros
#include <util/delay.h> // Generates a Blocking Delay
#include <string.h>
#include <stdio.h>
#include<stdint-gcc.h>
#include <math.h>
// #include<memory.h>
#include<stdlib.h>

#include "weather_station.h"
#define USART_BAUDRATE 9600 // Desired Baud Rate
// #define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define BUILD_IN_LED_PORT PORTB=0b00010000
#define BUILD_IN_LED PB5
#define LED_TOGGLE(X) PORTD^=(1<<(X))
#define BUILDIN_LED_TOGGLE LED_TOGGLE(BUILD_IN_LED)



#ifdef F_CPU
#define F_CPU 16000000UL  
#endif

///////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////

int main()
{
	rawData newWS;
	processedData processData;
	char str[50];


	WEATHER_STATION_init(&newWS, 9600);
	_delay_ms(200);

	while (1)
	{
	collectData(&newWS, &processData);
	_delay_ms(3000);
	sendWeatherData(WEATHER_STATION_createStr(&processData,str));
	_delay_ms(200);

	}
	return 0;
}
