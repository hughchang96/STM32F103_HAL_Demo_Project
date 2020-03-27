/**
  ******************************************************************************
  * @file    app_key.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
*/
#include "app_key.h"
#if(KEY)

#include "bsp_key.h"

#ifndef KEY_EXIT
/**
  * @brief  按键服务函数
  * @param  void
  * @retval void
  */
void App_Key(void)
{
	switch(Key_Scan(1))
	{
#if(LED)
		case KEYRI:
			HAL_GPIO_TogglePin(GPIOx_LED0.GPIOx, GPIOx_LED0.GPIO_Pin);
		break;
		case KEYDO:					
			HAL_GPIO_TogglePin(GPIOx_LED1.GPIOx, GPIOx_LED1.GPIO_Pin);
		break;
		case KEYLE:
			HAL_GPIO_TogglePin(GPIOx_LED0.GPIOx, GPIOx_LED0.GPIO_Pin);
			HAL_GPIO_TogglePin(GPIOx_LED1.GPIOx, GPIOx_LED1.GPIO_Pin);
		break;
#endif //LED
		case KEYUP:
			HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin);
		break;
		default:
				HAL_Delay(10);
		break;
	}
}
#endif //KEY_EXIT
#endif //KEY
