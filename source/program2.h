 /********************************************************************
*
* @file program2.h
* @brief Contains functions to read and write values to DAC/ADC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/
#ifndef __PROGRAM2_H__
#define __PROGRAM2_H__

#include <stdio.h>
#include <math.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_dac.h"
#include "program1.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/**
* @brief updates DAC value every .1 seconds
*
*@return void
*/
void updateDAC_task(void *p);

#endif /*___PROGRAM2_H__*/
