/*
 * comms.h
 *
 *  Created on: Apr 11, 2018
 *      Author: Tanner Smith
 */

#ifndef COMMS_H_
#define COMMS_H_

#include "stdint.h"

void COMMS_Init();
void COMMS_Send(char *s);
void COMMS_SendXY(char *s, uint8_t x, uint8_t y);

#endif /* COMMS_H_ */
