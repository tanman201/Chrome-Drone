/*
 * led_driver.c
 *
 *  Created on: Apr 5, 2018
 *      Author: tomas
 */


#include "system.h"
#include "comms.h"

void LED1_On();
void LED1_Off();
void LED1_Toggle();
void LED2_On();
void LED2_Off();
void LED2_Toggle();
void LED3_On();
void LED3_Off();
void LED3_Toggle();
void LED4_On();
void LED4_Off();
void LED4_Toggle();
void LED5_On();
void LED5_Off();
void LED5_Toggle();
void LED6_On();
void LED6_Off();
void LED6_Toggle();
void LED7_On();
void LED7_Off();
void LED7_Toggle();
void LED8_On();
void LED8_Off();
void LED8_Toggle();
void LED9_On();
void LED9_Off();
void LED9_Toggle();
void LEDA_On();
void LEDA_Off();
void LEDA_Toggle();
void LEDB_On();
void LEDB_Off();
void LEDB_Toggle();
void LEDC_On();
void LEDC_Off();
void LEDC_Toggle();

void LED_Init(){
    //Set LEDs as outputs
    P1DIR |= 0x1E;
    P2DIR |= 0x60; //Blutooth P2.6 Power P2.5
    P3DIR |= 0x07;
    P4DIR |= 0x0C;
    P5DIR |= 0x0F;

    //Initialize LEDs as off
    P1OUT &= ~0x1E;
    P2OUT &= ~0x60;
    P3OUT &= ~0x07;
    P4OUT &= ~0x0C;
    P5OUT &= ~0x0F;
}

void LED_On(unsigned int LED){
    switch(LED) {
          case 1 :
             LED1_On();
             break;
          case 2 :
              LED2_On();
          case 3 :
             LED3_On();
             break;
          case 4 :
             LED4_On();
             break;
          case 5 :
             LED5_On();
             break;
          case 6 :
             LED6_On();
             break;
          case 7 :
             LED7_On();
             break;
          case 8 :
             LED8_On();
             break;
          case 9 :
             LED9_On();
             break;
          case 10 :
             LEDA_On();
             break;
          case 11 :
             LEDB_On();
             break;
          case 12 :
             LEDC_On();
             break;
          default :
             break;
       }
}

void LED_Off(unsigned int LED){
    switch(LED) {
          case 1 :
             LED1_Off();
             break;
          case 2 :
              LED2_Off();
          case 3 :
             LED3_Off();
             break;
          case 4 :
             LED4_Off();
             break;
          case 5 :
             LED5_Off();
             break;
          case 6 :
             LED6_Off();
             break;
          case 7 :
             LED7_Off();
             break;
          case 8 :
             LED8_Off();
             break;
          case 9 :
             LED9_Off();
             break;
          case 10 :
             LEDA_Off();
             break;
          case 11 :
             LEDB_Off();
             break;
          case 12 :
             LEDC_Off();
             break;
          default :
             break;
       }
}

void LED_Toggle(unsigned int LED){
    switch(LED) {
          case 1 :
             LED1_Toggle();
             break;
          case 2 :
              LED2_Toggle();
          case 3 :
             LED3_Toggle();
             break;
          case 4 :
             LED4_Toggle();
             break;
          case 5 :
             LED5_Toggle();
             break;
          case 6 :
             LED6_Toggle();
             break;
          case 7 :
             LED7_Toggle();
             break;
          case 8 :
             LED8_Toggle();
             break;
          case 9 :
             LED9_Toggle();
             break;
          case 10 :
             LEDA_Toggle();
             break;
          case 11 :
             LEDB_Toggle();
             break;
          case 12 :
             LEDC_Toggle();
             break;
          default :
             break;
       }
}

void LED_Bluetooth_On(){
    P2OUT |= BIT5;      //LED1 on PCB
}

void LED_Bluetooth_Off(){
    P2OUT &= ~BIT5;     //LED1 on PCB
}

void LED_Bluetooth_Toggle(){
    P2OUT ^= BIT5;      //LED1 on PCB
}

void LED_Power_On(){
    P2OUT |= BIT6;      //LED2 on PCB
}

void LED_Power_Off(){
    P2OUT &= ~BIT6;     //LED2 on PCB
}

void LED_Power_Toggle(){
    P2OUT ^= BIT6;      //LED2 on PCB
}

