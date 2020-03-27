/**
  ******************************************************************************
  * @file    bsp_standby.c
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention:待机模式的目的主要是节省功耗，在此模式下最低只需要2.2uA电流（最低功耗模式
	*）。期间MCU所有功能全部关闭。可以由WKUP引脚上升沿、RTC闹钟、RTC唤醒、RTC入侵事件、
	*RTC时间戳、NRST引脚外部复位、IWDG复位，唤醒。从待机模式唤醒后的代码执行等同于复位后的
	*执行。
  ******************************************************************************
*/
#include "bsp_standby.h"
#if(STANDBY_MODE)

#include "global_variable.h"
#include "tool.h"

/**
  * @brief  进入待机模式
  * @param  void
  * @retval void
  */
void StandbyMode_Measure(void)
{  
	__HAL_RCC_PWR_CLK_ENABLE();
	/* 后背区域访问使能 */
	HAL_PWR_EnableBkUpAccess();

	/* 禁用所有唤醒源: 唤醒引脚PA0 */
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
		/* 清除所有唤醒标志位 */
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	/* 使能唤醒引脚：PA0做为系统唤醒输入 */
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

	/* 进入待机模式 */
	HAL_PWR_EnterSTANDBYMode(); 
}

/**
  * @brief  在进入待机模式之前关闭一些外设
  * @param  void
  * @retval void
  */
void Sys_Enter_Standby(void)
{
	//关闭所有外设(根据实际情况写)
	HAL_DeInit();
  __HAL_RCC_GPIOE_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
	          
	StandbyMode_Measure();//进入待机模式
}

#endif //STANDBY_MODE
