/*
 * weather_station.c
 *
 *  Created on: Dec 29, 2023
 *      Author: kacper
 */

#include "weather_station.h"

#include "bmpX80.h"
#include "adc.h"
#include "string.h"
#include "stdio.h"
//void WS_init(rawData* data, unsigned long usart_baudrate)
//{
//    USART_Init(usart_baudrate);
//    ADC_init();
//    I2C_init();
//    BMP180_readCalibrationData(&(data->_bmpData));
//
//}

void WS_collectData(WS_DataTypedef* prData)
{
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  (prData->_procRainFall) = HAL_ADC_GetValue(&hadc1);

	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  (prData->_procLuminosity)= HAL_ADC_GetValue(&hadc1);


	  BMP280_readTempAndPressure(&(prData->_procTemperature), &(prData->_procPressure));
}




uint8_t crc8_simple(const uint8_t* data, size_t len, uint8_t poly)
{
    uint8_t crc=0x00;
    for(size_t i=0; i<len; ++i)
    {
        crc^=data[i];
        for(int j=0; j<8; ++j)
        {
            if((crc&0x80)!=0)
                crc=(uint8_t)((crc << 1)^poly);
            else
                crc<<=1;
        }
    }
    return crc;
}


char*  WS_createStr(WS_DataTypedef* prData, char* msg)
{

//	char tmp[50];
    sprintf(msg, "A %ld %ld %ld %ld", prData->_procTemperature, prData->_procPressure,
    		prData->_procRainFall, prData->_procLuminosity);


    uint8_t crc=crc8_simple((uint8_t*)msg,strlen(msg), 0x07);

    sprintf(msg,"%s %X\r\n", msg, crc);
    return msg;
}


