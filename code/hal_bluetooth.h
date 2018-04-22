/*
 * hal_bluetooth.h
 *
 *  Created on: Apr 21, 2018
 *      Author: tanma
 */

#ifndef HAL_BLUETOOTH_H_
#define HAL_BLUETOOTH_H_

#include "msp430fr5994.h"

// RN42 Reset - Active low (drive low to reset bluetooth) - Connected to P5.6
volatile unsigned char * reset_port_dir =               &P5DIR;
volatile unsigned char * reset_port_out =               &P5OUT;
const int reset_location =                              BIT6;

// RN42 GPIO2 Input - Status (High when Bluetooth Connected) - Connected to P2.7
// High when module is connected over Bluetooth
// Low when module is not connected over Bluetooth
volatile unsigned char * connected_port_dir =              &P2DIR;
volatile unsigned char * connected_port_in =               &P2OUT;
const int connected_location =                             BIT7;

// RN42 GPIO3 Output - Auto-discovery mode (Set high always) - Connected to P4.6
// Set high to put the module in auto-discovery mode
// Set low to make sure connected to specific device (dependent on GPIO6)
volatile unsigned char * discovery_port_dir =           &P4DIR;
volatile unsigned char * discovery_port_out =           &P4OUT;
const int discovery_location =                          BIT6;

// RN42 GPIO4 Output - Factory Resets when driven high - Connected to P4.4
// To reset the module, GPIO4 should be high on start up and then toggle between
// low and high with 1 second wait times between transitions
volatile unsigned char * factory_port_dir =             &P4DIR;
volatile unsigned char * factory_port_out =             &P4OUT;
const int factory_location =                            BIT4;

// RN42 GPIO5 Input - Status toggles based on state - Connected to P4.5
// Toggles at 1 Hz when the module is discoverable and waiting for connection
// Toggles at 10 Hz when the module is in command mode
// Driven High when the modle is connected over Bluetooth
volatile unsigned char * status_port_dir =           &P4DIR;
volatile unsigned char * status_port_in =            &P4OUT;
volatile unsigned char * status_port_out =              &P4OUT;
volatile unsigned char * status_ren_reg =               &P4REN;
volatile unsigned char * status_ie_reg =                &P4IE;
volatile unsigned char * status_ies_reg =               &P4IES;
volatile unsigned char * status_ifg_reg =               &P4IFG;
const int status_location  =                         BIT5;

// RN42 GPIO6 - Set Bluetooth as master - Connected to P1.0
// Setting this pin high will force the module to connect to the address stored
// Setting this pin low (and setting GPIO3 high) will cause this to go into discovery/pairing mode
volatile unsigned char * master_port_dir =              &P1DIR;
volatile unsigned char * master_port_out =              &P1OUT;
const int master_location =                             BIT0;


// RN42 GPIO7 - Set baudrate - Connected to P5.7
// Setting this pin high will force the bluetooth module to run at 9600
// Setting this pin low will set the baudrate to 115200 or firmware setting
volatile unsigned char * baud_port_dir =                &P4DIR;
volatile unsigned char * baud_port_out =                &P4OUT;
const int baud_location =                               BIT4;



#endif /* HAL_BLUETOOTH_H_ */
