/**
  ******************************************************************************
  * @file    bsp_standby.c
  * @author  �Ż�
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention:����ģʽ��Ŀ����Ҫ�ǽ�ʡ���ģ��ڴ�ģʽ�����ֻ��Ҫ2.2uA��������͹���ģʽ
	*�����ڼ�MCU���й���ȫ���رա�������WKUP���������ء�RTC���ӡ�RTC���ѡ�RTC�����¼���
	*RTCʱ�����NRST�����ⲿ��λ��IWDG��λ�����ѡ��Ӵ���ģʽ���Ѻ�Ĵ���ִ�е�ͬ�ڸ�λ���
	*ִ�С�
  ******************************************************************************
*/
#include "bsp_standby.h"
#if(STANDBY_MODE)

#include "global_variable.h"
#include "tool.h"

/**
  * @brief  �������ģʽ
  * @param  void
  * @retval void
  */
void StandbyMode_Measure(void)
{  
	__HAL_RCC_PWR_CLK_ENABLE();
	/* ���������ʹ�� */
	HAL_PWR_EnableBkUpAccess();

	/* �������л���Դ: ��������PA0 */
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
		/* ������л��ѱ�־λ */
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	/* ʹ�ܻ������ţ�PA0��Ϊϵͳ�������� */
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);

	/* �������ģʽ */
	HAL_PWR_EnterSTANDBYMode(); 
}

/**
  * @brief  �ڽ������ģʽ֮ǰ�ر�һЩ����
  * @param  void
  * @retval void
  */
void Sys_Enter_Standby(void)
{
	//�ر���������(����ʵ�����д)
	HAL_DeInit();
  __HAL_RCC_GPIOE_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
	          
	StandbyMode_Measure();//�������ģʽ
}

#endif //STANDBY_MODE
