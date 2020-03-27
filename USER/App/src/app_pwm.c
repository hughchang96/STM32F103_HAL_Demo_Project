/**
  ******************************************************************************
  * @file    app_pwm.h
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
#include "app_pwm.h"
#if(PWM)

#include "bsp_pwm.h"
#include "tool.h"
#include "tim.h"
#include "global_variable.h"

/**
  * @brief  呼吸灯 TIM3 PWM PB5 PWM Generation CH2
  * @param  void
  * @retval void
  */
void App_Led_Pwm(void)
{	
	uint16_t pwm_value = 0, dir;
	while(1)
	{
		HAL_Delay(5);	 
		if(dir)
			pwm_value++;
		else 
			pwm_value--;
		if(pwm_value>500)
			dir=0;
		if(pwm_value==0)
			dir=1;	
		Pwm_SetValue(&htim3 ,TIM_CHANNEL_2, pwm_value);
	}
}

#if(PWM_IN_INFRARED)
/**
  * @brief  红外遥控器
  * @param  void
  * @retval void
  */
void App_Infrared_Remote(void)
{
	uint8_t sta=0;       
	uint8_t t1,t2;
	
	if(Tim4_InfraredDev.Flag_recv_Key == 1 )//得到一个按键的所有信息了
	{ 
		t1 = Tim4_InfraredDev.Key_Value >> 24;			//得到地址码
		t2 = (Tim4_InfraredDev.Key_Value >> 16 ) & 0xff;	//得到地址反码 
		if((t1 == (uint8_t)~t2) && t1 == 0)//检验遥控识别码(ID)及地址 ，判断地址是否正确再获取数据
		{ 
			t1 = Tim4_InfraredDev.Key_Value >> 8;
			t2 = Tim4_InfraredDev.Key_Value; 	
			if(t1 == (uint8_t)~t2)
				sta = t1;//键值正确	 
		}   
		if((sta == 0) || (Tim4_InfraredDev.Flag_recv_Sync == 0))//按键数据错误/遥控已经没有按下了（在得到一个按键的信息后如果因为时间太久就认为引导码无效，
										//那么就得清除有效按键标识了，否则遥控器停止按下的时候还会去处理上一次发的按键不就乱套了嘛）
		{
		 	Tim4_InfraredDev.Flag_recv_Key = 0;//清除接收到有效按键标识
			Tim4_InfraredDev.Repeat_Number = 0;		//清除按键次数计数器
		}
    USER_PRINTF("0x%02x", sta);
	}  
}
#endif //PWM_IN_INFRARED

#endif //PWM
