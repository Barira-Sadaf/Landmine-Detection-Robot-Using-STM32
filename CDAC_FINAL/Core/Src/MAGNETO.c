/*
 * MAGNETO.c
 *
 *  Created on: Feb 10, 2025
 */



#include "main.h"
#include "MAGNETO.h"
#include <string.h>
extern I2C_HandleTypeDef hi2c1;
extern uint8_t mode_value = 0;
extern uint8_t reg_addr = 0x03;
extern uint8_t mode_reg[2] = {0x03, 0x00}; // {Register Address, Value (Continuous mode)}
extern uint8_t config_A[2] = {0x00, 0x70}; // Config Register A: 15Hz, Normal Mode, 8 samples
extern uint8_t config_B[2] = {0x01, 0x20}; // Config Register B: Gain = 1090 LSb/Gauss
extern int8_t mag_x, mag_y, mag_z;
extern char uart_buffer[100]; // Buffer to store formatted string

void Magneto_init(void){
	 HAL_StatusTypeDef ret;
	   ret = HAL_I2C_IsDeviceReady(&hi2c1, (0x1E<<1), 3, HAL_MAX_DELAY);
	   if(ret == HAL_OK)
	 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	   else
	 	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

	   HAL_I2C_Master_Transmit(&hi2c1, (0x1E << 1), mode_reg, 2, HAL_MAX_DELAY);
	   HAL_I2C_Master_Transmit(&hi2c1, (0x1E << 1), config_A, 2, HAL_MAX_DELAY);
	   HAL_I2C_Master_Transmit(&hi2c1, (0x1E << 1), config_B, 2, HAL_MAX_DELAY);

	   HAL_I2C_Master_Transmit(&hi2c1, (0x1E << 1), &reg_addr, 1, HAL_MAX_DELAY);
	   HAL_I2C_Master_Receive(&hi2c1, (0x1E << 1), &mode_value, 1, HAL_MAX_DELAY);
}

void HMC5883L_ReadData(int16_t *mag_x, int16_t *mag_y, int16_t *mag_z) {
    uint8_t data_reg = 0x03;
    uint8_t raw_data[6];

    HAL_I2C_Master_Transmit(&hi2c1, (0x1E << 1), &data_reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, (0x1E << 1), raw_data, 6, HAL_MAX_DELAY);

    *mag_x = (int16_t)(raw_data[0] << 8 | raw_data[1]);
    *mag_z = (int16_t)(raw_data[2] << 8 | raw_data[3]);
    *mag_y = (int16_t)(raw_data[4] << 8 | raw_data[5]);
    // Format the output string
       sprintf(uart_buffer, "X: %d, Y: %d, Z: %d\r\n", *mag_x, *mag_y, *mag_z);


}
