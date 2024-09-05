/*
 * MPU_6050.h
 *
 *  Created on: Sep 4, 2024
 *      Author: Youstina Magdy
 */

#ifndef MPU_6050_H_
#define MPU_6050_H_

#include <stdint.h>

typedef struct{

	uint16_t gyro_scale_range;  //0 to 3 //user programmable
	uint16_t acc_scale_range;            //user programmable

	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;

	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;

	int16_t temp;
	//self test??
	struct HW_Interface{
		//function pointers
		void (*Read)(uint8_t slave,);
		void (*Init)(uint8_t slave,);
	};

}MPU_T;


#endif /* MPU_6050_H_ */
