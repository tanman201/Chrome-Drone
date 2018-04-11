/*
 *            mpu6050.c
 *
 *   Created on:  March 24, 2017
 *  Last Edited:  March 28, 2017
 *       Author:  Nick Gorab
 *        
 *  This code is used for interfacing with the
 *  MPU6050 Gyro/Accelerometer used for this project.
 */


#include "mpu6050.h"


/*
 * Function: MPU6050_Wake_Up
 * -------------------------
 * Wakes up the MPU6050 by writing all zeros to the power
 * managment register.
 * 
 */

void MPU6050_Wake_Up(void) {
    char data[1] = {0};
    i2c_UCB2_single_write(MPU6050_ADDRESS_LOW, PWR_MGMT_1, data);
}



/*
 * Function: MPU6050_Get_ID
 * ------------------------
 * Returns the device ID for the MPU6050. Can be used
 * to make sure that the device is properly connected.
 *
 * @param sensdat:  Sensor data structure is used as an
 *                  argument so the I2c code can use the
 *                  data_buffer included in the struct
 *                  to store the incoming information.
 * @param return:   Returns a single byte of data which
 *                  represents the data address. It should
 *                  always read 0x68.
 */

char MPU6050_Get_ID(void) {
    char device_id[1] = {0};

    i2c_UCB2_single_read(MPU6050_ADDRESS_LOW, MPU6050_ID, device_id);

    return device_id[0];
}



/*
 * Function: MPU6050_Get_Accel
 * ---------------------------
 * Gets the current acceleration data from the
 * x, y, and z registers of the MPU6050.
 *
 * @param sensdat:  Sensor data structure is used as an
 *                  argument so the I2c code can use the
 *                  data_buffer included in the struc.
 *                  Additionally, separate variables are
 *                  included to store the accel. data.
 */

void MPU6050_Get_Accel(int *x_accel, int *y_accel, int *z_accel) {
  char accel_data[6] = {0};
  char msb, lsb;

  /* Reads the accelerometer data */
    i2c_UCB2_multiple_read(MPU6050_ADDRESS_LOW, ACCEL_DATA, 6, accel_data);

    /* Determining X acceleration */
    lsb = accel_data[1];
    msb = accel_data[0];
    x_accel = ((msb << 8) | lsb);

    /* Determining y acceleration */
    lsb = accel_data[3];
    msb = accel_data[2];
    y_accel = ((msb << 8) | lsb);

    /* Determining z acceleration */
    lsb = accel_data[5];
    msb = accel_data[4];
    z_accel = ((msb << 8) | lsb);
}



/*
 * Function: MPU6050_Calibrate_Accel
 * ---------------------------------
 * Zeros out the accelerometer readings for the current 
 * attitude of the accelerometer. This should be used 
 * every time the program is run to ensure good data
 *
 * @param sensdat:  Function reads from the x, y, and z
 *                  accelerometer variables in the struct
 *                  to create a mean value of accel data.
 */

void MPU6050_Calibrate_Accel(void) {
    P1OUT |= BIT1;      // Turns on status LED for calibration

    /* Varibales used to store the mean accelerometer data */
    int x_mean = 0;
    int y_mean = 0;
    int z_mean = 0;

    MPU6050_Mean_Accel(&x_mean, &y_mean, &z_mean);

    int x_offset = -x_mean/8;
    int y_offset = -y_mean/8;
    int z_offset = (16384-z_mean)/8;

    while(1) {
    int calibrated = 0; 

        /* Sets the new offsets */
        Set_X_Accel_Offset(x_offset);
        Set_Y_Accel_Offset(y_offset);
        Set_Z_Accel_Offset(z_offset);

        MPU6050_Mean_Accel(&x_mean, &y_mean, &z_mean);

        /* Checks to see if the means are within the limits */
        if(abs(x_mean)<=ACCEL_DEADZONE) {
            calibrated++;
        } else {
            x_offset = x_offset - x_mean/ACCEL_DEADZONE;
        }

        if(abs(y_mean)<=ACCEL_DEADZONE) {
            calibrated++;
        } else {
            y_offset = y_offset - y_mean/ACCEL_DEADZONE;
        }

        if(abs(16384-z_mean)<=ACCEL_DEADZONE) {
            calibrated++;
        } else {
            z_offset = z_offset + (16384-z_mean)/ACCEL_DEADZONE;
        }

        /* If all of the axis pass calibration */
        if(calibrated == 3) {
            break;
        }
    }
}



/*
 * Function: MPU6050_Mean_Accel
 * ----------------------------
 * Returnes the average value of the accelerometer 
 * after 100 consequtive readings. 
 *
 * @param sensdat:  Used to reference the current x, y, and z
 *                  accelerometer data.
 * @param x_mean:   Pointer to the average x acceleration variable.
 * @param y_mean:   Pointer to the average y acceleration variable.
 * @oaram z_mean:   Pointer to the average z acceleration variable.
 */

void MPU6050_Mean_Accel(int* x_mean, int* y_mean, int* z_mean) {

   uint32_t x_accel_buffer = 0;
   uint32_t y_accel_buffer = 0;
   uint32_t z_accel_buffer = 0;
   int x_accel, y_accel, z_accel;

   int i = 0;
   while(i < (CALIB_BUF_SIZE+1)) {
       MPU6050_Get_Accel(&x_accel, &y_accel, &z_accel);
       x_accel_buffer += x_accel;
       y_accel_buffer += y_accel;
       z_accel_buffer += z_accel;
       i++;
       __delay_cycles(2); // Delays so is won't read the same data from MPU6050
    }

    /* Uses the pointers to set the mean values */
    *x_mean = x_accel_buffer/CALIB_BUF_SIZE;
    *y_mean = y_accel_buffer/CALIB_BUF_SIZE;
    *z_mean = z_accel_buffer/CALIB_BUF_SIZE;
}



/*
 * Function: Set_X_Accel_Offset
 * ----------------------------
 * Sets the offset register of the x-axis for the MPU6050.
 *
 * @param offset:   Value in which the x-axis of the MPU6050
 *                  will be offset by.
 */

void MPU6050_Set_X_Accel_Offset(int offset) {
    int MSB = offset >> 8;
    int LSB = offset & 0xFF;

    char offset_data[2] = {MSB, LSB};

    i2c_UCB2_multiple_write(MPU6050_ADDRESS_LOW, X_OFFSET_ADDRESS, 2, offset_data);
}



/*
 * Function: Set_Y_Accel_Offset
 * ----------------------------
 * Sets the offset register of the y-axis for the MPU6050.
 *
 * @param offset:   Value in which the y-axis of the MPU6050
 *                  will be offset by.
 */

void MPU6050_Set_Y_Accel_Offset(int offset) {
    int MSB = offset >> 8;
    int LSB = offset & 0xFF;

    char offset_data[2] = {MSB, LSB};

    i2c_UCB2_multiple_write(MPU6050_ADDRESS_LOW, Y_OFFSET_ADDRESS, 2, offset_data);
}



/*
 * Function: Set_Z_Accel_Offset
 * ----------------------------
 * Sets the offset register of the z-axis for the MPU6050.
 *
 * @param offset:   Value in which the z-axis of the MPU6050
 *                  will be offset by.
 */
void MPU6050_Set_Z_Accel_Offset(int offset) {
    int MSB = offset >> 8;
    int LSB = offset & 0xFF;

    char offset_data[2] = {MSB, LSB};

    i2c_UCB2_multiple_write(MPU6050_ADDRESS_LOW, Z_OFFSET_ADDRESS, 2, offset_data);
}



