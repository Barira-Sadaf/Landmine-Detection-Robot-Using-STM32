/*
 * ULTRASONIC.h
 *
 *  Created on: Feb 10, 2025
 *      Author: faizkhan
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "main.h"
void Ultrasonic_distance(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif /* INC_ULTRASONIC_H_ */
