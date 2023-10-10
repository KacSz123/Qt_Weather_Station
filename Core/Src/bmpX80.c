/*
 * bmpX80.c
 *
 *  Created on: Dec 12, 2023
 *      Author: kacper
 */


#include "bmpX80.h"


int32_t BMP280_compensateTemp(int32_t adc_T)
{
	int32_t var1, var2, T;

	var1 = ((((adc_T>>3) - ((BMP280_S32_t)params.T1<<1))) * ((BMP280_S32_t)params.T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BMP280_S32_t)params.T1)) * ((adc_T>>4)-
			((BMP280_S32_t)params.T1))) >> 12)*((BMP280_S32_t)params.T3)) >> 14;

	params.t_fine = var1 + var2;
	T = (params.t_fine * 5 + 128) >> 8;

	return T;
}


uint8_t BMP280_read8b(uint8_t addr)
{
	uint8_t tmp;
	HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDR_SLAVE , addr, 1, &tmp, sizeof(tmp), 10);

	return tmp;
}

void BMP280_write8b(uint8_t addr, uint8_t data)
{

	HAL_I2C_Mem_Write(&hi2c1,BMP280_ADDR_SLAVE , addr, 1, &data, sizeof(data), 10);
}


/*! @brief Reading 16b data in order: LSB, MSB...
 *
 * Function created for reading measurement data stored in BE
 * and converts it to LE.
 *
 * @param[in] addr Adress in i2c device.
 *
 * @return read data
 */
uint16_t BMP280_read16LM(uint8_t addr)
{


	uint8_t tmp[2];// {LSB, MSB}
	HAL_I2C_Mem_Read(&hi2c1, BMP280_ADDR_SLAVE, addr, 1, tmp, 2, 10);
	return ((tmp[0]) | tmp[1]<<8); // 0x[msb][lsb]

//	uint8_t lsb, msb;
//	HAL_I2C_Mem_Read(&hi2c1, BMP280_ADDR_SLAVE, addr, 1, &lsb, 1, 10);
//	HAL_I2C_Mem_Read(&hi2c1, BMP280_ADDR_SLAVE, addr+1, 1, &msb, 1, 10);
//
//	return (lsb)|(msb<<8);

}

/*! @brief Reading 16b data in  order: MSB, LSB...
 *
 * Function created for reading compensation data which is
 * stored in memory with LE.
 *
 * @param[in] addr Adress in i2c device.
 *
 * @return read data in  little endian
 */
uint16_t BMP280_read16ML(uint8_t addr)
{				//		0x
	uint8_t tmp[2]; // [MSB , LSB]
	HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDR_SLAVE , addr, 1, tmp, 2, 10);


	return (tmp[0]<<8)|tmp[1]; //0x [MSB][LSB]
}



uint32_t BMP280_read24ML(uint8_t addr)
{
	uint8_t tmp[3];  // [ ]
	HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDR_SLAVE , addr, 1, tmp, 3, 10);

	return ((tmp[0] << 16) | tmp[1] << 8 | tmp[2]);
}
void BMP280_setConfig(BMP280_StandbyTypedef standby, BMP280_FilterTypedef filter)
{
	BMP280_write8b(BMP280_CONFIG, ((standby<<5)|(filter<<2)));
}

