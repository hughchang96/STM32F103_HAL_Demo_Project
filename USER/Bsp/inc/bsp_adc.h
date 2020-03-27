/**
  ******************************************************************************
  * @file    bsp_adc.h
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

#ifndef  __BSP_ADC_H__
#define  __XXX_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"
#if(STM_ADC)

#include "stm32f1xx_hal.h"

/* Exported_Functions --------------------------------------------------------*/
uint32_t Get_ADC_Value_Pool(ADC_HandleTypeDef *hadcx);
void Get_ADC_Value_DMA(ADC_HandleTypeDef* hadcx,uint32_t *Value_buff , uint16_t Channel_Number, uint32_t Length);

/* Exported constants --------------------------------------------------------*/

#endif //ADC
#endif //__BSP_ADC_H__
