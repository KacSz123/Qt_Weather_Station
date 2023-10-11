/*!
 * @file main.c
 * @author {Kacper Szczepanowski} ({kacperszcz159@gmail.com})
 * @brief 
 * @version 0.8
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
//avr includes
#include<avr/io.h>		// Contains all the I/O Register Macros
#include<util/delay.h> // Generates a Blocking Delay

//ws include
#include "weather_station.h"

// #define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define USART_BAUDRATE 9600 // Desired Baud Rate

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
		sendWeatherData(WEATHER_STATION_createStr(&processData, str));
		_delay_ms(200);
	}
	return 0;
}
