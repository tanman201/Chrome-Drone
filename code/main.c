#include <msp430.h> 
#include "project_settings.h"
#include "subsystem.h"
#include "task.h"
#include "uart.h"
#include "hal_general.h"

void Blink_Setup();
void Blink();

/**
 * main.c
 */
int main(void)
{

    PM5CTL0 &= ~LOCKLPM5;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    DisableInterrupts();

    Task_Init();
 //   UART_Init(SUBSYSTEM_UART);

    Blink_Setup();

    EnableInterrupts();

    Task_Schedule(Blink, 0, 0, 1000);

    while(1) {
        SystemTick();
    }
}

void Blink_Setup(){
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction
}

void Blink(){
    P1OUT ^= BIT0;                      // Toggle LED
}
