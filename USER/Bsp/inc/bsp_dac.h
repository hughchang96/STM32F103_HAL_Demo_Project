/**
  ******************************************************************************
  * @file    bsp_dac.h
  * @author  ’≈ª¢
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
*/

#ifndef  __BSP_DAC_H__
#define  __BSP_DAC_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"
#if(STM_DAC)

#include "stm32f1xx_hal.h"

/* Exported_Functions --------------------------------------------------------*/
void DAC_Output(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);
void DAC_Output_Wave(TIM_HandleTypeDef *htimx, DAC_HandleTypeDef *hdac, uint32_t Channel);

/* Exported constants --------------------------------------------------------*/

#endif //STM_DAC
#endif //__BSP_DAC_H__
