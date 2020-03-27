/**
  ******************************************************************************
  * @file    key.C
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

#include "bsp_key.h"
#if(KEY)

#include "tool.h"
#include "global_variable.h"

#if(KEY_EXIT)
/**
  * @brief  �ⲿ�жϻص�����
  * @param  GPIO_Pin�������жϵ�����
  * @retval 
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
//		HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin);
	}
	if(GPIO_Pin == GPIO_PIN_4)
	{
//		HAL_GPIO_TogglePin(GPIOx_LED0.GPIOx, GPIOx_LED0.GPIO_Pin);
	}
}
#endif //KEY_EXIT
#if(KEY_SCAN)
/**
  * @brief  ����ɨ�躯��
  * @param  mode���Ƿ�֧������ 0����֧�� 1��֧��
  * @retval ���µİ���
  */
uint16_t Key_Scan(uint16_t mode)
{
	static uint16_t key_up = 1; //�������ɿ���־
	if(mode)
	{
		key_up = 1; //֧������ 
	}
	if(key_up && (KEYRI_STATE == GPIOx_KEYRI.EffectLevel || KEYDO_STATE == GPIOx_KEYDO.EffectLevel || KEYLE_STATE == GPIOx_KEYLE.EffectLevel || KEYUP_STATE == GPIOx_KEYUP.EffectLevel))
	{
		HAL_Delay(100); //ȥ����
		key_up = 0;
		if(KEYRI_STATE == GPIOx_KEYRI.EffectLevel)
		{
			USER_PRINTF("key right press");
			return KEYRI;
		}			
		else if(KEYDO_STATE == GPIOx_KEYDO.EffectLevel)
		{
			USER_PRINTF("key down press");
			return KEYDO;
		}
		else if(KEYLE_STATE == GPIOx_KEYLE.EffectLevel)
		{
			USER_PRINTF("key left press");
			return KEYLE;
		}
		else if(KEYUP_STATE == GPIOx_KEYUP.EffectLevel)
		{
			USER_PRINTF("key up press KEYUP_STATE %d ", KEYUP_STATE);
			return KEYUP;
		}
	}
	else if(KEYRI_STATE && !GPIOx_KEYRI.EffectLevel && KEYDO_STATE == !GPIOx_KEYDO.EffectLevel && KEYLE_STATE == !GPIOx_KEYLE.EffectLevel && KEYUP_STATE == !GPIOx_KEYUP.EffectLevel)
		key_up=1; 
	return KEYNO; // �ް�������
}

#endif //KEY_SCAN

#endif //KEY
