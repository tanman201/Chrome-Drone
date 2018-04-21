/*
 *            pwm.c
 *
 *   Created on:  April 9, 2018
 *  Last Edited:  March 9, 2018
 *       Author:  Nick Gorab
 *        
 *  Drivers which control the PWM applied to each of the motors
 */

#include "pwm.h"

void PWM_Initialize_GPIO(void) {
    P3DIR  |= BIT4
           |  BIT5;
    P3SEL0 |= BIT4
           |  BIT5;
    P1DIR  |= BIT4
           |  BIT5;
    P1SEL0 |= BIT4
           |  BIT5;
}

void PWM_Initizlize_Timer_A(void) {
    TA0CTL   = TASSEL_2  
             + MC_2;
    TA0CCTL2 = OUTMOD_7; 
    TA0CCR0  = 100;     
}

void PWM_Initizlize_Timer_B(void) {
    TB0CTL   = TBSSEL_2     
             + MC_1;        
    TB0CCTL2 = OUTMOD_7;    
    TB0CCTL3 = OUTMOD_7;    
    TB0CCTL5 = OUTMOD_7;    
    TB0CCR0  = 100;         
}

void PWM_Initialize_Timers(void) {
    PWM_Initialize_GPIO();
    PWM_Initizlize_Timer_A();
    PWM_Initizlize_Timer_B();
}

void PWM_Set_Motor_1(int pwm) {
	TA0CCR2 = pwm;
}

void PWM_Set_Motor_2(int pwm) {
	TB0CCR2 = pwm;
}

void PWM_Set_Motor_3(int pwm) {
	TB0CCR3 = pwm;
}

void PWM_Set_Motor_4(int pwm) {
	TB0CCR5 = pwm;
}

void PWM_Set_All_Motors(int pwm) {
	TA0CCR2 = TB0CCR2 = TB0CCR3 = TB0CCR5 = pwm;
}

