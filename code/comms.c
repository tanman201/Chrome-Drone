/*
 * comms.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Tanner Smith
 */

#include "msp430.h"
#include "comms.h"
#include "commands.h"
#include "uart.h"
#include "terminal.h"

#define BLUETOOTH_BAUD          115200
#define BLUETOOTH_UART          2
#define STOP_CHAR               0x0A

char string[128];
uint8_t string_index = 0;

void COMMS_Init();
void COMMS_Send(char *s);
void COMMS_SendXY(char *s, uint8_t x, uint8_t y);
void BluetoothReceiver(uint8_t c);


void COMMS_Init(){
    UART_Init(BLUETOOTH_UART);
    UART_ReconfigureBaud(BLUETOOTH_UART, BLUETOOTH_BAUD);
    UCA2MCTLW = 0xD600;
    UART_RegisterReceiver(BLUETOOTH_UART, BluetoothReceiver);
}

void BluetoothReceiver(uint8_t c){

    if(c == STOP_CHAR){
        COMMANDS_Process(&string[0], string_index + 1);
        string_index = 0;
    }
    else{
        string[string_index] = c;
        string_index++;
    }

}

void COMMS_Send(char *s){
    char c = *s++;
    while(c){
        UART_WriteByte(BLUETOOTH_UART, c);
        c = *s++;
    }
}

void COMMS_SendXY(char *s, uint8_t x, uint8_t y){
    Terminal_CursorXY(BLUETOOTH_UART, x, y);
    COMMS_Send(s);
}
