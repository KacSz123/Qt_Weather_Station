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
// avr libs
#ifndef __WEATHER_DATA_H
#define __WEATHER_DATA_H





#include <avr/io.h>  

// c libs
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*!
 * @brief Structure of data read from
 * @struct rawData
 */
typedef struct rawData
{
    uint16_t _temperature;
    uint16_t _pressure;
    uint16_t _rainFall;
    uint16_t _luminosity;
}rawData;
void collectData(rawData* dataStr, uint16_t temp, uint16_t press,
                 uint16_t rain, uint16_t light){}





/*!
 * @brief Structure of processed data
 * @struct rawData
 */
typedef struct processedData
{
    uint16_t _procTemperature;
    uint16_t _procPressure;
    uint16_t _procRainFall;
    uint16_t _procLuminosity;
}processedData;

void crc8(){}
void processData(const rawData rawD, processData* prData){}

char*  createDataString(const processedData& dataToSend){}


#endif//__WEATHER_DATA_H