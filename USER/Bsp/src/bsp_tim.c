/**
  ******************************************************************************
  * @file    bsp_tim.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention 定时器时间配置：
  *		例：配置1s完成一次计时：
  *		Tout(1s) = （（arr（10000-1）+1）*（psc（7200-1）+1））/Tclk （72）
  ******************************************************************************
*/
#include "bsp_tim.h"
#if(TIM)

#include "tim.h"
#include "tool.h"
#include "protocol_remote_NEC.h"


/**
  * @brief  定时器溢出中断回调函数
  * @param  htim：产生中断的的定时器
  * @retval void
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
#if(PWM_IN_INFRARED)
	if (htim->Instance == htim4.Instance)
  {
		Remote_Nec_PeriodElapsedCallback(htim);
	}
#endif //PWM_IN_INFRARED
}

/**
	* @brief  捕获中断回调
  * @param  htim：产生中断的的定时器
  * @retval void
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
#if(PWM_IN_GET)
	if(htim == &htim5 && htim->Channel == TIM_CHANNEL_1)
	{
		if(PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Edge == 0)
		{
			PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//获取上升沿时间点
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);//切换捕获极性
			HAL_TIM_IC_Start_IT(htim, TIM_CHANNEL_1);
			PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Edge = 1;
			if(PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeLast == 0)
			{
				PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Period = 0;
			}
			else
			{
				if(PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow > PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeLast)
				{
					PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Period = PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow - PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeLast;
				}
				else
				{
					PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Period = PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow + 0xffff - PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeLast + 1;
				}
			}
			PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeLast = PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow;
		}
		else if(PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Edge == 1)
		{
			PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_FallingTime = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);	
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			HAL_TIM_IC_Start_IT(htim, TIM_CHANNEL_1);
			
			if(PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_FallingTime < PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow)
			{
				PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_HighTime = PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_FallingTime + 0xffff - PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow + 1;
			}
			else
			{
				PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_HighTime = PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_FallingTime - PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_RisingTimeNow;
			}
			if(PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Period != 0)
			{
				PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Percent = (uint8_t)(((float)PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_HighTime / PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Period) * 1000);
				USER_PRINTF("Channel1 = %d	", PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Percent);
			}
			PWM_INPIT_CAPTURE_TIM5_CHANNEL1.Channel_Edge = 0;
		}
	}
#endif //PWM_IN_GET
#if(PWM_IN_INFRARED)
	if(htim->Instance == htim4.Instance)
	{
		Remote_Nec_CaptureCallback(htim);
	}  	
#endif //PWM_IN_INFRARED

}

#endif
