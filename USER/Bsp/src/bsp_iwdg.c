/**
  ******************************************************************************
  * @file    bsp_iwdg.c
  * @author  �Ż�
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention IWDG ʱ����㣺	
  *													IWDGʱ��Ƶ�ʣ�40��/(��Ƶϵ��*����ֵ) = ʱ��
  *													����40000/(32*1250) = 1ms
  ******************************************************************************
*/
#include "bsp_iwdg.h"
#if(DOG_IWDG)

#include "global_variable.h"
#include "iwdg.h"

/**
  * @brief  ��ʱι��
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

