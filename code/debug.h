/*
 *            debug.h
 *
 *   Created on:  April 6, 2018
 *  Last Edited:  March 6, 2018
 *       Author:  Nick Gorab
 *        
 *  Header file to deal with the debug menu handler
 */

#ifndef DEBUG_h_
#define DEBUG_H_

#include "system.h"

void debugMenuHandle(uint8_t c);
void Debug_Options();
void accelMenuHandle(uint8_t c);
void Accel_Tests();
void proxMenuHandle(uint8_t c);
void Prox_Tests();



#endif /* DEBUG_H_ */
