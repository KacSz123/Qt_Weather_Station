#include "weather_station.h"

#include<string.h>
#include<stdio.h>
#include <util/delay.h> 


void WEATHER_STATION_init(rawData* data, unsigned long usart_baudrate)
{
    USART_Init(usart_baudrate);
    ADC_init();
    I2C_init();
    BMP180_readCalibrationData(&(data->_bmpData));

}

void collectData(rawData* data, processedData* prData)
{
    data->temp=BMP180_getTemperature();
    _delay_ms(50);
    prData->_procTemperature = BMP180_calculateTemp(data->temp, &(data->_bmpData));
    _delay_ms(50);

    data->press = BMP180_getPressure(BMP180_STANDARD);
    _delay_ms(50);
    prData->_procPressure = BMP180_calculatePressure(data->press, &(data->_bmpData),BMP180_STANDARD)/100;
    _delay_ms(50);

    prData->_procRainFall = (uint32_t)ADC_takeMeasure(RAIN_ADC);
    _delay_ms(50);
    
    prData->_procLuminosity = (uint32_t)ADC_takeMeasure(LIGHT_ADC);
    _delay_ms(50);

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


char*  WEATHER_STATION_createStr(const processedData* dataToSend, char* msg)
{

    // char msg[50];
    sprintf(msg, "A %ld %ld %ld %ld", dataToSend->_procTemperature, dataToSend->_procPressure,
                               dataToSend->_procRainFall, dataToSend->_procLuminosity);
    
    uint8_t crc=crc8_simple((uint8_t*)msg,strlen(msg), 0x07);

    sprintf(msg,"%s %X\r\n", msg, crc);
    return msg;
}

void sendWeatherData(char* dataStr)
{
    USART_TransmitString((uint8_t*)dataStr);
}