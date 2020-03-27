/**
  ******************************************************************************
  * @file    moudle_base_init.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   moudle_base_init
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
*/
#include "module_basedevice.h"
#include "device_config.h"
#include "global_variable.h"
#if(SERIALPORT)
#include "usart.h"
#include "bsp_uart.h"
#endif //SERIALPORT
#if( TIM || STANDBY_TIM_EXIT )
#include "tim.h"
#endif //TIM || STANDBY_TIM_EXIT
#if(RTC_CLOCK)
#include "rtc.h"
#include "bsp_rtc.h"
#endif //RTC_CLOCK
#if(DOG_WWDG)
#include "wwdg.h"
#endif //DOG_WWDG 
#if(STANDBY_MODE)
#include "bsp_standby.h"
#endif //STANDBY_MODE
#if(ADC_DMA)
#include "bsp_adc.h"
#include "adc.h"
#endif //ADC_DMA

/**
  * @brief  基本模块配置初始化
  * @param  void
  * @retval void
  */
void Moudle_Base_Init(void)
{
#if(SERIALPORT)
	MODULEUART_SERIALPORT.moduleType = MODULETYPE_SERIALPORT; 
	MODULEUART_SERIALPORT.huartx = &huart1;
	MODULEUART_SERIALPORT.RxByteTimeout = SERIALPORT_BYTETIMEOUT;
	MODULEUART_SERIALPORT.RxTotalTimeout = SERIALPORT_TOTALTIMEOUT;
	MODULEUART_SERIALPORT.errorBase = ERROR_DT0_SERIALPORT;
	/* 使能主通讯串口中断*/
	UART_NVIC_Init(MODULEUART_SERIALPORT.huartx, &SERIALPORT_RECVBUFF);	
#endif //SERIALPORT
#if(KEY)
	//nothing to do
#endif //KEY
#if(LED)
	//nothing to do
#endif //LED
#if(BEEP)
	//nothing to do
#endif //BEEP
#if(DOG_IWDG)
	//nothing to do
#endif //DOG_IWDG
#if(DOG_WWDG)
	__HAL_WWDG_ENABLE_IT(&hwwdg, WWDG_IT_EWI);
#endif //DOG_WWDG
#if(TIM)
//	HAL_TIM_Base_Start_IT(&htim3);
#endif //TIM
#if(PWM)
	#if(PWM_OUT)
	//输出比较
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	#endif //PWM_OUT
	#if(PWM_IN_GET)
	//输入捕获
	HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_1);	
	#endif //PWM_IN_GET
	#if(PWM_IN_INFRARED)
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);	//输入捕获中断
	HAL_TIM_Base_Start_IT(&htim4);
	#endif //PWM_IN_INFRARED
#endif //PWM
#if(RTC_CLOCK)
	Keep_Time_Invariant();	
	#if(STOP_WATCH_SECIT)
	//上面基本配置时已经配置好了
	#endif //STOP_WATCH_SECIT
	#if(STOP_WATCH_ALRAIT)
	RTC_AlarmConfig(&hrtc, 22, 11, 31);//配置为下一秒中的闹钟
	#endif //STOP_WATCH_ALRAIT
#endif //RTC_CLOCK
#if(STANDBY_MODE)
	//相关配置代码在bsp_systick中
#endif //STANDBY_MODE
#if(ADC_DMA)
	Get_ADC_Value_DMA(&hadc1, Adc_Dma_Buff , COLLECT_CHANNEL_NUMBER, sizeof(Adc_Dma_Buff));
#endif //ADC_DMA
}

