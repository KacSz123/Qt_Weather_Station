/*!
 * @file i2c.h
 * @author {Kacper Szczepanowski} ({kacperszcz159@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef I2C_H
#define I2C_H
#include<stdint-gcc.h>


/*!
 * @brief I2C init
 * 
 */
void I2C_init();

/*!
 * @brief Send start signal
 * 
 */
void I2C_start();


/*!
 * @brief wait for answer
 * 
 */
void I2C_wait() ;

/*!
 * @brief Stop signal
 * 
 */
void I2C_stop();


/*!
 * @brief Write byte throug i2c
 * 
 * @param[in] data byte to send
 */
void I2C_writeByte(uint8_t data);

/*!
 * @brief read byte with or without ack
 * if !ack, doesnt wait for it,=.
 * 
 * @param ack 
 * @return uint8_t 
 */
uint8_t I2C_readByte(uint8_t ack);

/*!
 * @brief 
 * 
 * @param[in] device slave address
 * @param[in] addr Memory address
 * @param[in] data data to send
 */
void I2C_send(uint8_t device, uint8_t addr, uint8_t data);

/*!
 * @brief Receiving 8b data.
 * 
 * @param deviceW slave address W
 * @param deviceR slave address R
 * @param addr Memory address
 * @param ack if ack 
 * 
 * @return uint8_t data
 */
uint8_t I2C_receive(uint8_t deviceW,uint8_t deviceR, uint8_t addr, uint8_t ack);


/*!
 * @brief Read data with ack
 * 
 * @return uint8_t  data
 */
uint8_t I2C_ReadDataAck();


/*!
 * @brief Read data with no ack
 * 
 * @return uint8_t 
 */
uint8_t I2C_ReadDataNotAck();

#endif // I2C_H