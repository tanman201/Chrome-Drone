/*
 * commands.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Tanner Smith
 */

#include "commands.h"
#include "comms.h"
#include "led_driver.h"


void COMMANDS_Process(char *message, uint8_t length){
    char *s = message;

    char *s1 = "Set Kp ";
    char *s2 = "Set Ki ";
    char *s3 = "Set Kd ";
    char *s4 = "Set height ";
    char *s5 = "LED Party";

    uint8_t s1_check = 0;
    uint8_t s2_check = 0;
    uint8_t s3_check = 0;
    uint8_t s4_check = 0;
    uint8_t s5_check = 0;

    // Check message 1
    while((*s == *s1) && (*s1 != 0x00)){
        *s++;
        *s1++;
        s1_check++;
    }
    if(s1_check == 7){
        char value[3] = {*s++, *s++, *s++};
        COMMS_Send("Kp set to ");
        COMMS_Send(&value[0]);
        COMMS_Send(&value[1]);
        COMMS_Send(&value[2]);
    }
    s = message;

    // Check message 2
    while((*s == *s2) && (*s2 != 0x00)){
        *s++;
        *s2++;
        s2_check++;
    }
    if(s2_check == 7){
        COMMS_Send("Message Received");
    }
    s = message;

    // Check message 3
    while((*s == *s3) && (*s3 != 0x00)){
        *s++;
        *s3++;
        s3_check++;
    }
    if(s3_check == 7){
        COMMS_Send("Message Received");
    }
    s = message;

    // Check message 4
    while((*s == *s4) && (*s4 != 0x00)){
        *s++;
        *s4++;
        s4_check++;
    }
    if(s4_check == 11){
        COMMS_Send("Message Received");
    }
    s = message;

    while((*s == *s5) && (*s5 != 0x00)){
        *s++;
        *s5++;
        s5_check++;
    }
    if(s5_check == 9){
        LED_Party();
    }
    s = message;

}

