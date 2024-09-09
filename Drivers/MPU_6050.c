/*
 * MPU_6050.c
 *
 *  Created on: Sep 5, 2024
 *      Author: Youstina Magdy Refaat
 */

#include "MPU_6050.h"

/**
 * @fn void MPU_Check(MPU_t*)
 * @brief checks for sleep mode and slave address by using a function pointer
 *
 * @param sensor an instance of the MPU sensor
 */

void MPU_Check(MPU_t *sensor){
	sensor->HW_Interface.Check_UI(MPU_slave_address);
}

/**
 * @fn void MPU_Init(MPU_t*)
 * @brief initializes full scale range for both gyro and accelerometer
 *
 * @param sensor an instance of the MPU sensor
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
 * @brief gets raw data of the accel
 *
 * @param sensor an instance of the MPU sensor
 */

void MPU_GET_ACC_RAW(MPU_t *sensor){ //leh pointer

	uint8_t reg_address=59;                               //recheck
	sensor->HW_Interface.Write_UI(MPU_slave_address, &reg_address, 1 );
	sensor->HW_Interface.Read_UI(MPU_slave_address, sensor->acc_buffer, 6 );
	sensor->acc_x =(int16_t) ((sensor->acc_buffer[0] << 8) | sensor->acc_buffer[1]);
	sensor->acc_y =(int16_t) ((sensor->acc_buffer[2] << 8) | sensor->acc_buffer[3]);
	sensor->acc_z =(int16_t) ((sensor->acc_buffer[4] << 8) | sensor->acc_buffer[5]);
	/*reg_address =63;
	sensor->HW_Interface.Write_UI(MPU_slave_address, &reg_address, 1 );
	sensor->HW_Interface.Read_UI(MPU_slave_address, sensor->buff, 2 );*/
}

/**
 * @fn void MPU_GET_GYRO_RAW(MPU_t*)
 * @brief gets raw data of the gyro
 *
 * @param sensor an instance of the MPU sensor
 */
void MPU_GET_GYRO_RAW(MPU_t *sensor){ //leh pointer

	uint8_t reg_address =67;
	sensor->HW_Interface.Write_UI(MPU_slave_address, &reg_address, 1 );
	sensor->HW_Interface.Read_UI(MPU_slave_address, sensor->gyro_buffer, 6 );
	sensor->gyro_x = ((sensor->gyro_buffer[0] << 8) | sensor->gyro_buffer[1]);
	sensor->gyro_y = ((sensor->gyro_buffer[2] << 8) | sensor->gyro_buffer[3]);
	sensor->gyro_z = ((sensor->gyro_buffer[4] << 8) | sensor->gyro_buffer[5]);
}

/**
 * @fn void MPU_CALC_ACC_NORM(MPU_t*)
 * @brief calculates normalized accel readings
 *
 * @param sensor an instance of the MPU sensor
 */

void MPU_CALC_ACC_NORM(MPU_t *sensor){
	sensor->norm_acc_x = (float)sensor->acc_x / ((1<<15) / (1<<(1+sensor->acc_scale_range)));
	sensor->norm_acc_y = (float)sensor->acc_y / ((1<<15) / (1<<(1+sensor->acc_scale_range)));
	sensor->norm_acc_z = (float)sensor->acc_z / ((1<<15) / (1<<(1+sensor->acc_scale_range)));
}

/**
 * @fn void MPU_CALC_GYRO_NORM(MPU_t*)
 * @brief calculates normalized gyro readings
 *
 * @param sensor an instance of the MPU sensor
 */

void MPU_CALC_GYRO_NORM(MPU_t *sensor){
	sensor->norm_gyro_x = sensor->gyro_x / (131 / (1<<sensor->gyro_scale_range));
	sensor->norm_gyro_y = sensor->gyro_y / (131 / (1<<sensor->gyro_scale_range));
	sensor->norm_gyro_z = sensor->gyro_z / (131 / (1<<sensor->gyro_scale_range));

}

/**
 * @fn void MPU_GET_TEMP(MPU_t*)
 * @brief gets raw temp reading and calculates normalized temp
 *
 * @param sensor an instance of the MPU sensor
 */

void MPU_GET_TEMP(MPU_t *sensor){
	uint8_t reg_address =65;
    sensor->HW_Interface.Write_UI(MPU_slave_address, &reg_address, 1 );
	sensor->HW_Interface.Read_UI(MPU_slave_address, sensor->temp_buffer, 6 );
	sensor->raw_temp = (int16_t)((sensor->temp_buffer[0] << 8) | sensor->temp_buffer[1]);
	sensor->norm_temp = (float)(sensor->raw_temp/340.0) +36.53; //temp in celsius
}

/**
 * @fn void MPU_GET_PITCH_ROLL_YAW(MPU_t*)
 * @brief calculates pitch, roll and yaw angles
 *
 * @param sensor an instance of the MPU sensor
 */

void MPU_GET_PITCH_ROLL_YAW(MPU_t *sensor){

	static float previousYaw =0;
	static uint32_t previousTime = 0;
	uint32_t currentTime = sensor->HW_Interface.Tick();
	float deltaTime = (float)(currentTime - previousTime) / 1000;

	MPU_GET_ACC_RAW(sensor);
	MPU_GET_GYRO_RAW(sensor);
	MPU_CALC_ACC_NORM(sensor);
	MPU_CALC_GYRO_NORM(sensor);

	sensor->pitch = (float)atan2(sensor->acc_y, sqrt(sensor->acc_x * sensor->acc_x + sensor->acc_z * sensor->acc_z)) * RAD_TO_DEG;
	sensor->roll = (float)atan2(sensor->acc_x, sqrt(sensor->acc_y * sensor->acc_y + sensor->acc_z * sensor->acc_z)) * RAD_TO_DEG;
    sensor->yaw = (float)previousYaw + sensor->norm_gyro_z * deltaTime;

    if(sensor->yaw >=360){   //issue**************
    	sensor->yaw= sensor->yaw - 360 ;
    } else if (sensor->yaw <= -360){
    	sensor->yaw <= 360 + sensor->yaw ;
    }

    previousTime = currentTime;
    previousYaw = sensor->yaw;

}
