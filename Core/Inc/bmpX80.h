/*
 * bmpX80.h
 *
 *  Created on: Dec 12, 2023
 *      Author: kacper
 */

#ifndef INC_BMPX80_H_
#define INC_BMPX80_H_

//#include "stm32l4xx.h"
#include "i2c.h"

#define BMP280_TEMP_XLSB 0xFC
#define BMP280_TEMP_LSB 0xFB
#define BMP280_TEMP_MSB 0xFA
#define BMP280_PRESS_XLSB 0xF9
#define BMP280_PRESS_LSB 0xF8
#define BMP280_PRESS_MSB 0xF7


#define BMP280_CONFIG 0xF5
#define BMP280_CONTROL 0xF4
#define BMP280_STATUS 0xF3
#define BMP280_RESET 0xE0
#define BMP280_CHIPID 0xD0
#define BMP280_CHIPID_OK 0x58

// compensate addrs
#define BMP280_DIG_T1 0x88
#define BMP280_DIG_T2 0x8A
#define BMP280_DIG_T3 0x8C


#define BMP280_DIG_P1 0x8E
#define BMP280_DIG_P2 0x90
#define BMP280_DIG_P3 0x92
#define BMP280_DIG_P4 0x94
#define BMP280_DIG_P5 0x96
#define BMP280_DIG_P6 0x98
#define BMP280_DIG_P7 0x9A
#define BMP280_DIG_P8 0x9C
#define BMP280_DIG_P9 0x9E

#define BMP280_ADDR_SLAVE 0xEC





// FILTER

typedef enum{
	BMP280_FILTER_OFF = 0,
	BMP280_FILTER_X2 =  1,
	BMP280_FILTER_X4 =  2,
	BMP280_FILTER_X8 =  3,
	BMP280_FILTER_X16 = 4 // OR 5/6  ---- [1 0 1]/[1 1 0]/[1 1 1]
}BMP280_FilterTypedef;

// TEMP measurement resolution
//#define BMP280_TEMP_16b 1
//#define BMP280_TEMP_17b 2
//#define BMP280_TEMP_18b 3
//#define BMP280_TEMP_19b 4
//#define BMP280_TEMP_20b 5

// PRESS resolution oversampling
//#define BMP280_PRESS_ULTRALOW  1
//#define BMP280_PRESS_LOW	   2
//#define BMP280_PRESS_STANDARD  3
//#define BMP280_PRESS_HIGH      4
//#define BMP280_PRESS_ULTRAHIGH 5

// standby time

typedef enum{
	BMP280_STANDBY_0_5_MS	= 0,
	BMP280_STANDBY_65_5_MS	= 1,
	BMP280_STANDBY_125_MS	= 2,
	BMP280_STANDBY_250_MS	= 3,
	BMP280_STANDBY_500_MS	= 4,
	BMP280_STANDBY_1000_MS	= 5,
	BMP280_STANDBY_2000_MS	= 6,
	BMP280_STANDBY_4000_MS	= 7
}BMP280_StandbyTypedef;

typedef enum{
	BMP280_PRESS_ULTRALOW=1,
	BMP280_PRESS_LOW=2,
	BMP280_PRESS_STANDARD=3,
	BMP280_PRESS_HIGH=4,
	BMP280_PRESS_ULTRAHIGH = 5
}BMP280_PressureOversamplingTypedef;

typedef enum {
	BMP280_TEMP_16b = 1,
	BMP280_TEMP_17b = 2,
	BMP280_TEMP_18b = 3,
	BMP280_TEMP_19b = 4,
	BMP280_TEMP_20b = 5,
} BMP280_TempResolutrionTypedef;


// MODES
typedef enum{
BMP280_MODE_SLEEP  = 0,
BMP280_MODE_FORCED = 1,  // OR 2    01/10
BMP280_MODE_NORMAL = 3
} BMP280_ModeTypedef;

//#define BMP280_TW

typedef struct BMP280_CompensationParameters
{
	uint16_t T1;
	int16_t T2;
	int16_t T3;

	uint16_t P1;
	int16_t P2;
	int16_t P3;
	int16_t P4;
	int16_t P5;
	int16_t P6;
	int16_t P7;
	int16_t P8;
	int16_t P9;

	int32_t t_fine;

	BMP280_ModeTypedef mode;
	BMP280_PressureOversamplingTypedef pressOversampling;
	BMP280_TempResolutrionTypedef tempResolution;
//	enum {MODE1, MODE2, MODE3} mode;

}BMP280_CompensationParametersType;

BMP280_CompensationParametersType params;
#define BMP280_S32_t int32_t
#define BMP280_US32_t uint32_t

int32_t BMP280_compensateTemp(int32_t adc_T);

uint8_t BMP280_read8b(uint8_t addr);
void BMP280_write8b(uint8_t addr, uint8_t data);

/*! @brief Reading 16b data in order: LSB, MSB...
 *
 * Function created for reading measurement data stored in BE
 * and converts it to LE.
 *
 * @param[in] addr Adress in i2c device.
 *
 * @return read data
 */
uint16_t BMP280_read16LM(uint8_t addr);

/*! @brief Reading 16b data in  order: MSB, LSB...
 *
 * Function created for reading compensation data which is
 * stored in memory with LE.
 *
 * @param[in] addr Adress in i2c device.
 *
 * @return read data in  little endian
 */
uint16_t BMP280_read16ML(uint8_t addr);


uint32_t BMP280_read24ML(uint8_t addr);
void BMP280_setConfig(BMP280_StandbyTypedef standby, BMP280_FilterTypedef filter);
void BMP280_init(BMP280_PressureOversamplingTypedef pressOversampling,
				BMP280_TempResolutrionTypedef tempResolution,
				BMP280_ModeTypedef mode);


int32_t BMP280_readTemperature();
int32_t BMP280_readPressure();


void BMP280_readTempAndPressure(int32_t* temp, int32_t *pressure);

#endif /* INC_BMPX80_H_ */
