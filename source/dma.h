 /********************************************************************
*
* @file dma.h
* @brief Contains functions to init DMA
*
*
*
* @author Kyle Bryan
* @date December 2019
* version 1.0
*
***********************************************************************/
#ifndef __DMA_H__
#define __DMA_H__

#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "fsl_debug_console.h"
#include <stdio.h>

extern	dma_handle_t DMA_Handle;
extern  dma_transfer_config_t transferConfig;
extern volatile bool g_Transfer_Done;

/**
* @brief initializes DMA
*
*@return void
*/
void initDMA();

/**
* @brief User callback function for DMA transfer.
*
* @param dma_handle_t *handle pointer to dma handler
* @param void *param required void pointer parameter
*/
void DMA_Callback(dma_handle_t *handle, void *param);

#endif /*__DMA_H__*/
