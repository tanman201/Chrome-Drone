/*
 * project_settings.h
 *
 *  Created on: April 5, 2018
 *      Author: Tanner Smith
 */

#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#define FCPU 1000000

// include the library header
#include "library.h"
// let the system know which lower level modules are in use
// this way higher modules can selectively utilize their resources
#define USE_MODULE_TASK
#define USE_MODULE_SUBSYSTEM
#define USE_MODULE_BUFFER_PRINTF
#define USE_MODULE_UART

#define SUBSYSTEM_UART 0

#define UART0_TX_BUFFER_LENGTH 256

#define USE_UART0

#define TASK_MAX_LENGTH 20

#endif /* PROJECT_SETTINGS_H */
