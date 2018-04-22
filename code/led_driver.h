/*
 * led_driver.h
 *
 *  Created on: Apr 5, 2018
 *      Author: tomas
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "system.h"

void LED_Init();
void LED_On(unsigned int LED);
void LED_Off(unsigned int LED);
void LED_Toggle(unsigned int LED);
void LED_Bluetooth_On();
void LED_Bluetooth_Off();
void LED_Bluetooth_Toggle();
void LED_Power_On();
void LED_Power_Off();
void LED_Power_Toggle();
void LED_All_On();
void LED_All_Off();
void LED_All_Toggle();
void LED_Party();

#endif /* LED_DRIVER_H_ */
