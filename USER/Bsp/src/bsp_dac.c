/**
  ******************************************************************************
  * @file    bsp_dac.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention	DAC输出电压计算 V = Data*4096/3.3
  *
  *
  ******************************************************************************
*/
#include "bsp_dac.h"
#if(STM_DAC)

/**
  * @brief  设置DAC的输出参数并开始输出
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @param  Alignment Specifies the data alignment.
  *          This parameter can be one of the following values:
  *            @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *            @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *            @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  Data Data to be loaded in the selected data holding register.
  * @retval void
  */
void DAC_Output(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data)
{
	 /* Set DAC channel DHR12RD register */
	HAL_DAC_SetValue(hdac, Channel, Alignment, Data);
   
  /* 2- Enable DAC Channel */
	HAL_DAC_Start(hdac, Channel);
}

/**
	* @brief  利用定时器使DAC输出波形（三角波）
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
	* @retval void
	*/
void DAC_Output_Wave(TIM_HandleTypeDef *htimx, DAC_HandleTypeDef *hdac, uint32_t Channel)
{
	/* Start the TIM Base generation in interrupt mode */
	HAL_TIM_Base_Start(htimx);

	/* Enable DAC Channel1 */
	HAL_DAC_Start(hdac, Channel);
}
  

#endif //STM_DAC
