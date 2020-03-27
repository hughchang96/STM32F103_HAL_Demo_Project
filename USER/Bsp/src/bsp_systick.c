/**
  ******************************************************************************
  * @file    bsp_systick.c
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
#include "tool.h"
#include "bsp_systick.h"
#include "stm32f1xx_hal.h"
#include "global_variable.h"
#if(KEY)
#include "bsp_key.h"
#endif //KEY
#include "bsp_standby.h"

/**
  * @brief  利用滴答计时器的计时完成一些功能
  * @param  void
  * @retval void
  */
void HAL_SYSTICK_Callback(void)
{
#if(DOG_IWDG)
	sysTick ++;
	Feed_IWDGDog();
#endif //DOG_IWDG
#if(STANDBY_MODE)
	if(KEYRI_STATE == GPIOx_KEYRI.EffectLevel) //检测到按键按下
	{
		key_press_long++;
		if(key_press_long >= 3000) //1ms中断一次
		{			
			USER_PRINTF("Enter Standby Mode !!!");
			Sys_Enter_Standby();
			key_press_long = 0;	
		}
	}
	if(key_press_long != 0 && key_press_long < 3000)//避免出现多次短按次数到3000后出现复位
	{
		if(KEYRI_STATE != GPIOx_KEYRI.EffectLevel) //按键没有按下
		{
			key_press_short++;
			if(key_press_short >= 1000) //距离第一次检测到按下过去1s了，还是没有达到长按要求				
			{
				key_press_short = 0;
				key_press_long = 0;	
			}
		}	
	}
#endif //STANDBY_MODE	

}
