/*
 * bluetooth.h
 *
 *  Created on: Apr 21, 2018
 *      Author: tanma
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

void BLUETOOTH_Init();
int  Status_Read();
void Status_EnableInterrupt(int positive_edge_trigger);
void Status_DisableInterrupt();
void Status_ClearFlag();



#endif /* BLUETOOTH_H_ */
