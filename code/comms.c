/*
 * comms.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Tanner Smith
 */

#include "comms.h"
#include "commands.h"
#include "uart.h"
#include "terminal.h"

#define BLUETOOTH_BAUD          115200
#define BLUETOOTH_UART          UART1
#define STOP_CHAR               '\r'

uint8_t string[128];
int string_index = 0;

void COMMS_Init();
void COMMS_Send(char *s);
void COMMS_SendXY(char *s, uint8_t x, uint8_t y);
void BluetoothReceiver(uint8_t c);

void COMMS_Init(){
    UART_Init(BLUETOOTH_UART);
    UART_ReconfigureBaud(BLUETOOTH_UART, BLUETOOTH_BAUD);
    UART_RegisterReceiver(BLUETOOTH_UART, BluetoothReceiver);
}

void BluetoothReceiver(uint8_t c){

    int successful_reception = 0;

    if(c == STOP_CHAR){
        successful_reception = COMMAND_Process(string, string_index + 1);
        string_index = 0;
        if(!successful_reception){
            UART_printf(BLUETOOTH_UART, "Command Not Found");
        }
    }
    else{
        string[string_index] = c;
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
