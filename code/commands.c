/*
 * commands.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Tanner Smith
 */
#include "commands.h"

void COMMANDS_Process(char *message, uint8_t length){
    char *s = message;

    char *s1 = "Set Kp ";
    char *s2 = "Set Ki ";
    char *s3 = "Set Kd ";
    char *s4 = "Set height ";
    char *s5 = "Turn on graph ";

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

    }

    // Check message 2
    while((*s == *s2) && (*s2 != 0x00)){
        *s++;
        *s2++;
        s2_check++;
    }
    if(s2_check == 7){

    }

    // Check message 3
    while((*s == *s3) && (*s3 != 0x00)){
        *s++;
        *s3++;
        s3_check++;
    }
    if(s3_check == 7){

    }

    // Check message 4
    while((*s == *s4) && (*s4 != 0x00)){
        *s++;
        *s4++;
        s4_check++;
    }
    if(s4_check == 11){

    }

    // Check message 1
    while(*s == *s1){
        *s++;
        *s1++;
        s1_check++;
    }
    if(s1_check == 7){

    }
}

