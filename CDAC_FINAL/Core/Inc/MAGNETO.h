/*
 * MAGNETO.h
 *
 *  Created on: Feb 10, 2025
 */

#ifndef INC_MAGNETO_H_
#define INC_MAGNETO_H_

#include "main.h"
void Magneto_init(void);
void HMC5883L_ReadData(int16_t *mag_x, int16_t *mag_y, int16_t *mag_z);

#endif /* INC_MAGNETO_H_ */
