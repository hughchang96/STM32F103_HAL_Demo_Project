/**
  ******************************************************************************
  * @file    app_adc.h
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

#ifndef  __APP_ADC_H__
#define  __APP_ADC_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"
#if(STM_ADC)

#include "stm32f1xx_hal.h"

/* Exported_Functions --------------------------------------------------------*/
void App_Temperature_Light_Poll(void);
void App_Temperature_Light_Dma(void);

/* Exported constants --------------------------------------------------------*/

#endif //STM_ADC
#endif //__APP_ADC_H__

