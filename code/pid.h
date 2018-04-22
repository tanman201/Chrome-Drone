/*
 *            contorl.h
 *
 *   Created on:  April 10, 2018
 *  Last Edited:  April 10, 2018
 *       Author:  Nick Gorab
 *        
 *  Driver for the PID controller and motor-PWM distribution
 */

#ifndef PID_H_
#define PID_H_

#include "system.h"

#define DELTA_T		100
#define MAX_OUTPUT	100
#define MIN_OUTPUT	  4

void PID_Set_Ki(int value);
void PID_Set_Kp(int value);
void PID_Set_Kd(int value);
void PID_Set_Target_Height(int value);
void PID_Update(void);

#endif /* SYSTEM_H_ */
