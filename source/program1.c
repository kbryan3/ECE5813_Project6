 /********************************************************************
*
* @file program1.c
* @brief Contains functions to create a sinusoid to feed a DAC
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/

#include "program1.h"

void genDACValues(uint16_t * dacValues)
{

	float waveVal;
	//calculate sine Values
    for(uint8_t i = 0; i < 50; i++)
    {
    	waveVal =  sin(((float)(i)/10.0f)*2.0f*M_PI/5.0f)+2.0f; //calculate sinewave
    	dacValues[i] = (uint16_t)(waveVal * 4096.0f / 3.3f); //convert to DAC Reg value
    }
    log_string((uint8_t*)"Generate DAC Values", DBUG, GENDACVALUES);
}

