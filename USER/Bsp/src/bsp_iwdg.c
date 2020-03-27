/**
  ******************************************************************************
  * @file    bsp_iwdg.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention IWDG 时间计算：	
  *													IWDG时钟频率（40）/(分频系数*计数值) = 时间
  *													例：40000/(32*1250) = 1ms
  ******************************************************************************
*/
#include "bsp_iwdg.h"
#if(DOG_IWDG)

#include "global_variable.h"
#include "iwdg.h"

/**
  * @brief  定时喂狗
  * @param  void
  * @retval void
  */
void Feed_IWDGDog(void)
{
	if(sysTick - iwdg_LastFeedTime > IWDG_FEEDTIME)
	{
		HAL_IWDG_Refresh(&hiwdg);
		iwdg_LastFeedTime = sysTick;
	}
}
#endif //DOG_IWDG

