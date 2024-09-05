/*
 * HW_Interface_MPU.h
 *
 *  Created on: Sep 4, 2024
 *      Author: hp
 */

#ifndef INC_HW_INTERFACE_MPU_H_
#define INC_HW_INTERFACE_MPU_H_

#include "../../Drivers/MPU_6050.h"
#define MPU_slave_address 0b110100    //LSB is AD0 (there's a missing bit)

void I2C_READ();
void I2C_INIT();


#endif /* INC_HW_INTERFACE_MPU_H_ */
