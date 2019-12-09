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

static void timerLEDOff(TimerHandle_t xTimer);

void updateDAC_task(void *p)
{
	uint16_t count = 0;
	while(1)
	{
		log_string((uint8_t*)"Starting Task", DBUG, UPDATEDAC_TASK);
		//check if mutex is available
		if(uxSemaphoreGetCount(xLEDMutex))
		{
			toggleLED(1);
		}
		DAC_SetBufferValue(DAC0, 0U, dacVal[count++]);
		if(count >=50)
		{
			count = 0;
		}
		//check if mutex is available
		if(uxSemaphoreGetCount(xLEDMutex))
		{
			toggleLED(3);
		}
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
	TimerHandle_t ledTimer;
	ledTimer = xTimerCreate("LED_Timer",500,pdFALSE,0,timerLEDOff);
	while(1)
	{
		log_string((uint8_t*)"Starting Task", DBUG, TRANSFERADC_TASK);
		//check if the LED has been on for .5 seconds and can be released
		if(	g_halfsecond == 1)
		{
			xSemaphoreGive(xLEDMutex);
			g_halfsecond = 0;
		}
		else
		{

			ADC16_SetChannelConfig(ADC0, 0U, &adc16ChannelConfigStruct);
			Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC0, 0U);
			add(buffer_ADC, Adc16ConversionValue);
			if(buffIsFull(buffer_ADC) == BUFFER_FULL)
			{
				add(buffer_ADC, Adc16ConversionValue);
				xSemaphoreTake(xLEDMutex, (TickType_t) 0);
				toggleLED(2);
				xTimerStart(ledTimer, 0);
				//following DMA code is edited version of the SDK dma example
				DMA_PrepareTransfer(&transferConfig, buffer_ADC->buffer, sizeof(uint16_t),
						dmaBuffer, sizeof(uint16_t), (uint32_t)(buffer_ADC->length*2)
						,kDMA_MemoryToMemory);
				DMA_SubmitTransfer(&DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
				log_string((uint8_t*)"Starting DMA Transfer: ", STATUS, TRANSFERADC_TASK);
				log_string((uint8_t*)"Starting DMA Transfer: ", DBUG, TRANSFERADC_TASK);
				DMA_StartTransfer(&DMA_Handle);
				/* Wait for DMA transfer finish */
				while (g_Transfer_Done != true)
				{
				}
				log_string((uint8_t*)"DMA Transfer Complete: ", STATUS, TRANSFERADC_TASK);
				log_string((uint8_t*)"DMA Transfer Complete: ", DBUG, TRANSFERADC_TASK);
				initCircBuffer(buffer_ADC, adcVals, 64);
			}
		}
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}

void processSignal_task(void *p)
{
	uint16_t max;
	uint16_t min;
	uint32_t sum;
	uint16_t average;
	uint64_t stand_dev;
	uint8_t runs = 0;
	float stand_devf;
	float maxVal;
	float minVal;
	float averageVal;
	float stand_devVal;
	while(1)
	{
		log_string((uint8_t*)"Starting Task", DBUG, PROCESSSIGNAL_TASK);
		if(g_Transfer_Done == true)
		{
			g_Transfer_Done = false;
			max = 0;
			min = 5000;
			sum = 0;
			average = 0;
			stand_dev = 0;
			stand_devf = 0.0;
			maxVal = 0.0;
			minVal = 5000.0;
			averageVal = 0.0;
			stand_devVal = 0.0;

			for(uint8_t i=0; i<64; i++)
			{
				//max value
				if(max < dmaBuffer[i])
				{
					max = dmaBuffer[i];
				}
				//min value
				if(min > dmaBuffer[i])
				{
					min = dmaBuffer[i];
				}
				//sum of values
				sum += dmaBuffer[i];
			}

			average = sum/64;
//found std deviation algorithm from www.programiz.com/c-programming/examples/standard-deviation
			for(uint8_t i = 0; i<64; i++)
			{
				stand_dev += pow((dmaBuffer[i])-average,2);
			}

			stand_devf = sqrtf(((float)stand_dev)/64.0);

			maxVal = max*3.3f/4096.0f;
			minVal = min*3.3f/4096.0f;
			averageVal = average*3.3f/4096.0f;
			stand_devVal = stand_devf*3.3f/4096.0f;
			runs++;
			PRINTF("Run Number: %d\n\rMax: %f\n\rMin: %f\n\rAverage: %f\n\r"
					"SD: %f\n\r\n\r\n\r",runs, maxVal, minVal, averageVal, stand_devVal);

			if(runs >= 5)
			{
				vTaskEndScheduler();
			}
		}

		vTaskDelay(500/portTICK_PERIOD_MS);
	}

}

static void timerLEDOff(TimerHandle_t xTimer)
{
	toggleLED(3);
	g_halfsecond = 1;
}


