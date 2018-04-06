/*
 *             system.h
 *
 *   Created on:  March 24, 2018
 *  Last Edited:  March 28, 2018
 *       Author:  Nick Gorab
 * 
 *  This file is used for all the includes 
 *  found in this project to simplify everything
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>
#include <msp430.h>

/* Structure definition for storing sensor data */
typedef struct {
    char data_buffer[6];
    int      x_accel;
    int      y_accel;
    int      z_accel;
    uint16_t prox_data;
} sensdat_t;

sensdat_t* sensdat;

/* Global variable decleration */
extern sensdat_t sensor_data;

/* 
 * These include files need to be below the
 * struct definition because they reference
 * the global decleration. 
 */

#include "i2c.h"
#include "mpu6050.h"
#include "vcnl4200.h"
#include "led_driver.h"


#endif /* SYSTEM_H_ */
