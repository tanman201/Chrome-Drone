/*
 * bluetooth.c
 *
 * RN42 Bluetooth module for MSP430FR5994
 *
 *  Created on: Apr 21, 2018
 *      Author: Tanner Smith
 */

#include "hal_bluetooth.h"
#include "bluetooth.h"


void BLUETOOTH_Init(){
    // Initialize reset to high so the module (active low) is not resetting constantly
   *reset_port_dir |= reset_location;
   *reset_port_out |= reset_location;
   P5SEL0 &= ~reset_location;
   P5SEL1 &= ~reset_location;

   // Initialize status pin as input and configure GPIO interrupt to toggle LED
   *status_port_dir &= ~status_location;
   *status_ren_reg |= status_location;
   *status_port_out &= ~status_location;

   // Initialize module to be in auto-discovery mode
   *discovery_port_dir |= discovery_location;
   *discovery_port_out |= discovery_location;

   // Initialize factory reset to be output and low
   *factory_port_dir |= factory_location;
   *factory_port_out &= ~factory_location;

   // Initialize connected pin as input
   *status_port_dir &= ~reset_location;

   // Initialize master toggle low so module will be in pairing mode
   *master_port_dir |= master_location;
   *master_port_out &= ~master_location;

   // Initialize baudrate to 115200
   *baud_port_dir |= baud_location;
   *baud_port_out &= ~baud_location;

   Status_ClearFlag();
   Status_EnableInterrupt(0);
}


/** Used to determine if button 1 is pressed or unpressed.
*
*  @return 1 for pressed Status and 0 for unpressed Status
*/
int Status_Read(){
return (*status_port_in & status_location) ^ status_location;
}

/** Enable the button 1 interrupt.
*
*  @param int positive_edge_trigger    1 for pos edge trigger, 0 for neg edge trigger
*/
void Status_EnableInterrupt(int positive_edge_trigger){
*status_ie_reg |= status_location;
if(positive_edge_trigger){
    *status_ies_reg |= status_location;
}
else{
    *status_ies_reg &= ~status_location;
}
*status_ifg_reg &= ~(status_location);

Status_ClearFlag();
}

/** Disable the button 1 interrupt */
void Status_DisableInterrupt(){
*status_ie_reg &= ~status_location;
}

/** Clear the button 1 interrupt flag */
void Status_ClearFlag(){
*status_ifg_reg &= ~(status_location);
}



