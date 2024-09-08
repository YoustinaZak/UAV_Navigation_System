/*
 * ADXL_345_accelerometer.c
 *
 *  Created on: Sep 3, 2024
 *      Author: M.W Laptop
 */

#include "ADXL_345_accelerometer.h"

#define ADXL345_SLA 0x53 << 1  // I2C address for ADXL345

typedef enum {
	OFSX_X = 0x1e, OFSX_Y = 0x1f, OFSX_Z = 0x20,
} ADXl345_Reg;

/// @fn adxl345_stat_t ADXL345_Init(adxl345_t*)
/// @brief
///
/// @param accelerometer ptr to the accelerometer handle
/// @return
adxl345_stat_t ADXL345_Init(adxl345_t *accelerometer) {
	//Set the device to measurement mode
	accelerometer->I2C_Buffer[0] = ADXL345_REG_POWER_CTL;
	accelerometer->I2C_Buffer[1] = (accelerometer->Link
			| accelerometer->Auto_Sleep | accelerometer->Measure
			| accelerometer->Sleep | accelerometer->Wakeup) >> 2;

	//transfer the config to the device via I2C write

	return ADXL345_WriteConfig(accelerometer);

}

/// @fn uint8_t ADXL345_WriteConfig(adxl345_t*)
/// @brief
/// Applies the configuration to the device
/// @param accelerometer ptr to the accelerometer handle
/// @return ADXL345_success if successful
adxl345_stat_t ADXL345_WriteConfig(adxl345_t *accelerometer) {
	//write the accelerometer offsets
	accelerometer->I2C_Buffer[0] = OFSX_X;

	//load the offset values into the I2C buffer
	for (uint8_t x = 0; x < 3; x++) {
		accelerometer->I2C_Buffer[1 + x] = accelerometer->Offsets[x];
	}
	//assigning the rate and power mode to BW_RATE reg
	accelerometer->I2C_Buffer[4] = ADXL345_REG_BW_RATE;
	accelerometer->I2C_Buffer[5] = (accelerometer->Power_Mode
			| accelerometer->Data_Rate) >> 3;

	if (accelerometer->AG_HW_Interface.Write_config(ADXL345_SLA,
			accelerometer->I2C_Buffer, 8) != 1) {
		return ADXL345_failed;
	} else {
		return ADXL345_success;
	}
}

/// @fn adxl345_stat_t ADXL345_ReadData(adxl345_t*, int16_t*, int16_t*, int16_t*)
/// @brief
///
/// @param accelerometer
/// @param x
/// @param y
/// @param z
/// @return
adxl345_stat_t ADXL345_ReadData(adxl345_t *accelerometer, int16_t *x,
		int16_t *y, int16_t *z) {

	accelerometer->I2C_Buffer[0] = ADXL345_REG_DATAX0;

	*x = ((int16_t) accelerometer->I2C_Buffer[2] << 8)
			| accelerometer->I2C_Buffer[1];
	*y = ((int16_t) accelerometer->I2C_Buffer[4] << 8)
			| accelerometer->I2C_Buffer[3];
	*z = ((int16_t) accelerometer->I2C_Buffer[6] << 8)
			| accelerometer->I2C_Buffer[7];
	return ADXL345_WriteConfig(accelerometer);
}

