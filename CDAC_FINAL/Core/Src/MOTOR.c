/*
 * MOTOR.c
 *
 *  Created on: Feb 10, 2025
 *      Author: faizkhan
 */
#include "main.h"
#include "MOTOR.h"
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
#define IN1_PIN  GPIO_PIN_0
#define IN2_PIN  GPIO_PIN_1
#define IN3_PIN  GPIO_PIN_2
#define IN4_PIN  GPIO_PIN_3
#define MOTOR1   1
#define MOTOR2   2
#define FORWARD  1   // IN1 =1; IN2 = 0;
#define BACKWARD  0

void set_motor_direction(uint8_t motor, uint8_t direction)
{

	  if(motor != MOTOR1 && motor != MOTOR2){
		  // invalid motor not a define
		  return;
	  }

	  if(direction != FORWARD && direction != BACKWARD){
	 		  // invalid direction not a define in my code
	 		  return;
	 	  }
	  // normally define which motor are run
	  uint8_t motor_pin1,motor_pin2;
	  if(motor==MOTOR1){
		  motor_pin1 = IN1_PIN;
		  motor_pin2 = IN2_PIN;
	  }
	  else{
		  motor_pin1 = IN3_PIN;
		  motor_pin2 = IN4_PIN;
	  }

  	  if(direction == FORWARD)
  	  {
  		  HAL_GPIO_WritePin(GPIOC, motor_pin1,SET);
  		  HAL_GPIO_WritePin(GPIOC, motor_pin2, RESET);

  	  }
  	  else if(direction == BACKWARD){

  		  HAL_GPIO_WritePin(GPIOC, motor_pin1, RESET);
  		  HAL_GPIO_WritePin(GPIOC, motor_pin2, SET);

  	  }
  	  else{ // stop
  		HAL_GPIO_WritePin(GPIOC, motor_pin1, RESET);
  		HAL_GPIO_WritePin(GPIOC, motor_pin2, RESET);
  	  }

 }

void set_motor_speed(uint8_t motor, uint8_t speed)
{
	if(motor != MOTOR1 && motor != MOTOR2){
			  // invalid motor not a define
			  return;
		  }

   	uint32_t clock = (speed*1000)/100; // it is timer clock and change to percentage
   	if(motor == MOTOR1)
   	  {
           __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,clock);  // first we use channel1 but pa6 and pa5 pin are use in another place
   	  }
   	else   // MOTOR2
   	{
   		  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,clock);
   	  }

}
