/**
  ******************************************************************************
  * @file    bsp_wwdg.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention:	WWDG 时间计算：	
	*		APB1时钟频率（36MHZ）/(4096*分频系数（8））= x MHZ（910us）		（1/1HZ = 1s）							
  *		x(910) * (127-上窗口值(95))  <	 刷新窗口(58.2-28.2) < x(910) * 64 = 58.2ms
  *				上窗口时间(28.2)						  必须喂狗时间(30ms)			下窗口时间(58.2)
  ******************************************************************************
*/
#include "bsp_wwdg.h"
#if(DOG_WWDG)

#include "wwdg.h"
#include "tool.h"
/**
  * @brief  开启中断后自动在递减到64之前喂狗
  * @param  hwwdg：窗口看门狗配置信息结构体
  * @retval void
  */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
		HAL_WWDG_Refresh(hwwdg);
}
#endif //DOG_WWDG

