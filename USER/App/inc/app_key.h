/**
  ******************************************************************************
  * @file    app_key.h
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

#ifndef  __APP_KEY_H__
#define  __APP_KEY_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"

#if(KEY)
#include "stm32f1xx_hal.h"

/* Exported_Functions --------------------------------------------------------*/
#ifndef KEY_EXIT
void App_Key(void);
#endif //KEY_EXIT

/* Exported constants --------------------------------------------------------*/

#endif //KEY
#endif //__APP_KEY_H__
