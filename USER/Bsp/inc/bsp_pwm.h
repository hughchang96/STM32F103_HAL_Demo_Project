/**
  ******************************************************************************
  * @file    bsp_pwm.h
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

#ifndef  __BSP_PWM_H__
#define  __BSP_PWM_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"

#if(PWM)
#include "main.h"

/* Exported_Functions --------------------------------------------------------*/
void Pwm_SetValue(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t value);

/* Exported constants --------------------------------------------------------*/

#endif //PWM
#endif //__BSP_PWM_H__

