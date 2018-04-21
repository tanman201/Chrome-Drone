/*
 *            pwm.h
 *
 *   Created on:  April 9, 2018
 *  Last Edited:  March 9, 2018
 *       Author:  Nick Gorab
 *        
 *  Header file for motor PWM
 */

#ifndef PWM_H_
#define PWM_H_

#include "system.h"

void PWM_Initialize_Timers(void);
void PWM_Set_Motor_1(int pwm);
void PWM_Set_Motor_2(int pwm);
void PWM_Set_Motor_3(int pwm);
void PWM_Set_Motor_4(int pwm);
void PWM_Set_All_Motors(int pwm);

#endif /* PWM_H_ */
