/*!
 * @file weather_data.h
 * @author {Kacper Szczepanowski} ({kacperszcz159@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2023-10-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __WEATHER_STATION_H
#define __WEATHER_STATION_H


// avr libs
#include <avr/io.h>
// #include <avr/interrupt.h>
// c libs
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// my headers
#include"usart.h"
#include"i2c.h"
#include"adc.h"
#include"bmp180.h"

//////////////////////////////////////
//    W. S. Macros
//////////////////////////////////////
#define RAIN_ADC A0
#define RAIN_GPIO 1 

#define LIGHT_ADC A2

/*!
 * @brief Init status enum.
 * 
 */
// typedef enum WS_CHECK{ WS_OK, WS_ADC_NOK,WS_USART_NOK, WS_BMP180_NOK};


// #define USART_BAUDRATE 9600 // Desired Baud Rate


/*!
 * @brief Structure of data read from
 * @struct rawData
 */
typedef struct rawData
{
    //helper data

    //raw data:
    //bmp180    
    bmp180DataConf _bmpData;
	long int temp, press;

    // // adc
    // uint16_t _rainFall;
    // uint16_t _luminosity;
}rawData;

/*!
 * @brief Structure of processed data
 * @struct rawData
 */
typedef struct processedData
{
    uint32_t _procTemperature;
    uint32_t _procPressure;
    uint32_t _procRainFall;
    uint32_t _procLuminosity;
}processedData;



void WEATHER_STATION_init(rawData* data, unsigned long usart_baudrate);




void collectData(rawData* data, processedData* prData);






void processData(const rawData rawD, processedData* prData);

/*!
 * @brief Create a Data String object from data
 * 
 * @param[in] dataToSend processedData object with takien measures.
 * @param[out] msg string container  
 * @return char* 
 */
char*  WEATHER_STATION_createStr(const processedData* dataToSend, char* msg);



/*!
 * @brief 
 * 
 * @param data 
 * @param len 
 * @param poly 
 * @return uint8_t 
 */
uint8_t crc8_simple(const uint8_t* data, size_t len, uint8_t poly);


void sendWeatherData(char* dataStr);
#endif//__WEATHER_STATION_H