void BMP280_init(BMP280_PressureOversamplingTypedef pressOversampling,
				BMP280_TempResolutrionTypedef tempResolution,
				BMP280_ModeTypedef mode)
{

	if(pressOversampling>=BMP280_PRESS_ULTRAHIGH)
		params.pressOversampling = BMP280_PRESS_ULTRAHIGH;
	else
		params.pressOversampling = pressOversampling;

	if(params.tempResolution>=BMP280_TEMP_20b)
		params.tempResolution=BMP280_TEMP_20b;
	else
		params.tempResolution = tempResolution;


	if(params.mode>=BMP280_MODE_NORMAL)
		params.mode=BMP280_MODE_NORMAL;
	else
		params.mode = mode;


	while(BMP280_read8b(BMP280_CHIPID)!=BMP280_CHIPID_OK){};
	params.T1 = BMP280_read16LM(BMP280_DIG_T1);
	params.T2 = BMP280_read16LM(BMP280_DIG_T2);
	params.T3 = BMP280_read16LM(BMP280_DIG_T3);

	params.P1 = BMP280_read16LM(BMP280_DIG_P1);
	params.P2 = BMP280_read16LM(BMP280_DIG_P2);
	params.P3 = BMP280_read16LM(BMP280_DIG_P3);
	params.P4 = BMP280_read16LM(BMP280_DIG_P4);
	params.P5 = BMP280_read16LM(BMP280_DIG_P5);
	params.P6 = BMP280_read16LM(BMP280_DIG_P6);
	params.P7 = BMP280_read16LM(BMP280_DIG_P7);
	params.P8 = BMP280_read16LM(BMP280_DIG_P8);
	params.P9 = BMP280_read16LM(BMP280_DIG_P9);


	BMP280_write8b(BMP280_CONTROL, ((params.tempResolution<<5)|(params.pressOversampling<<2)|params.mode));
	params.t_fine = 0;
//	HAL_I2C_Mem_Write(&hi2c1, BMP280_ADDR_SLAVE, BMP280_CONFIG, 1, 0x00, 1, 10);
//	return HAL_OK;
}



int32_t BMP280_readTemperature()
{

	//control status
	uint8_t ctrl = BMP280_read8b(BMP280_CONTROL);
	uint8_t mode;
	ctrl &=~(0x03); // reset last 2 bits
	ctrl|=BMP280_MODE_FORCED; //set last bits on FORCED mode

	BMP280_write8b(BMP280_CONTROL, ctrl);

	mode = BMP280_read8b(BMP280_CONTROL);
	mode &= 0x03; // reset all bits besides  modes bits [last 2b]


	if(mode == BMP280_MODE_FORCED) // if mode is not forced end with -99!
	{
		while((BMP280_read8b(BMP280_CONTROL) & 0x03)!=BMP280_MODE_SLEEP){}; // wait for end of conversion

		int32_t adc_T = BMP280_read24ML(BMP280_TEMP_MSB);  //read 3 bytes
		adc_T>>=4;
		// calculation to C'
		int32_t var1, var2, T;

		var1 = ((((adc_T>>3) - ((int32_t)params.T1<<1))) * ((int32_t)params.T2)) >> 11;
		var2 = (((((adc_T>>4) - ((int32_t)params.T1)) * ((adc_T>>4) - ((int32_t)params.T1))) >> 12) *
		((int32_t)params.T3)) >> 14;
		params.t_fine = var1 + var2;
		T = (int32_t)((params.t_fine * 5 + 128) >> 8)/10;
		return T;
	}

	return -99;
}
int32_t BMP280_readPressure()
{
//	float P;
	BMP280_readTemperature(); // for t_fine

	uint32_t adc_P = BMP280_read24ML(BMP280_PRESS_MSB);

	adc_P>>=4;

	int64_t var1, var2, p;
	var1 = ((int64_t)params.t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)params.P6;
	var2 = var2 + ((var1*(int64_t)params.P5)<<17);
	var2 = var2 + (((int64_t)params.P4)<<35);
	var1 = ((var1 * var1 * (int64_t)params.P3)>>8) + ((var1 * (int64_t)params.P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)params.P1)>>33;
	if (var1 == 0)
	{
	return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)params.P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)params.P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)params.P7)<<4);

	return (int32_t)((int32_t)p/256)/100; //to hpa


//	return P;
}


void BMP280_readTempAndPressure(int32_t* temp, int32_t *pressure)
{
//	float P;
	*temp = BMP280_readTemperature(); // for t_fine
	HAL_Delay(10);
	uint32_t adc_P = BMP280_read24ML(BMP280_PRESS_MSB);

	adc_P>>=4;

	int64_t var1, var2, p;
	var1 = ((int64_t)params.t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)params.P6;
	var2 = var2 + ((var1*(int64_t)params.P5)<<17);
	var2 = var2 + (((int64_t)params.P4)<<35);
	var1 = ((var1 * var1 * (int64_t)params.P3)>>8) + ((var1 * (int64_t)params.P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)params.P1)>>33;
	if (var1 == 0)
	{
		*temp = -99; *pressure = -999;
	return ; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)params.P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)params.P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)params.P7)<<4);

	* pressure = ((int32_t)p/256)/100; //to hpa


//	return P;
}
