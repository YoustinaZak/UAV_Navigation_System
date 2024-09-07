/*
 * MPU_6050.c
 *
 *  Created on: Sep 5, 2024
 *      Author: Youstina Magdy
 */

#include "MPU_6050.h"

/**
 * @fn void MPU_Check(MPU_t*)
 * @brief
 *
 * @param sensor
 */
void MPU_Check(MPU_t *sensor){
	sensor->HW_Interface.Check_UI(MPU_slave_address);
}

/**
 * @fn void MPU_Init(MPU_t*)
 * @brief
 *
 * @param sensor
 */
void MPU_Init(MPU_t *sensor){            //test success
	sensor->gyro_scale_buffer[0]=0x1B;
	sensor->gyro_scale_buffer[1]= (sensor->gyro_scale_range)<<3;
	sensor->acc_scale_buffer[0]=0x1C;
	sensor->acc_scale_buffer[1]= (sensor->acc_scale_range)<<3;
	sensor->HW_Interface.Write_UI(MPU_slave_address, sensor->gyro_scale_buffer, 2 );
	sensor->HW_Interface.Write_UI(MPU_slave_address, sensor->acc_scale_buffer, 2 );
}
/**
 * @fn void MPU_GET_ACC_RAW(MPU_t*)
 * @brief
 *
 * @param sensor
 */
void MPU_GET_ACC_RAW(MPU_t *sensor){ //leh pointer

	uint8_t reg_address=59;                               //recheck
	sensor->HW_Interface.Write_UI(MPU_slave_address, &reg_address, 1 );
	sensor->HW_Interface.Read_UI(MPU_slave_address, sensor->acc_buffer, 6 );
	sensor->acc_x = sensor->acc_buffer[0] << 8 | sensor->acc_buffer[1];
	sensor->acc_y = sensor->acc_buffer[2] << 8 | sensor->acc_buffer[3];
	sensor->acc_z = sensor->acc_buffer[4] << 8 | sensor->acc_buffer[5];
}

/**
 * @fn void MPU_GET_GYRO_RAW(MPU_t*)
 * @brief
 *
 * @param sensor
 */
void MPU_GET_GYRO_RAW(MPU_t *sensor){ //leh pointer

	uint8_t reg_address =67;
	sensor->HW_Interface.Write_UI(MPU_slave_address, &reg_address, 1 );
	sensor->gyro_x = sensor->gyro_buffer[0] << 8 | sensor->gyro_buffer[1];
	sensor->gyro_y = sensor->gyro_buffer[2] << 8 | sensor->gyro_buffer[3];
	sensor->gyro_z = sensor->gyro_buffer[4] << 8 | sensor->gyro_buffer[5];
}

/**
 * @fn void MPU_CALC_ACC_NORM(MPU_t*)
 * @brief
 *
 * @param sensor
 */
void MPU_CALC_ACC_NORM(MPU_t *sensor){
	sensor->norm_acc_x = (float)sensor->acc_x / ((1<<15) / (1<<(1+sensor->acc_scale_range)));
	sensor->norm_acc_y = (float)sensor->acc_y / ((1<<15) / (1<<(1+sensor->acc_scale_range)));
	sensor->norm_acc_z = (float)sensor->acc_z / ((1<<15) / (1<<(1+sensor->acc_scale_range)));
}

/**
 * @fn void MPU_CALC_GYRO_NORM(MPU_t*)
 * @brief
 *
 * @param sensor
 */
void MPU_CALC_GYRO_NORM(MPU_t *sensor){
	sensor->norm_gyro_x = sensor->gyro_x / (131 / (1<<sensor->gyro_scale_range));
	sensor->norm_gyro_y = sensor->gyro_y / (131 / (1<<sensor->gyro_scale_range));
	sensor->norm_gyro_z = sensor->gyro_z / (131 / (1<<sensor->gyro_scale_range));

}
