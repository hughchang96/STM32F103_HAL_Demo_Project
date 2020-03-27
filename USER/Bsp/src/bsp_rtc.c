/**
  ******************************************************************************
  * @file    bsp_rtc.C
  * @author  �Ż�
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention ע�⣺	����cubemx����ʱ�����OUTPUT
  *		cubemx�Զ����ɵĴ���ÿ�θ�λ�Ὣʱ�����³�ʼ����ͨ���޸�MX_RTC_Init������⣬Ϊ����								
  *��������rtc����ģ����һֱ����
  ******************************************************************************
*/
#include "bsp_rtc.h"
#if(RTC_CLOCK)

#include "stdio.h"
#include "tool.h"
#include "global_variable.h"

/**
  * @brief  �������Ĵ���д����
  * @param  DATE��Ҫд������
  * @retval void
  */
void MY_HAL_RTCEx_BKUPWrite(RTC_DateTypeDef *DATE)
{
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5050);//��ָ���ĺ�����Ĵ���д������
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, (uint16_t)DATE->Year);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, (uint16_t)DATE->Month);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, (uint16_t)DATE->Date);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, (uint16_t)DATE->WeekDay);
}

/**
  * @brief  �Ӻ�����Ĵ�����֮ǰд�������
  * @param  DATE��������������д����
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
  * @brief  ��ȡʵʱʱ�䱣���������Ĵ���
  * @param  void
  * @retval void
  */
void Get_Real_Time(void)
{
	
	HAL_RTC_GetDate(&hrtc, &DATE, RTC_FORMAT_BIN);
	MY_HAL_RTCEx_BKUPWrite(&DATE);
}

/**
  * @brief  ��MX_RTC_Init�����ӵĴ������ʵ�ָ�λʱ�䲻����
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
  * @brief  ʹ��RTC Second interrupt �����жϰ�ʵʱʱ��д�������
  * @param  hrtc�������жϵ�RTC��Ϣ�ṹ��
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
  * @brief  ���������ж�ʱ��
  * @param  hrtc��RTC��Ϣ�ṹ��
	* @param  Hours��Сʱ
	* @param  Minutes������
	* @param  Seconds����
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
  * @brief RTC Alarm interrupt �ص�
  * @param  hrtc�������жϵ�RTC��Ϣ�ṹ��
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
