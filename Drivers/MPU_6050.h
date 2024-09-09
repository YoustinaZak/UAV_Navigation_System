/*
 * MPU_6050.h
 *
 *  Created on: Sep 4, 2024
 *      Author: Youstina Magdy Refaat
 */

#ifndef MPU_6050_H_
#define MPU_6050_H_

#include <stdint.h>
#include <math.h>

#define MPU_slave_address     0b110100<<1  //LSB is AD0 (there's a missing bit)
#define RAD_TO_DEG 57.2957795131

typedef enum {
	range_250,  //norm eq:   131/(2^0)
	range_500,  //norm eq:   131/(2^1)
	range_1000, //norm eq:   131/(2^2)
	range_2000  //norm eq:   131/(2^3)
}gyro_scale_t;

typedef enum {
	range_2g,   //norm eq:   2^15 / 2^(1+0) LSB
	range_4g,   //norm eq:   2^15 / 2^(1+1) LSB
	range_8g,   //norm eq:   2^15 / 2^(1+2) LSB
	range_16g   //norm eq:   2^15 / 2^(1+3) LSB
}acc_scale_t;

typedef struct{

	uint8_t gyro_scale_buffer[2];          //trial
	gyro_scale_t gyro_scale_range;  //0 to 3 //user programmable
	uint8_t acc_scale_buffer[2];
	acc_scale_t acc_scale_range;            //user programmable

	uint8_t acc_buffer[6];
	int16_t acc_x;
	float norm_acc_x;
	int16_t acc_y;
	float norm_acc_y;
	int16_t acc_z;
	float norm_acc_z;

	uint8_t gyro_buffer[6];
	int16_t gyro_x;
	float norm_gyro_x;
	int16_t gyro_y;
	float norm_gyro_y;
	int16_t gyro_z;
	float norm_gyro_z;

	uint8_t temp_buffer[2];
	int16_t raw_temp;
	float norm_temp;
	//self test??

	float pitch;
	float roll;
	float yaw;
	struct {
		//function pointers
		uint8_t (*Read_UI)(uint8_t SL_address, uint8_t *Data, uint8_t Len);
		uint8_t (*Write_UI)(uint8_t SL_address, uint8_t *Data, uint8_t Len);
		uint8_t (*Check_UI)(uint8_t SL_address);
		uint32_t (*Tick)();
	}HW_Interface;

}MPU_t;

void MPU_GET_ACC_RAW(MPU_t *sensor);
void MPU_GET_GYRO_RAW(MPU_t *sensor);
void MPU_CALC_ACC_NORM(MPU_t *sensor);
void MPU_CALC_GYRO_NORM(MPU_t *sensor);
void MPU_GET_PITCH_ROLL_YAW(MPU_t *sensor);

#endif /* MPU_6050_H_ */
