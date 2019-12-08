 /********************************************************************
*
* @file adc.c
* @brief Contains functions to init ADC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/

#include "adc.h"

//initialization was taken from the SDK's DAC_ADC example
void initADC()
{
	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	adc16ConfigStruct.enableContinuousConversion = 1;
	ADC16_Init(ADC0, &adc16ConfigStruct);


#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
    {
        PRINTF("\r\nADC16_DoAutoCalibration() Done\r\n.");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    /* Prepare ADC channel setting */
    adc16ChannelConfigStruct.channelNumber = 0U;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}
