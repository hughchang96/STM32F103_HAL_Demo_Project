/**
  ******************************************************************************
  * @file    app_adc.c
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
#include "app_adc.h"
#if(STM_ADC)

#include "bsp_adc.h"
#include "tool.h"
#include "adc.h"
#include "stdlib.h"
#include "global_variable.h"


/**
  * @brief  利用ADC单通道轮询采集温度 光线强度
	*					ADC1:温度 ADC3:光敏
  * @param  void
  * @retval void
  */
void App_Temperature_Light_Poll(void)
{
	uint16_t AD_Value;
	float temperature_light;

	/* 获取常规通道的转换值 */
	AD_Value = Get_ADC_Value_Pool(&hadc1);
	temperature_light = ((1.43 - (AD_Value*3.3/4096))/4.3) + 25;
	USER_PRINTF("Temperature :%d  %f ",AD_Value, temperature_light);

	/* 获取常规通道的转换值 */
	AD_Value = Get_ADC_Value_Pool(&hadc3);
	temperature_light = 100 - (AD_Value/40);
	USER_PRINTF("Light :%d  %f ",AD_Value, temperature_light);
}

/**
  * @brief  ADC之DMA多通道采集温度
	*					ADC1:温度 ADC3:光敏
  * @param  void
  * @retval void
  */
void App_Temperature_Light_Dma(void)
{
	uint16_t x, y;
	uint32_t *buff;
	buff = (uint32_t *)malloc(sizeof(uint32_t)*COLLECT_CHANNEL_NUMBER);
	for(x = 0; x < COLLECT_NUMBER; x += COLLECT_CHANNEL_NUMBER)
	{
		for(y = 0; y < COLLECT_CHANNEL_NUMBER; y++)
		{
			buff[y] = Adc_Dma_Buff[x++];
		}
		x -= COLLECT_CHANNEL_NUMBER;
	}
	buff[0] = ((1.43 - (buff[0]*3.3/4096))/4.3) + 25;
	USER_PRINTF("Temperature :%d ", buff[0]);
	free(buff);
}

#endif //STM_ADC		

