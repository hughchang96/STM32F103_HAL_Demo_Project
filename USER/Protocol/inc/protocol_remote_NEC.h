/**
  ******************************************************************************
  * @file    protocol_remote_NEC.h
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

#ifndef  __PROTOCOL_REMOTE_NEC_H__
#define  __PROTOCOL_REMOTE_NEC_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"
#if(PWM_IN_INFRARED)

#include "stm32f1xx_hal.h"

/* definition constant  --------------------------------------------------------*/

#define INFRARED_RECV_STATE 	HAL_GPIO_ReadPin(INFRARED_RECV_GPIO_Port, INFRARED_RECV_Pin)

/* Exported_Functions --------------------------------------------------------*/
void Remote_Nec_CaptureCallback(TIM_HandleTypeDef *htim);
void Remote_Nec_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

/* Exported constants --------------------------------------------------------*/

#endif //PWM_IN_INFRARED
#endif //__PROTOCOL_REMOTE_NEC_H__
