/*
 *            control.c
 *
 *   Created on:  April 10, 2018
 *  Last Edited:  April 10, 2018
 *       Author:  Nick Gorab
 *              
 *  Driver for the PID controller and motor-PWM distribution
 */

#include "pid.h"
extern int Ki;
extern int Kd;
extern int Kp;
extern int target_height;
extern int past_error;


void PID_Set_Ki(char value) {
	Ki = value;
}

void PID_Set_Kp(char value) {
	Kp = value;
}

void PID_Set_Kd(char value) {
	Kd = value;
}

void PID_Update(void) {
	uint16_t current_height = VCNL4200_Get_PS_Data();

	int current_error = current_height - target_height;
	int p_value = Kp * current_error;
	int d_value = (((current_error - past_error)/DELTA_T) * Kd);
	int i_value = current_error * DELTA_T * Ki;

	/* Sums values to get total PID output */
	int pid_output = p_value - d_value + i_value;

	/* Updates the past error */
	past_error = current_error;

	/* Checks to make sure output is within bounds */
	if(pid_output < MIN_OUTPUT) {
		pid_output = MIN_OUTPUT;
	} else if(pid_output > MAX_OUTPUT) {
		pid_output = MAX_OUTPUT;
	}
}
