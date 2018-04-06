#include <msp430.h> 
#include "project_settings.h"
#include "subsystem.h"
#include "task.h"
#include "uart.h"
#include "hal_general.h"
#include "system.h"

void Blink_Setup();
void Blink();
void Data_Struct_Init(sensdat_t* sendat);
void Sensor_Connection_Test(sensdat_t* sensdat);




/* Global struct deceleration */
sensdat_t sensor_data;






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
        Data_Struct_Init(&sensor_data);

        VCNL4200_Start_PS();

while(1) {

    __delay_cycles(30000);

    VCNL4200_Set_LED_I();
    VCNL4200_Get_PS_Data(&sensor_data);
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
 * Function: Data_Struct_Init
 * --------------------------
 * Initializes the data structure for the
 * storage of the sensor data. 
 *
 * @param sensdat:  Pointer to the struct
 *                  which is to be initialized.
 */

void Data_Struct_Init(sensdat_t* sendat) {

    sensdat = sensdat;

    int i = 0;
    for(i = 0; i <= sizeof(sensdat->data_buffer); i++) {
        sensdat->data_buffer[i] = 0x00;
    }

    sensdat->x_accel   = 0;
    sensdat->y_accel   = 0;
    sensdat->z_accel   = 0;
    sensdat->prox_data = 0;

    return;
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

void Sensor_Connection_Test(sensdat_t* sensdat) {
    int connected = 0;
    while(1) {
        if(VCNL4200_Get_ID(sensdat) == 0x5810) {
            connected++;
        }
        if(MPU6050_Get_ID(sensdat) == 0x68) {
            connected++;
        }
        if(connected == 2) {
            break;
        }
    }
}
