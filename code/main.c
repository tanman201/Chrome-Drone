#include <msp430.h> 
#include "project_settings.h"
#include "subsystem.h"
#include "task.h"
#include "uart.h"
#include "hal_general.h"
#include "system.h"

void Blink_Setup();
void Blink();
void Sensor_Connection_Test(void);

/* Global variable declerations */
int target_height = 0;
int Kp = 0;
int Ki = 0;
int Kd = 0;
int past_error = 0;


/**
 * main.c
 */
int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    DisableInterrupts();
    EnableInterrupts();

    i2c_init();
    LED_Init();

        VCNL4200_Start_PS();

while(1) {

    __delay_cycles(60000);
    VCNL4200_Get_PS_Data();
    LED_Toggle(1);
    LED_Toggle(2);
    LED_Toggle(3);
    LED_Toggle(4);
}
//    Task_Init();
// //   UART_Init(SUBSYSTEM_UART);
//
//    Blink_Setup();
//

//
//    Task_Schedule(Blink, 0, 0, 1000);
//
//    while(1) {
//        SystemTick();
//    }
}

void Blink_Setup(){
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction
}

void Blink(){
    P1OUT ^= BIT0;                      // Toggle LED
}




/*
 * Function: Sensor_Connection_Test
 * --------------------------------
 * This is a function which will be able to 
 * check both of the I2C devices used to make
 * sure that they are functioning nominally.
 * (Might want to add a flag.)
 *
 * @param sensdat:  Struct used as an argument
 *                  for the Get_ID functions.
 */

void Sensor_Connection_Test(void) {
    int connected = 0;
    while(1) {
        if(VCNL4200_Get_ID() == 0x5810) {
            connected++;
        }
        if(MPU6050_Get_ID() == 0x68) {
            connected++;
        }
        if(connected == 2) {
            break;
        }
    }
}
