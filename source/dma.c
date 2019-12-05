 /********************************************************************
*
* @file dma.c
* @brief Contains functions to init DMA
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/

#include "dma.h"

void initDMA()
{
	/* Configure DMAMUX */
	DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, 0, 63);
    DMAMUX_EnableChannel(DMAMUX0, 0);
    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&DMA_Handle, DMA0, 0);
    DMA_SetCallback(&DMA_Handle, DMA_Callback, NULL);
}

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
}
