/**
  ******************************************************************************
  * @file    bsp_rtc.h
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

#ifndef  __BSP_RTC_H__
#define  __BSP_RTC_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"

#if(RTC_CLOCK)
#include "stm32f1xx_hal.h"
#include "rtc.h"

/* Exported_Functions --------------------------------------------------------*/
void RTC_AlarmConfig(RTC_HandleTypeDef *hrtc, uint8_t Hours, uint8_t Minutes, uint8_t Seconds);
void Keep_Time_Invariant(void);

/* Exported constants --------------------------------------------------------*/
extern RTC_TimeTypeDef TIME;
extern RTC_DateTypeDef DATE;
#endif //REAL_TIME_CLOCK
#endif //__BSP_RTC_H__
