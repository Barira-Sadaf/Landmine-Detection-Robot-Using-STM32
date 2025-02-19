/*
 * GSM.c
 *
 *  Created on: Feb 10, 2025
 */


#include "main.h"
#include "GSM.h"
#include <string.h>
extern UART_HandleTypeDef huart2;
void GSM_Send_AT_Command(char *cmd, uint16_t delay) {
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd), 1000);
    HAL_Delay(delay);
}

void GSM_Send_SMS(char *phone_number, char *message) {
    GSM_Send_AT_Command("AT\r\n", 1000);  // Check GSM response
    GSM_Send_AT_Command("AT+CMGF=1\r\n", 1000);  // Set SMS mode to text
    HAL_Delay(1000);

    char sms_command[50];
    sprintf(sms_command, "AT+CMGS=\"%s\"\r\n", phone_number);
    GSM_Send_AT_Command(sms_command, 1000);

    GSM_Send_AT_Command(message, 1000);
    GSM_Send_AT_Command("\x1A", 1000); // End message with Ctrl+Z (ASCII 26)
}
