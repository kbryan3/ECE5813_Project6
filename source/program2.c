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
    initCircBuffer(buffer_ADC, adcVals, 64);
	uint16_t Adc16ConversionValue;
	while(1)
	{
		ADC16_SetChannelConfig(ADC0, 0U, &adc16ChannelConfigStruct);
		Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC0, 0U);
		add(buffer_ADC, Adc16ConversionValue);
		if(buffIsFull(buffer_ADC) == BUFFER_FULL)
		{
			DMA_PrepareTransfer(&transferConfig, buffer_ADC->buffer, sizeof(uint16_t),
					dmaBuffer, sizeof(uint16_t), (uint32_t)buffer_ADC->length
					,kDMA_MemoryToMemory);
    		DMA_SubmitTransfer(&DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
    		DMA_StartTransfer(&DMA_Handle);
    		/* Wait for DMA transfer finish */
			while (g_Transfer_Done != true)
			{
			}
			g_Transfer_Done = false;
			initCircBuffer(buffer_ADC, adcVals, 64);
		}

		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}
