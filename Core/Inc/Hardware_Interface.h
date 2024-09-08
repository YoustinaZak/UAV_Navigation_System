/*
 * Hardware_Interface.h
 *
 *  Created on: Sep 7, 2024
 *      Author: M.W Laptop
 */

#ifndef INC_HARDWARE_INTERFACE_H_
#define INC_HARDWARE_INTERFACE_H_

#include "stm32f1xx_hal.h"

uint8_t Read_Data(uint8_t sla, uint8_t *Data, uint8_t Length);
uint8_t Write_config(uint8_t sla, uint8_t *Data, uint8_t Length);


#endif /* INC_HARDWARE_INTERFACE_H_ */
