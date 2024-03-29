/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    test.c
 * @brief   Application entry point.
 */
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
#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "program1.h"
#include "program2.h"
#include "dac.h"
#include "adc.h"
#include "led_control.h"
#include "defines.h"
#include "dma.h"
#include "logger.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* TODO: insert other definitions and declarations here. */
/* The software timer period. */
#define SW_TIMER_PERIOD_MS (69 / portTICK_PERIOD_MS)
uint16_t dacVal[50];
uint16_t count;
logger_level log_level;
_Bool log_a;
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
dma_handle_t DMA_Handle;
dma_transfer_config_t transferConfig;
volatile bool g_Transfer_Done;
uint16_t dmaBuffer[64];
bool g_dma_done_flag;
bool g_halfsecond;
SemaphoreHandle_t xLEDMutex;
uint32_t g_ticks;

#ifdef PROGRAM1
/* The callback function. */
static void SwTimerCallback(TimerHandle_t xTimer);
#endif

/*
 * @brief   Application entry point.
 */
int main(void) {

#ifdef PROGRAM1
	TimerHandle_t SwTimerHandle = NULL;
#endif
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    initializeLEDs();
    log_a = 1;
    g_ticks = 0;
#ifdef STATUS
    log_level = 2;
#else
    log_level = 1;
#endif

    g_Transfer_Done = false;
	g_halfsecond = 0;
    g_dma_done_flag = 0;
    xLEDMutex = xSemaphoreCreateMutex();

    //initialize DAC
    initDAC();
    log_string((uint8_t*)"Initialized DAC: ",DBUG, MAIN);

    //generate values for DAC
    genDACValues((uint16_t *) &dacVal);
#ifndef PROGRAM1
    //initialize ADC
    initADC();
    log_string((uint8_t*)"Initialized ADC: ",DBUG, MAIN);

    //initialize DMA
    initDMA();
    log_string((uint8_t*)"Initialized DMA: ",DBUG, MAIN);


    xTaskCreate(updateDAC_task, (portCHAR *)"updateDAC_task", configMINIMAL_STACK_SIZE + 10,
    		NULL, 3, NULL);

    xTaskCreate(transferADC_task, (portCHAR *)"transferADC_task", configMINIMAL_STACK_SIZE + 10,
        		NULL, 2, NULL);

    xTaskCreate(processSignal_task, (portCHAR *)"processSignal_task", configMINIMAL_STACK_SIZE + 500,
        		NULL, 1, NULL);

    vTaskStartScheduler();
#endif


#ifdef PROGRAM1
    count = 0;
    SystemCoreClockUpdate();
    /* Create the software timer. */
    SwTimerHandle = xTimerCreate("SwTimer",          /* Text name. */
    							 SW_TIMER_PERIOD_MS, /* Timer period. */
                                 pdTRUE,             /* Enable auto reload. */
                                 0,                  /* ID is not used. */
                                 SwTimerCallback);   /* The callback function. */
   /* Start timer. */
   xTimerStart(SwTimerHandle, 0);
   /* Start scheduling. */
   vTaskStartScheduler();
#endif

    /* Enter an infinite loop*/
    while(1)
    {

    }
}

#ifdef PROGRAM1
static void SwTimerCallback(TimerHandle_t xTimer)
{
	toggleLED(2);
    DAC_SetBufferValue(DAC0, 0U, dacVal[count++]);
    if(count >=50)
    {
    	count = 0;
    }
    toggleLED(3);
}
#endif
