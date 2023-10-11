##
# Qt_Weather_Station
Development of a project made for classes on Visualization of Sensory Data at WUST. Project on ATmega328p.

## Table of contents
<!-- - [costam](#costam) -->
- [Description](#description)
- [Sensors](#sensors)
- [Peripherials](#peripherials)
- [Dependiecies](#dependiecies)
- [Installation](#installation)
- [Example](#example)

<!-- ## costam -->

## Description 
Project of a Weather Station based on ATmega328p. Device collects data about: temperature, pressure, rain density, luminosity. Project uses Serial  interface to communicate with PC (data correctness is checked with CRC8).


<!-- <sup>[1]</sup>, rain density<sup>[1]</sup>.  -->
<!-- <i><sup>[1]</sup> Based on Analog to Digital Converter.</i> -->

## Sensors
- Temperature and Pressure: **BMP180** <i>(future BMPX80)</i> --> I<i><sup>2</sup>C interface.
- Rain Density: **FC-37** electrode pad and **YL-38 LM393** converter module.
- Luminosity: **voltage divider with photoresistor**.

## Peripherials
1. I<i><sup>2</sup>C:
    - PC4: I<i><sup>2</sup>C SDA
    - PC5: I<i><sup>2</sup>C SCL
2. ADC-10b:
    - PC0: Rain Sensor Output
    - PC2: Light voltage divider output.


## Dependiecies

Tested with:
- **Ubuntu 20.04**
- **avr-gcc 5.4.0**.
- **avrdude 6.3-20171130**
- **GNU Make 4.2.1**
## Installation

1. Clone repo branch with:
 <pre>git clone --branch ATmega328p_C_code https://github.com/KacSz123/Qt_Weather_Station</pre>

2. Compile project from ~/*/Qt_Weather_Station/ by:
    <pre>make</pre>


3. Load into MCU
    <pre>make flash</pre>


## Example

Example <i>main.c</i> code.
<pre>#include&ltavr/io.h>		// Contains all the I/O Register Macros
#include&ltutil/delay.h> // Generates a Blocking Delay

//ws include
#include"weather_station.h"

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
		
                sendWeatherData(WEATHER_STATION_createStr(&processData,
                                                            str));
		_delay_ms(200);
	}
	return 0;
}
 </p>