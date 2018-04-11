/*
 *             i2c.c
 *
 *   Created on:  March 24, 2018
 *  Last Edited:  March 24, 2018
 *       Author:  Nick Gorab
 *        Board:  5994
 */


#include "i2c.h"

int     RX_Byte_Ctr;    // Coutner to make sure all of the information is received
int     TX_Byte_Ctr;    // Counter to make sure all of the information is sent
int i  = 0;             // Counting variable for the I2C interrupt
int v  = 0;             // Counting variable for the I2c interrupt
char    tx_buffer[6],     // Creates an array to store memory data
        rx_buffer[6];    // Data buffer which stores data to be sent


/*
 * Function: i2c_init
 * ------------------------------
 * Initializes both UCB1 and UCB2 I2C channels.
 */

void i2c_init(void) {
    /* UCB2 Initialization */
    P7SEL0    |= BIT0           // SDA line for I2C using UCB2
              |  BIT1;          // SCL line for I2C using UCB2
    UCB2CTLW0 |= UCSWRST;       // Enters reset state, USCI stops operation
    UCB2CTLW1 |= UCASTP_2;      // Sends stop bit when UCTBCNT is reached
    UCB2CTLW0 |= UCMST          // Master Mode
              |  UCMODE_3       // I2C Mode
              |  UCSSEL__SMCLK; // Synchronous Mode
    UCB2BRW    = 0x08;          // SMCLK/8
    UCB2CTLW0 &= ~UCSWRST;      // Exits reset mode, USCI enters operation
    UCB2IE    |= UCTXIE         // Data received interrupt enable
              |  UCRXIE;        // Data ready to transmit interrupt enable

    /* UCB1 Initialization */
    P1SEL0    |= BIT6           // SDA line for I2C using UCB2
              |  BIT7;          // SCL line for I2C using UCB2
    UCB1CTLW0 |= UCSWRST;       // Enters reset state, USCI stops operation
    UCB1CTLW1 |= UCASTP_2;      // Sends stop bit when UCTBCNT is reached
    UCB1CTLW0 |= UCMST          // Master Mode
              |  UCMODE_3       // I2C Mode
              |  UCSSEL__SMCLK; // Synchronous Mode
    UCB1BRW    = 0x08;          // SMCLK/8
    UCB1CTLW0 &= ~UCSWRST;      // Exits reset mode, USCI enters operation
    UCB1IE    |= UCTXIE         // Data received interrupt enable
              |  UCRXIE;        // Data ready to transmit interrupt enable
}


/*
 * Function: i2c_UCB2_single_write
 * -------------------------------
 * Writes a single byte of data through I2c using the UCB2 port
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which is to 
 *                        be written to.
 * @param data:           A pointer to an array which contains
 *                        the data being sent.
 */

void i2c_UCB2_single_write(char slave_address, char memory_address, char *tx_data) {
    UCB2I2CSA = slave_address;          // Sets slave address
    TX_Byte_Ctr = 2;                    // Sets the amount of bytes to be sent
    UCB2TBCNT  = 0x02;                  // Expecting to receive 2 bytes of data


    /* Loads the data into the tx_data buffer */
    tx_buffer[0] = memory_address;

    /* Iterates through the pointed array */
    unsigned int j = 0;
    for(j = 0; j < 1; j++) {
        tx_buffer[j + 1] = tx_data[j];     // Offset by 2 to avoid address overwrite
    }


    UCB2CTL1 |= UCTR                    // Enables TX Mode
             |  UCTXSTT;                // Sends start condition
    __bis_SR_register(LPM0_bits | GIE); // Enters Low-Power mode and enables global interrupt
}


/*
 * Function: i2c_UCB2_multiple_write
 * ---------------------------------
 * Writes multiple bytes of data through I2c using port UCB2
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being 
 *                        written to.
 * @param size:           The number of bytes which are going
 *                        to be sent.
 * @param data:           A pointer to an array which contains
 *                        the data being sent.
 */

