/**
  ******************************************************************************
  * @file    key.h
  * @author  ???бщ
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
*/

#ifndef  __BSP_KEY_H__
#define  __BSP_KEY_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"
#if(KEY)

#include "main.h"
#include "global_variable.h"

/* definition constant  --------------------------------------------------------*/

/* KEY STATE */
#define KEYRI_STATE 	HAL_GPIO_ReadPin(GPIOx_KEYRI.GPIOx, GPIOx_KEYRI.GPIO_Pin)
#define KEYDO_STATE		HAL_GPIO_ReadPin(GPIOx_KEYDO.GPIOx, GPIOx_KEYDO.GPIO_Pin)
#define KEYLE_STATE 	HAL_GPIO_ReadPin(GPIOx_KEYLE.GPIOx, GPIOx_KEYLE.GPIO_Pin)
#define KEYUP_STATE 	HAL_GPIO_ReadPin(GPIOx_KEYUP.GPIOx, GPIOx_KEYUP.GPIO_Pin)
/* KEY VALUE */
typedef enum
{
	KEYNO,
	KEYRI,
	KEYDO,
	KEYLE,
	KEYUP,
}KEY_VALUE;


/* Exported_Functions --------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
extern uint16_t Key_Scan(uint16_t mode);

#endif //KEY
#endif //__BSP_KEY_H__
