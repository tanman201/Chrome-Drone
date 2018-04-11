/*
 *            contorl.h
 *
 *   Created on:  April 10, 2018
 *  Last Edited:  April 10, 2018
 *       Author:  Nick Gorab
 *        
 *  Driver for the PID controller and motor-PWM distribution
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "system.h"


void Control_Set_Height_Ki(char value);
void Control_Set_Height_Kp(char value);
void Control_Set_Height_Kd(char value);
void Control_Update_Height_PID(int set_height);

#endif /* SYSTEM_H_ */
