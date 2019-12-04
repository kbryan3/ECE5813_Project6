 /********************************************************************
*
* @file program2.c
* @brief Contains functions to read and write values to DAC/ADC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/
#include "program2.h"

void updateDAC_task(void *p)
{
	uint16_t count = 0;
	while(1)
	{
		toggleLED(1);
		DAC_SetBufferValue(DAC0, 0U, dacVal[count++]);
		if(count >=50)
		{
			count = 0;
		}
		toggleLED(3);
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}
