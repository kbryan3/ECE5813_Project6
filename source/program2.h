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
#include "fsl_adc16.h"
#include "program1.h"
#include "led_control.h"
#include "circularbuffer.h"
#include "adc.h"
#include "dma.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

extern uint16_t dmaBuffer[64];
/**
* @brief updates DAC value every .1 seconds
*
*@return void
*/
void updateDAC_task(void *p);

/**
* @brief Transfers ADC values into a "DSP Buffer" every 64 samples
*
*@return void
*/
void transferADC_task(void *p);

#endif /*___PROGRAM2_H__*/