void i2c_UCB2_multiple_write(char slave_address, char memory_address, int size, char *tx_data) {
    UCB2I2CSA = slave_address;          // Sets slave address
    TX_Byte_Ctr = 1 + size;             // Sets the amount of bytes to be sent
    UCB2TBCNT  = 1 + size;                  // Expecting to receive 2 bytes of data


    /* Loads the data into the tx_data buffer */
    tx_buffer[0] = memory_address;

    /* Iterates through the pointed array */
    unsigned int j = 0;
    for(j = 0; j < size; j++) {
        tx_buffer[j + 1] = tx_data[j];     // Offset by 2 to avoid address overwrite
    }


    UCB2CTL1 |= UCTR                    // Enables TX Mode
             |  UCTXSTT;                // Sends start condition
    __bis_SR_register(LPM0_bits | GIE); // Enters Low-Power mode and enables global interrupt
}


/*
 * Function: i2c_UCB2_single_read
 * ------------------------------
 * Reads a single byte of data over I2c using port UCB2. The data is stored
 * in the data_buffer attribute of the sensor_data struct.
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being
 *                        written to.
 */

void i2c_UCB2_single_read(int slave_address, char memory_address, char *rx_data) {
    UCB2I2CSA = slave_address;              // Sets slave address
    RX_Byte_Ctr = 1;                        // Sets the amount of bytes to be received
    TX_Byte_Ctr = 1;                        // Sets the amount of bytes to be sent
    i = 0;                                  // Counting variable set to zero
    tx_buffer[0] = memory_address;            // Loads LSB into sending buffer

    UCB2CTL1 |= UCTR                        // Enables TX Mode
             |  UCTXSTT;                    // Sends start condition
     __bis_SR_register(LPM0_bits | GIE);    // Enters Low-Power mode and enables global interrupt
    UCB2TBCNT  = 0x01;                      // Sets 1 byte of data to be sent
    __delay_cycles(8);                      // Delays cycles for unknown reason

    UCB2CTL1 &= ~UCTR;                      // Enters RX Mode
    UCB2CTL1 |= UCTXSTT;                    // Sends start condition
    __bis_SR_register(LPM0_bits | GIE);     // Enters Low-Power mode and enables global interrupt
}


/*
 * Function: i2c_UCB2_multiple_read
 * --------------------------------
 * Reads a single byte of data over I2c using port UCB2. The data is stored
 * in the data_buffer attribute of the sensor_data struct.
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being
 *                        written to.
 * @param size:           The amount of bytes you are expecting
 *                        to read from the slave.
 */

void i2c_UCB2_multiple_read(int slave_address, char memory_address, int size, char *rx_data) {
    UCB2I2CSA = slave_address;              // Sets slave address
    UCB2TBCNT  = 4;                         // Set to 4 to avoid stop condition
    RX_Byte_Ctr = size;                     // Sets the amount of bytes to be received
    TX_Byte_Ctr = 1;                        // Sets the amount of bytes to be sent
    i = 0;                                  // Counting variable set to zero
    tx_buffer[0] = memory_address;            // Loads LSB into sending buffer

    UCB2CTL1 |= UCTR                        // Enables TX Mode
             |  UCTXSTT;                    // Sends start condition
     __bis_SR_register(LPM0_bits | GIE);    // Enters Low-Power mode and enables global interrupt
    UCB2TBCNT  = 0x03;                      // Sets 1 byte of data to be sent
    __delay_cycles(8);                      // Delays cycles for unknown reason
    UCB2TBCNT  = size;
    UCB2CTL1 &= ~UCTR;                      // Enters RX Mode
    UCB2CTL1 |= UCTXSTT;                    // Sends start condition
    __bis_SR_register(LPM0_bits | GIE);     // Enters Low-Power mode and enables global interrupt
}



/*
 * Function: i2c_UCB1_single_write
 * -------------------------------
 * Reads a single byte of data over I2c using port UCB2. The data is stored
 * in the data_buffer attribute of the sensor_data struct.
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being
 *                        written to.
 * @param data:           A pointer to a 1-byte array containing 
 *                        the byte which is to be sent over I2C.
 */

