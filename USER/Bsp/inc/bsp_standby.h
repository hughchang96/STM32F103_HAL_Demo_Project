/**
  ******************************************************************************
  * @file    bsp_standby.h
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

#ifndef  __BSP_STANDBY_H__
#define  __BSP_STANDBY_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"

#if(STANDBY_MODE)
#include "stm32f1xx_hal.h"

/* Exported_Functions --------------------------------------------------------*/
void Sys_Enter_Standby(void);

/* Exported constants --------------------------------------------------------*/

#endif //STANDBY_MODE
#endif //__BSP_STANDBY_H__
