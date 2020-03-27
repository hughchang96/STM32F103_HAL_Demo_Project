/**
  ******************************************************************************
  * @file    bsp_adc.c
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
#include "bsp_adc.h"
#if(STM_ADC)

#include "stdlib.h"

/**
  * @brief  ADC��ѯ�ɼ�����˵��ô˺���ʵ�ֶ�ͨ���ɼ����ɼ�˳��ͨ��˳��
  * @param  Ҫ��ȡ��ADC
  * @retval �ɼ�����ֵ
  */
uint32_t Get_ADC_Value_Pool(ADC_HandleTypeDef *hadcx)
{
	HAL_ADC_Start(hadcx);

	 /*  Before starting a new conversion, you need to check the current state of 
							the peripheral; if it��s busy you need to wait for the end of current
							conversion before starting a new one.
							For simplicity reasons, this example is just waiting till the end of the 
							conversion, but application may perform other tasks while conversion 
							operation is ongoing. */
	/* �ȴ�ת����� ��ʱʱ�䣺50 */
	HAL_ADC_PollForConversion(hadcx, 50);

	/* ��鳣��ͨ��������ת���Ƿ���� */  
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(hadcx), HAL_ADC_STATE_REG_EOC)) 
	{
		/* ��ȡ����ͨ����ת��ֵ */
		 return HAL_ADC_GetValue(hadcx);
  }
	return 0;
}

/**
  * @brief  ADC֮DMA�ɼ�
  * @param  hadc: ADC handle
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @retval 
  */
void Get_ADC_Value_DMA(ADC_HandleTypeDef* hadcx,uint32_t *Value_buff , uint16_t Channel_Number, uint32_t Length)
{
	uint16_t x, y;
	uint32_t	*ADC_Value;
	
	ADC_Value = (uint32_t *)malloc(sizeof(uint32_t)*Length);
	HAL_ADC_Start_DMA(hadcx, ADC_Value, Length);
	//����ȡ��ֵ��ͨ��˳��ֵ
	for(x = 0; x < Length; x += Channel_Number)
	{
		for(y = 0; y < Channel_Number; y++)
		{
			Value_buff[y] += ADC_Value[x++];
		}
		x -= Channel_Number;
	}
	//ȡƽ��ֵ
	for(y = 0; y < Channel_Number; y++)
	{
		Value_buff[y] = Value_buff[y]/(Length/Channel_Number);
	}
	free(ADC_Value);
}


#endif //STM_ADC
