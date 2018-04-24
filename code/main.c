#include <msp430.h> 
#include "comms.h"
#include "project_settings.h"
#include "subsystem.h"
#include "task.h"
#include "uart.h"
#include "hal_general.h"
#include "system.h"
#include "led_driver.h"
#include "bluetooth.h"

int target_height = 0;
int Kp = 0;
int Ki = 0;
int Kd = 0;
int past_error = 0;
uint16_t data = 0;
int pwm = 0;


void Blink_Setup();
void Blink();
void Sensor_Connection_Test(void);




/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    DisableInterrupts();

    LED_Init();
    LED_Power_On();
    Timing_Init();
    Task_Init();
    BLUETOOTH_Init();
    COMMS_Init();
    PWM_Initialize();
    i2c_init();

    EnableInterrupts();

    VCNL4200_Start_PS();
    LED_Party();


//   Task_Schedule(PID_Update, 0, 0, 400);

    while(1){
        SystemTick();
    }
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

#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void) {

    static int current_edge = 0;
    LED_Bluetooth_Toggle();
    Status_DisableInterrupt();
    Status_EnableInterrupt(current_edge);

    if(current_edge){
        current_edge = 0;
    }
    else {
        current_edge = 1;
    }

    Status_ClearFlag();
}
