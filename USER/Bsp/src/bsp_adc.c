/**
  ******************************************************************************
  * @file    bsp_adc.c
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
#include "bsp_adc.h"
#if(STM_ADC)

#include "stdlib.h"

/**
  * @brief  ADC轮询采集，多此调用此函数实现多通道采集，采集顺序即通道顺序
  * @param  要获取的ADC
  * @retval 采集到的值
  */
uint32_t Get_ADC_Value_Pool(ADC_HandleTypeDef *hadcx)
{
	HAL_ADC_Start(hadcx);

	 /*  Before starting a new conversion, you need to check the current state of 
							the peripheral; if it’s busy you need to wait for the end of current
							conversion before starting a new one.
							For simplicity reasons, this example is just waiting till the end of the 
							conversion, but application may perform other tasks while conversion 
							operation is ongoing. */
	/* 等待转换完成 超时时间：50 */
	HAL_ADC_PollForConversion(hadcx, 50);

	/* 检查常规通道的连续转换是否完成 */  
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(hadcx), HAL_ADC_STATE_REG_EOC)) 
	{
		/* 获取常规通道的转换值 */
		 return HAL_ADC_GetValue(hadcx);
  }
	return 0;
}

/**
  * @brief  ADC之DMA采集
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
	//将读取的值按通道顺序赋值
	for(x = 0; x < Length; x += Channel_Number)
	{
		for(y = 0; y < Channel_Number; y++)
		{
			Value_buff[y] += ADC_Value[x++];
		}
		x -= Channel_Number;
	}
	//取平均值
	for(y = 0; y < Channel_Number; y++)
	{
		Value_buff[y] = Value_buff[y]/(Length/Channel_Number);
	}
	free(ADC_Value);
}


#endif //STM_ADC
