/**
  ******************************************************************************
  * @file    bsp_systick.c
  * @author  �Ż�
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
  * @brief  ���õδ��ʱ���ļ�ʱ���һЩ����
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
	if(KEYRI_STATE == GPIOx_KEYRI.EffectLevel) //��⵽��������
	{
		key_press_long++;
		if(key_press_long >= 3000) //1ms�ж�һ��
		{			
			USER_PRINTF("Enter Standby Mode !!!");
			Sys_Enter_Standby();
			key_press_long = 0;	
		}
	}
	if(key_press_long != 0 && key_press_long < 3000)//������ֶ�ζ̰�������3000����ָ�λ
	{
		if(KEYRI_STATE != GPIOx_KEYRI.EffectLevel) //����û�а���
		{
			key_press_short++;
			if(key_press_short >= 1000) //�����һ�μ�⵽���¹�ȥ1s�ˣ�����û�дﵽ����Ҫ��				
			{
				key_press_short = 0;
				key_press_long = 0;	
			}
		}	
	}
#endif //STANDBY_MODE	

}
