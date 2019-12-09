 /********************************************************************
*
* @file adc.h
* @brief Contains functions to init ADC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#include "fsl_adc16.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include "logger.h"

extern	adc16_config_t adc16ConfigStruct;
extern  adc16_channel_config_t adc16ChannelConfigStruct;

/**
* @brief initializes ADC
*
*@return void
*/
void initADC();

#endif /*__ADC_H__*/