void i2c_UCB1_single_write(char slave_address, char memory_address, char *tx_data) {
    UCB1I2CSA = slave_address;          // Sets slave address
    TX_Byte_Ctr = 2;                    // Sets the amount of bytes to be sent
    UCB1TBCNT  = 0x02;                  // Expecting to receive 2 bytes of data


    /* Loads the data into the tx_data buffer */
    tx_buffer[0] = memory_address;

    /* Iterates through the pointed array */
    unsigned int j = 0;
    for(j = 0; j < 1; j++) {
        tx_buffer[j + 1] = tx_data[j];     // Offset by 2 to avoid address overwrite
    }


    UCB1CTL1 |= UCTR                    // Enables TX Mode
             |  UCTXSTT;                // Sends start condition
    __bis_SR_register(LPM0_bits | GIE); // Enters Low-Power mode and enables global interrupt
}


/*
 * Function: i2c_UCB1_multiple_write
 * ---------------------------------
 * Writes multiple bytes of data through I2C using port UCB1
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being 
 *                        written to.
 * @param size:           The number of bytes which are going
 *                        to be sent.
 * @param data:           A pointer to an array which contains
 *                        the data being sent.
 */

void i2c_UCB1_multiple_write(char slave_address, char memory_address, int size, char *tx_data) {
    UCB1I2CSA = slave_address;          // Sets slave address
    TX_Byte_Ctr = 1 + size;             // Sets the amount of bytes to be sent
    UCB1TBCNT  = 1 + size;                  // Expecting to receive 2 bytes of data


    /* Loads the data into the tx_data buffer */
    tx_buffer[0] = memory_address;

    /* Iterates through the pointed array */
    unsigned int j = 0;
    for(j = 0; j < size; j++) {
        tx_buffer[j + 1] = tx_data[j];     // Offset by 2 to avoid address overwrite
    }


    UCB1CTL1 |= UCTR                    // Enables TX Mode
             |  UCTXSTT;                // Sends start condition
    __bis_SR_register(LPM0_bits | GIE); // Enters Low-Power mode and enables global interrupt
}



/*
 * Function: i2c_UCB1_single_read
 * ------------------------------
 * Reads a single byte of data over I2C using port UCB1. The data is stored
 * in the data_buffer attribute of the sensor_data struct.
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being
 *                        written to.
 */


void i2c_UCB1_single_read(int slave_address, char memory_address, char *rx_data) {
    UCB1I2CSA = slave_address;              // Sets slave address
    RX_Byte_Ctr = 1;                        // Sets the amount of bytes to be received
    TX_Byte_Ctr = 1;                        // Sets the amount of bytes to be sent
    i = 0;                                  // Counting variable set to zero
    tx_buffer[0] = memory_address;            // Loads LSB into sending buffer

    UCB1CTL1 |= UCTR                        // Enables TX Mode
             |  UCTXSTT;                    // Sends start condition
     __bis_SR_register(LPM0_bits | GIE);    // Enters Low-Power mode and enables global interrupt
    UCB1TBCNT  = 0x01;                      // Sets 1 byte of data to be sent
    __delay_cycles(8);                      // Delays cycles for unknown reason

    UCB1CTL1 &= ~UCTR;                      // Enters RX Mode
    UCB1CTL1 |= UCTXSTT;                    // Sends start condition
    __bis_SR_register(LPM0_bits | GIE);     // Enters Low-Power mode and enables global interrupt
}



/*
 * Function: i2c_UCB1_multiple_read
 * --------------------------------
 * Reads a single byte of data over I2C using port UCB1. The data is stored
 * in the data_buffer attribute of the sensor_data struct.
 *
 * @param slave_address:  The address of the slave device
 *                        which is being targeted.
 * @param memory_address: The memory location which being
 *                        written to.
 * @param size:           The amount of bytes you are expecting
 *                        to read from the slave.
 */

