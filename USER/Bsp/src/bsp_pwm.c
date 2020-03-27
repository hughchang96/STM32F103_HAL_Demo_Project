/**
  ******************************************************************************
  * @file    bsp_pwm.c
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

#include "bsp_pwm.h"
#if(PWM)

#include "tool.h"
#include "tim.h"
#include "protocol_remote_NEC.h"

/**
  * @brief  设置pwm的占空比
  * @param  value：脉宽
  * @retval void
  */
void Pwm_SetValue(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t value)
{
	TIM_OC_InitTypeDef sConfigOC;

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = value;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, Channel);
	HAL_TIM_PWM_Start(htim, Channel);  
}


#endif //PWM
