/*
 * HW_Interface_MPU.h
 *
 *  Created on: Sep 4, 2024
 *      Author: Youstina Magdy Refaat
 */

#ifndef INC_HW_INTERFACE_MPU_H_
#define INC_HW_INTERFACE_MPU_H_

#include "stm32f1xx_hal.h"
#include "../../Drivers/MPU_6050.h"



uint8_t I2C_MPU_READ(uint8_t SL_address, uint8_t *Data, uint8_t Len);
uint8_t I2C_MPU_WRITE(uint8_t SL_address, uint8_t *Data, uint8_t Len);
uint8_t I2C_MPU_CHECK(uint8_t SL_address);
uint32_t GET_TICK();
#endif /* INC_HW_INTERFACE_MPU_H_ */
