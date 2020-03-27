/**
  ******************************************************************************
  * @file    app_pwm.h
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

#ifndef  __APP_PWM_H__
#define  __APP_PWM_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"

#if(PWM)
#include "stm32f1xx_hal.h"

/* Exported_Functions --------------------------------------------------------*/
void App_Led_Pwm(void);
void App_Infrared_Remote(void);

/* Exported constants --------------------------------------------------------*/

#endif //PWM
#endif //__APP_PWM_H__
