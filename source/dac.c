 /********************************************************************
*
* @file dac.c
* @brief Contains functions to init DAC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/

#include "dac.h"

void initDAC()
{
    dac_config_t dacConfigStruct;
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DAC0, &dacConfigStruct);
    DAC_Enable(DAC0, true);
}
