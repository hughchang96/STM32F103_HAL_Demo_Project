/**
  ******************************************************************************
  * @file    protocol_remote_NEC.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention	NEC协议：
	*	数据格式： 同步码头 + 地址码 +地址反码 + 按键码 + 按键反码 （LSB先行）
	*	同步码头：9ms低电平 + 4.5ms高电平
	*	连发码 ：   9ms低电平 + 2.5ms高电平
	*	逻辑1：      560us  +  1680us
	* 逻辑0：      560us  +  560us
  ******************************************************************************
*/
#include "protocol_remote_NEC.h"
#if(PWM_IN_INFRARED)

#include "tim.h"
#include "global_variable.h"

/**
  * @brief  NEC协议的红外遥控器协议解析 \
						在tim4的溢出中断中实现调用
  * @param  htim
  * @retval void
  */
void Remote_Nec_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(Tim4_InfraredDev.Flag_recv_Sync == 1)	//判断之前是不是接收到了同步码
	{			
		Tim4_InfraredDev.Flag_recv_Rising = 0; //清除上升沿已被捕获标志位
		if(Tim4_InfraredDev.Repeat_Number == 0)
		{
			Tim4_InfraredDev.Flag_recv_Key = 1;
		}
		if(Tim4_InfraredDev.Repeat_Number > 13) //已经接收了130ms的高电平了。肯定是完成一次完整的接收。将标志位等参数初始化。准备下次接收
		{
			Tim4_InfraredDev.Flag_recv_Sync = 0;
			Tim4_InfraredDev.Repeat_Number = 0;
		}
		else
		{
			Tim4_InfraredDev.Repeat_Number ++;
		}
	}
}


/**
  * @brief  NEC协议的红外遥控器协议解析 \
						在tim4的捕获中断中实现调用   __HAL_TIM_SET_CAPTUREPOLARITY中TIM_RESET_CAPTUREPOLARITY错误，第一行最后多一个括号
  * @param  htim
  * @retval void
  */
void Remote_Nec_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(INFRARED_RECV_STATE)//上升沿捕获:捕获中断自身不能区分是上升还是下降沿捕获 	通过检测当前IO的电平状态来间接判断为什么沿
	{
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC2);
		/* 切换捕获极性 */
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
		/* 清空定时器值 */
		__HAL_TIM_SET_COUNTER(htim,0);
		/* 标记上升沿已经被捕获 */
		Tim4_InfraredDev.Flag_recv_Rising = 1;			
	}
	else //下降沿捕获
	{
		/* 切换捕获极性 */
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);
		/* 获得高电平持续时间 */
		Tim4_InfraredDev.Keep_Time =__HAL_TIM_GET_COUNTER(htim);
		if(Tim4_InfraredDev.Flag_recv_Rising == 1) //判断之前是不是捕获到过上升沿，这里其实是没必要的，这里只是排除第一次中断直接就是下降沿触发的情况
		{	
			if(Tim4_InfraredDev.Flag_recv_Sync == 1)	//判断之前是不是接收到了同步码
			{	
				if(Tim4_InfraredDev.Keep_Time > 300 && Tim4_InfraredDev.Keep_Time < 800)			//560为标准值,560us，逻辑0
				{
					Tim4_InfraredDev.Key_Value <<= 1; //左移一位.	因为是低字节先传的
					Tim4_InfraredDev.Key_Value |= 0;	//接收到0
				}
				else if(Tim4_InfraredDev.Keep_Time > 1400 && Tim4_InfraredDev.Keep_Time < 1800)	//1680为标准值,1680us，逻辑1
				{
					Tim4_InfraredDev.Key_Value <<= 1; //左移一位.	因为是低字节先传的
					Tim4_InfraredDev.Key_Value |= 1;	//接收到0	 
				}
				else if(Tim4_InfraredDev.Keep_Time > 2200 && Tim4_InfraredDev.Keep_Time < 2600)	//得到按键键值增加的信息 2500为标准值2.5ms，连发码
				{
					Tim4_InfraredDev.Repeat_Number ++; 		//按键次数增加1次
					Tim4_InfraredDev.Keep_Time = 0;	//清空计时器		
				}
			}
			else if(Tim4_InfraredDev.Keep_Time > 4200 && Tim4_InfraredDev.Keep_Time < 4700)	//没有接收到同步码，则判断刚刚接收到的上升沿时间是否符合同步码
			{
				Tim4_InfraredDev.Flag_recv_Sync = 1;		//标记成功接收到了引导码
				Tim4_InfraredDev.Repeat_Number = 0;			//清除按键次数计数器
			}						 
		}
	//只要是触发了下降沿，将接收到上升沿标记清零
		Tim4_InfraredDev.Flag_recv_Rising = 0;
	}
}

#endif //PWM_IN_INFRARED

