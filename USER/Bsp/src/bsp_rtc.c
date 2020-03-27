/**
  ******************************************************************************
  * @file    bsp_rtc.C
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention 注意：	闹钟cubemx配置时必须打开OUTPUT
  *		cubemx自动生成的代码每次复位会将时间重新初始化，通过修改MX_RTC_Init解决问题，为避免								
  *出现意外rtc功能模块需一直开启
  ******************************************************************************
*/
#include "bsp_rtc.h"
#if(RTC_CLOCK)

#include "stdio.h"
#include "tool.h"
#include "global_variable.h"

/**
  * @brief  向后背区域寄存器写数据
  * @param  DATE：要写的数据
  * @retval void
  */
void MY_HAL_RTCEx_BKUPWrite(RTC_DateTypeDef *DATE)
{
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5050);//向指定的后备区域寄存器写入数据
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, (uint16_t)DATE->Year);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, (uint16_t)DATE->Month);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, (uint16_t)DATE->Date);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, (uint16_t)DATE->WeekDay);
}

/**
  * @brief  从后备区域寄存器读之前写入的数据
  * @param  DATE：将读出的数据写入它
  * @retval void
  */
void MY_HAL_RTCEx_BKUPRead(RTC_DateTypeDef *DATE)
{
	DATE->Year    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
	DATE->Month   = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
	DATE->Date    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
	DATE->WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
}

/**
  * @brief  获取实时时间保存进后备区域寄存器
  * @param  void
  * @retval void
  */
void Get_Real_Time(void)
{
	
	HAL_RTC_GetDate(&hrtc, &DATE, RTC_FORMAT_BIN);
	MY_HAL_RTCEx_BKUPWrite(&DATE);
}

/**
  * @brief  与MX_RTC_Init中增加的代码配合实现复位时间不清零
  * @param  void
  * @retval void
  */
void Keep_Time_Invariant(void)
{
	RTC_DateTypeDef DateToUpdate = {0};
	
	HAL_RTCEx_SetSecond_IT(&hrtc);	
	if(RTCEx_BKUPRead_Value != RTCEx_BKUP_Value)
	{
		DateToUpdate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
		DateToUpdate.Month = RTC_MONTH_MARCH;
		DateToUpdate.Date = 0x18;
		DateToUpdate.Year = 32;
		
		MY_HAL_RTCEx_BKUPWrite(&DateToUpdate);
	}
	if(RTCEx_BKUPRead_Value == RTCEx_BKUP_Value)
	{	
		MY_HAL_RTCEx_BKUPRead(&DATE);
		if (HAL_RTC_SetDate(&hrtc, &DATE, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
		Get_Real_Time();
	}
}

/**
  * @brief  使用RTC Second interrupt 的秒中断把实时时间写入后备区域
  * @param  hrtc：发生中断的RTC信息结构体
  * @retval void
  */
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
	if(hrtc->Instance == RTC)
	{
		Get_Real_Time();
#if(STOP_WATCH_SECIT)
		printf("%02d/%02d/%02d/Week%d\r\n",2000 + DATE.Year, DATE.Month, DATE.Date, DATE.WeekDay);
		HAL_RTC_GetTime(hrtc, &TIME, RTC_FORMAT_BIN);
		printf("%02d:%02d:%02d\r\n",TIME.Hours, TIME.Minutes, TIME.Seconds);
		printf("\r\n");
#endif //STOP_WATCH_SECIT
	}
}

/**
  * @brief  设置闹钟中断时间
  * @param  hrtc：RTC信息结构体
	* @param  Hours：小时
	* @param  Minutes：分钟
	* @param  Seconds：秒
  * @retval None
  */
void RTC_AlarmConfig(RTC_HandleTypeDef *hrtc, uint8_t Hours, uint8_t Minutes, uint8_t Seconds)
{
	RTC_AlarmTypeDef sAlarm;
	
	sAlarm.Alarm = RTC_ALARM_A;
	sAlarm.AlarmTime.Hours = Hours;
	sAlarm.AlarmTime.Minutes = Minutes;
	sAlarm.AlarmTime.Seconds = Seconds;

	HAL_RTC_SetAlarm_IT(hrtc,&sAlarm,RTC_FORMAT_BIN);	
}

#if(STOP_WATCH_ALRAIT)
/**
  * @brief RTC Alarm interrupt 回调
  * @param  hrtc：发生中断的RTC信息结构体
  * @retval void
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	/* Get the RTC current Time ,must get time first*/
	HAL_RTC_GetTime(hrtc, &TIME, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(hrtc, &DATE, RTC_FORMAT_BIN);
	RTC_AlarmConfig(hrtc, TIME.Hours, TIME.Minutes, TIME.Seconds + 1);

	/* Display date Format : yy/mm/dd */
	printf("%02d/%02d/%02d\r\n",2000 + DATE.Year, DATE.Month, DATE.Date);
	/* Display time Format : hh:mm:ss */
	printf("%02d:%02d:%02d\r\n",TIME.Hours, TIME.Minutes, TIME.Seconds);
	printf("\r\n");
}

#endif //STOP_WATCH_ALRAIT

#endif //RTC_CLOCK
