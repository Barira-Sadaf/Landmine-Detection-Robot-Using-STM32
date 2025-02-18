/*
 * GSM.h
 *
 *  Created on: Feb 10, 2025
 *      Author: faizkhan
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include "main.h"
void GSM_Send_AT_Command(char *cmd, uint16_t delay);

void GSM_Send_SMS(char *phone_number, char *message);
#endif /* INC_GSM_H_ */