void LED_All_On(){
     P1OUT |= 0x1E;
     P3OUT |= 0x07;
     P4OUT |= 0x0C;
     P5OUT |= 0x0F;
}
void LED_All_Off(){
    P1OUT &= ~0x1E;
    P3OUT &= ~0x07;
    P4OUT &= ~0x0C;
    P5OUT &= ~0x0F;
}
void LED_All_Toggle(){
     P1OUT ^= 0x1E;
     P3OUT ^= 0x07;
     P4OUT ^= 0x0C;
     P5OUT ^= 0x0F;
}
//**********LED Functions*******//
void LED1_On(){
    P4OUT |= BIT2; //LED3 on PCB
}

void LED1_Off(){
    P4OUT &= ~BIT2; //LED3 on PCB
}
void LED1_Toggle(){
    P4OUT ^= BIT2; //LED3 on PCB
}

void LED2_On(){
    P4OUT |= BIT3; //LED4 on PCB
}

void LED2_Off(){
    P4OUT &= ~BIT3; //LED4 on PCB
}
void LED2_Toggle(){
    P4OUT ^= BIT3; //LED4 on PCB
}

void LED3_On(){
    P3OUT |= BIT2; //LED5 on PCB
}

void LED3_Off(){
    P3OUT &= ~BIT2; //LED5 on PCB
}
void LED3_Toggle(){
    P3OUT ^= BIT2; //LED5 on PCB
}

void LED4_On(){
    P3OUT |= BIT1; //LED6 on PCB
}

void LED4_Off(){
    P3OUT &= ~BIT1; //LED6 on PCB
}
void LED4_Toggle(){
    P3OUT ^= BIT1; //LED6 on PCB
}

void LED5_On(){
    P1OUT |= BIT8; //LED7 on PCB
}

void LED5_Off(){
    P1OUT &= ~BIT8; //LED7 on PCB
}
void LED5_Toggle(){
    P1OUT ^= BIT8; //LED7 on PCB
}

void LED6_On(){
    P1OUT |= BIT1; //LED8 on PCB
}

void LED6_Off(){
    P1OUT &= ~BIT1; //LED8 on PCB
}
void LED6_Toggle(){
    P1OUT ^= BIT1; //LED8 on PCB
}

void LED7_On(){
    P5OUT |= BIT0; //LED9 on PCB
}

void LED7_Off(){
    P5OUT &= ~BIT0; //LED9 on PCB
}
void LED7_Toggle(){
    P5OUT ^= BIT0; //LED9 on PCB
}

void LED8_On(){
    P5OUT |= BIT1; //LED10 on PCB
}

void LED8_Off(){
    P5OUT &= ~BIT1; //LED10 on PCB
}
void LED8_Toggle(){
    P5OUT ^= BIT1; //LED10 on PCB
}

void LED9_On(){
    P1OUT |= BIT3; //LED11 on PCB
}

void LED9_Off(){
    P1OUT &= ~BIT3; //LED11 on PCB
}
void LED9_Toggle(){
    P1OUT ^= BIT3; //LED11 on PCB
}

void LEDA_On(){
    P3OUT |= BIT0; //LED12 on PCB
}

void LEDA_Off(){
    P3OUT &= ~BIT0; //LED12 on PCB
}
void LEDA_Toggle(){
    P3OUT ^= BIT0; //LED12 on PCB
}

void LEDB_On(){
    P5OUT |= BIT3; //LED13 on PCB
}

void LEDB_Off(){
    P5OUT &= ~BIT3; //LED13 on PCB
}
void LEDB_Toggle(){
    P5OUT ^= BIT3; //LED13 on PCB
}

void LEDC_On(){
    P5OUT |= BIT2; //LED14 on PCB
}

void LEDC_Off(){
    P5OUT &= ~BIT2; //LED14 on PCB
}
void LEDC_Toggle(){
    P5OUT ^= BIT2; //LED14 on PCB
}

#define DELAY 100

void LED_Party(){

    LED_Power_Toggle();
    DelayMs(DELAY);

    LED_Power_Toggle();
    DelayMs(DELAY);

    LED_Power_Toggle();
    DelayMs(DELAY);

    LED_Power_Toggle();
    DelayMs(DELAY);

    LED_All_On();
    DelayMs(DELAY);
    LED_All_Off();
    DelayMs(DELAY);

    LED_All_On();
    DelayMs(DELAY);
    LED_All_Off();
    DelayMs(DELAY);

    LED_All_On();
    DelayMs(DELAY);
    LED_All_Off();
    DelayMs(DELAY);

    unsigned int i = 0;
    for(i = 1; i <= 12; i++){
        LED_Toggle(i);
        DelayMs(DELAY);
    }
    for(i = 12; i > 0; i--){
        LED_Toggle(i);
        DelayMs(DELAY);
    }

    COMMS_Send("We are going to party till we're purple \r");
}
