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

void transferADC_task(void *p)
{
    //Create circular buffers
    CIRCBUFF * buffer_ADC = (CIRCBUFF *)malloc(22);
    uint16_t * adcVals = (uint16_t *)malloc(64);
    CIRCBUFF * buffer_DMA = (CIRCBUFF *)malloc(22);
    uint16_t * dmaVals = (uint16_t *)malloc(64);
    initCircBuffer(buffer_ADC, adcVals, 64);
    initCircBuffer(buffer_DMA, dmaVals, 64);
	uint16_t Adc16ConversionValue;
	while(1)
	{
		ADC16_SetChannelConfig(ADC0, 0U, &adc16ChannelConfigStruct);
		Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC0, 0U);
		add(buffer_ADC, Adc16ConversionValue);
/*		if(buffIsFull(buffer_ADC) == BUFFER_FULL)
		{
			while(buffIsEmpty(buffer_ADC)!=BUFFER_EMPTY)
			{
				toggle
				add(buffer_DMA, removeItem(buffer_ADC));
			}
		} */

		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}
