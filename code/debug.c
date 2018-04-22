/*
 *            debug.c
 *
 *   Created on:  April 6, 2018
 *  Last Edited:  April 9, 2018
 *       Author:  Nick Gorab
 *        
 *  This serves as a debug terminal for the 
 *  software to perform system test w/o debugging
 */

#include "debug.h"

void debugMenuHandle(uint8_t c) {
    UART_UnregisterReceiver(UART_CHANNEL_DEBUG, debugMenuHandle);
    switch (c) {
        case '1':
            Accel_Tests();
            break;
        case '2':
            Prox_Tests();
            break;
        case '3':
        	LED_Tests();
            break;
        case '4':
        	Motor_Test();
        	break;
        default:
            UART_RegisterReceiver(UART_CHANNEL_DEBUG, debugMenuHandle);
            break;
    }
}

void Debug_Options() {
	UART_RegisterReceiver(UART_CHANNEL_DEBUG, debugMenuHandle);

	char menu[] = 
			"\r\n\nDebug Console\n\r"
			"Select:\n\r"
			"1: Accelerometer Testing\n\r"
			"2: Proximity Sensor Testing\n\r"
			"3: LED Testing\n\r"
			"4: Motor Testing\n\r";

	UART_Printf(UART_CHANNEL_DEBUG, menu);
}


void accelMenuHandle(uint8_t c) {
	UART_Printf(UART_CHANNEL_DEBUG, "%c", c);
	int x, y, z;
	switch(c) {
		case '1':
			MPU6050_Wake_Up();
			break;
		case '2':
			MPU6050_Get_ID();
			break;
		case '3':
			MPU6050_Get_Accel(&x, &y, &z);
			break;
		case '4':
			MPU6050_Calibrate_Accel();
			break;
		case '0':
			UART_UnregisterReceiver(UART_CHANNEL_DEBUG, accelMenuHandle);
			Debug_Options();
			break;
	}
}

void Accel_Tests() {
	UART_RegisterReceiver(UART_CHANNEL_DEBUG, accelMenuHandle);

	char accelMenu[] = 
			"Select:\n\r"
			"1: Wake up MPU6050\n\r"
			"2: Get ID\n\r"
			"3: Get Acceleration Data\n\r"
			"4: Calibrate Accelerometer\n\r"
			"0: Return\n\r";

	UART_Printf(UART_CHANNEL_DEBUG, accelMenu);
}

void proxMenuHandle(uint8_t c) {
	UART_Printf(UART_CHANNEL_DEBUG, "%c", c);
	switch(c) {
		case '1':
			VCNL4200_Start_PS();
			break;
		case '2':
			VCNL4200_Start_ALS();
			break;
		case '3':
			VCNL4200_Get_ID();
			break;
		case '4':
			VCNL4200_Set_LED_I();
			break;
		case '0':
			UART_UnregisterReceiver(UART_CHANNEL_DEBUG, debugMenuHandle);
			Debug_Options();
			break;
	}
}

void Prox_Tests() {
	UART_RegisterReceiver(UART_CHANNEL_DEBUG, proxMenuHandle);

	char proxMenu[] = 
			"Select:\n\r"
			"1: Start Prox. sensor\n\r"
			"2: Start Ambient light sensor\n\r"
			"3: Get device ID\n\r"
			"4: Force single reading\n\r"
			"0: Return\n\r";

	UART_Printf(UART_CHANNEL_DEBUG, proxMenu);
}

void motorMenuHandle(uint8_t c) {
	UART_Printf(UART_CHANNEL_DEBUG, "%c", c);
	switch(c) {
		case '1':

	}
}
