/*
 * HW_Interface_MPU.c
 *
 *  Created on: Sep 4, 2024
 *      Author: hp
 */

#include "../Inc/HW_Interface_MPU.h"

extern I2C_HandleTypeDef hi2c1;      //recheck
/**
 * @fn uint8_t I2C_MPU_READ()
 *
 * @brief a hardware interface function that uses I2C to send
 *        an array of data
 *
 * @param SL_address: slave address
 * @param Data: pointer to an array of data
 * @param Len: length of the array
 *
 * @return uint8_t: 1 if acknowledge received, 0 if acknowledge not received
 */
uint8_t I2C_MPU_READ(uint8_t SL_address, uint8_t *Data, uint8_t Len){
	HAL_StatusTypeDef ACK = HAL_I2C_Master_Receive(&hi2c1, SL_address<<1 ,
						Data, Len, 100); //sends read bit automatically
				return (ACK == HAL_OK) ? 1 : 0;
}

/**
 * @fn uint8_t I2C_MPU_INIT()
 *
 * @brief a hardware interface function that uses I2C to receive
 *        an array of data
 *
 * @param SL_address: slave address
 * @param Data: pointer to an array of data
 * @param Len: length of the array
 *
 * @return uint8_t: 1 if acknowledge received, 0 if acknowledge not received
 */
uint8_t I2C_MPU_WRITE(uint8_t SL_address, uint8_t *Data, uint8_t Len){
	HAL_StatusTypeDef ACK = HAL_I2C_Master_Transmit(&hi2c1, SL_address << 1,
							Data, Len, 100); //sends write bit automatically
					return (ACK == HAL_OK) ? 1 : 0;
}

/**
 * @fn void I2C_MPU_CECK(uint8_t, uint8_t*, uint8_t)
 * @brief
 *
 * @param SL_address
 * @param Data
 * @param Len
 */
uint8_t I2C_MPU_CHECK(uint8_t SL_address){
	uint8_t check;
	uint8_t data;
	HAL_I2C_Mem_Read(&hi2c1, SL_address << 1, 0x75, 1, &check, 1, 100);

	    if (check == 0x68) {  // 0x68 is the default WHO_AM_I register value
	        data = 0;
	        // Wake up the MPU6050 by writing 0 to the Power Management register (0x6B)
	        HAL_StatusTypeDef ACK =HAL_I2C_Mem_Write(&hi2c1, MPU_slave_address << 1, 0x6B, 1, &data, 1, 100);
	        if(ACK==HAL_OK){
	        	return 1;
	        }
	        return 0;
	    }

}

/**
 * @fn uint32_t GET_TICK()
 * @brief
 *
 * @return
 */

uint32_t GET_TICK(){
	return HAL_GetTick();
}