void i2c_UCB1_multiple_read(int slave_address, char memory_address, int size, char *rx_data) {
    UCB1I2CSA = slave_address;              // Sets slave address
    UCB1TBCNT  = 4;                         // Set to 4 to avoid stop condition
    RX_Byte_Ctr = size;                     // Sets the amount of bytes to be received
    TX_Byte_Ctr = 1;                        // Sets the amount of bytes to be sent
    i = 0;                                  // Counting variable set to zero
    tx_buffer[0] = memory_address;            // Loads LSB into sending buffer

    UCB1CTL1 |= UCTR                        // Enables TX Mode
             |  UCTXSTT;                    // Sends start condition
     __bis_SR_register(LPM0_bits | GIE);    // Enters Low-Power mode and enables global interrupt
    UCB1TBCNT  = 0x03;                      // Sets 1 byte of data to be sent
    __delay_cycles(8);                      // Delays cycles for unknown reason
    UCB1TBCNT  = size;
    UCB1CTL1 &= ~UCTR;                      // Enters RX Mode
    UCB1CTL1 |= UCTXSTT;                    // Sends start condition
    __bis_SR_register(LPM0_bits | GIE);     // Enters Low-Power mode and enables global interrupt
}




/* Interrupt vector for UCB2 vector */
#pragma vector = EUSCI_B2_VECTOR
__interrupt void USCI_B2_ISR(void) {
    switch(__even_in_range(UCB2IV, USCI_I2C_UCBIT9IFG)) {

        case USCI_I2C_UCRXIFG0:                             // I2C RX Interrupt
            if(RX_Byte_Ctr > 1){                            // Checks if there is more data to be received
                rx_buffer[v] = UCB2RXBUF; // Loads the data array
                v++;                                        // Increments the pointer
                RX_Byte_Ctr--;                              // Decrement TX byte counter
            } else if (RX_Byte_Ctr == 1){
                rx_buffer[v] = UCB2RXBUF; // Loads the data array
                v++;                                        // Increments the pointer
                RX_Byte_Ctr--;
                v=0;
                __bic_SR_register_on_exit(LPM0_bits);       // Exit LPM0
            }
        break;

        case USCI_I2C_UCTXIFG0:                       // I2C TX Interrupt
            if(TX_Byte_Ctr > 1){
                UCB2TXBUF = tx_buffer[i];               // Example send
                i++;
                TX_Byte_Ctr--;
            } else if (TX_Byte_Ctr == 1){
                UCB2TXBUF = tx_buffer[i];               // Example send
                TX_Byte_Ctr--;
                i = 0;
                __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
            }
        break;
}   }


/* Interrupt vector for UCB1 vector */
#pragma vector = EUSCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void) {
    switch(__even_in_range(UCB1IV, USCI_I2C_UCBIT9IFG)) {

        case USCI_I2C_UCRXIFG0:                             // I2C RX Interrupt
            if(RX_Byte_Ctr > 1){                            // Checks if there is more data to be received
                rx_buffer[v] = UCB1RXBUF;   // Loads the data array
                v++;                                        // Increments the pointer
                RX_Byte_Ctr--;                              // Decrement TX byte counter
            } else if (RX_Byte_Ctr == 1){
                rx_buffer[v] = UCB1RXBUF;   // Loads the data array
                v++;                                        // Increments the pointer
                RX_Byte_Ctr--;
                v=0;
                __bic_SR_register_on_exit(LPM0_bits);   // Exit LPM0
            }
        break;

        case USCI_I2C_UCTXIFG0:                         // I2C TX Interrupt
            if(TX_Byte_Ctr > 1){
                UCB1TXBUF = tx_buffer[i];                // Example send
                i++;
                TX_Byte_Ctr--;
            } else if (TX_Byte_Ctr == 1){
                UCB1TXBUF = tx_buffer[i];                // Example send
                TX_Byte_Ctr--;
                i = 0;
                __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0
            }
        break;
}   }
