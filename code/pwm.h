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
void PWM_Initialize_Timer_A(void);
void PWM_Initialize_Timer_B(void);
void PWM_Set_Motor_1(char pwm);
void PWM_Set_Motor_2(char pwm);
void PWM_Set_Motor_3(char pwm);
void PWM_Set_Motor_4(char pwm);
void PWM_Set_All_Motors(char pwm);

#endif /* PWM_H_ */
