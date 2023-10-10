/*
 * weather_station.h
 *
 *  Created on: Dec 29, 2023
 *      Author: kacper
 */

#ifndef INC_WEATHER_STATION_H_
#define INC_WEATHER_STATION_H_
#include <string.h>
#include "stdint.h"
typedef struct WS_DataTypedef
{
    int32_t _procTemperature;
    int32_t _procPressure;
    int32_t _procRainFall;
    int32_t _procLuminosity;
}WS_DataTypedef;

typedef struct WS_RawDataTypedef
{
    uint32_t T;
    uint32_t P;
    uint32_t R;
    uint32_t L;
}WS_RawDataTypedef;


//void WS_init(rawData* data);

void WS_collectData(WS_DataTypedef* prData);



uint8_t WS_crc8_simple(const uint8_t* data, size_t len, uint8_t poly);

char*  WS_createStr(WS_DataTypedef* prData, char* msg);


#endif /* INC_WEATHER_STATION_C_ */
