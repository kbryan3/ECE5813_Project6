 /********************************************************************
*
* @file program1.h
* @brief Contains functions to create a sinusoid to feed a DAC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/
#ifndef __PROGRAM1_H__
#define __PROGRAM1_H__

#include <stdio.h>
#include <math.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_dac.h"
#include "logger.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#ifndef M_PI
	#define	M_PI 3.14159265358979323846
#endif

extern uint16_t dacVal[50];
/**
* @brief Generates a sinusoid values for DAC
*
*@param uint16_t * dacValues a pointer to values for DAC
*@return void
*/
void genDACValues(uint16_t * dacValues);

#endif /*___PROGRAM1_H__*/
