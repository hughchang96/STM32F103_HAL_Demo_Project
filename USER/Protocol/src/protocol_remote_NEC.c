/**
  ******************************************************************************
  * @file    protocol_remote_NEC.c
  * @author  �Ż�
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention	NECЭ�飺
	*	���ݸ�ʽ�� ͬ����ͷ + ��ַ�� +��ַ���� + ������ + �������� ��LSB���У�
	*	ͬ����ͷ��9ms�͵�ƽ + 4.5ms�ߵ�ƽ
	*	������ ��   9ms�͵�ƽ + 2.5ms�ߵ�ƽ
	*	�߼�1��      560us  +  1680us
	* �߼�0��      560us  +  560us
  ******************************************************************************
*/
#include "protocol_remote_NEC.h"
#if(PWM_IN_INFRARED)

#include "tim.h"
#include "global_variable.h"

/**
  * @brief  NECЭ��ĺ���ң����Э����� \
						��tim4������ж���ʵ�ֵ���
  * @param  htim
  * @retval void
  */
void Remote_Nec_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(Tim4_InfraredDev.Flag_recv_Sync == 1)	//�ж�֮ǰ�ǲ��ǽ��յ���ͬ����
	{			
		Tim4_InfraredDev.Flag_recv_Rising = 0; //����������ѱ������־λ
		if(Tim4_InfraredDev.Repeat_Number == 0)
		{
			Tim4_InfraredDev.Flag_recv_Key = 1;
		}
		if(Tim4_InfraredDev.Repeat_Number > 13) //�Ѿ�������130ms�ĸߵ�ƽ�ˡ��϶������һ�������Ľ��ա�����־λ�Ȳ�����ʼ����׼���´ν���
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
  * @brief  NECЭ��ĺ���ң����Э����� \
						��tim4�Ĳ����ж���ʵ�ֵ���   __HAL_TIM_SET_CAPTUREPOLARITY��TIM_RESET_CAPTUREPOLARITY���󣬵�һ������һ������
  * @param  htim
  * @retval void
  */
void Remote_Nec_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(INFRARED_RECV_STATE)//�����ز���:�����ж����������������������½��ز��� 	ͨ����⵱ǰIO�ĵ�ƽ״̬������ж�Ϊʲô��
	{
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC2);
		/* �л������� */
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
		/* ��ն�ʱ��ֵ */
		__HAL_TIM_SET_COUNTER(htim,0);
		/* ����������Ѿ������� */
		Tim4_InfraredDev.Flag_recv_Rising = 1;			
	}
	else //�½��ز���
	{
		/* �л������� */
		__HAL_TIM_SET_CAPTUREPOLARITY(htim,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);
		/* ��øߵ�ƽ����ʱ�� */
		Tim4_InfraredDev.Keep_Time =__HAL_TIM_GET_COUNTER(htim);
		if(Tim4_InfraredDev.Flag_recv_Rising == 1) //�ж�֮ǰ�ǲ��ǲ��񵽹������أ�������ʵ��û��Ҫ�ģ�����ֻ���ų���һ���ж�ֱ�Ӿ����½��ش��������
		{	
			if(Tim4_InfraredDev.Flag_recv_Sync == 1)	//�ж�֮ǰ�ǲ��ǽ��յ���ͬ����
			{	
				if(Tim4_InfraredDev.Keep_Time > 300 && Tim4_InfraredDev.Keep_Time < 800)			//560Ϊ��׼ֵ,560us���߼�0
				{
					Tim4_InfraredDev.Key_Value <<= 1; //����һλ.	��Ϊ�ǵ��ֽ��ȴ���
					Tim4_InfraredDev.Key_Value |= 0;	//���յ�0
				}
				else if(Tim4_InfraredDev.Keep_Time > 1400 && Tim4_InfraredDev.Keep_Time < 1800)	//1680Ϊ��׼ֵ,1680us���߼�1
				{
					Tim4_InfraredDev.Key_Value <<= 1; //����һλ.	��Ϊ�ǵ��ֽ��ȴ���
					Tim4_InfraredDev.Key_Value |= 1;	//���յ�0	 
				}
				else if(Tim4_InfraredDev.Keep_Time > 2200 && Tim4_InfraredDev.Keep_Time < 2600)	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms��������
				{
					Tim4_InfraredDev.Repeat_Number ++; 		//������������1��
					Tim4_InfraredDev.Keep_Time = 0;	//��ռ�ʱ��		
				}
			}
			else if(Tim4_InfraredDev.Keep_Time > 4200 && Tim4_InfraredDev.Keep_Time < 4700)	//û�н��յ�ͬ���룬���жϸոս��յ���������ʱ���Ƿ����ͬ����
			{
				Tim4_InfraredDev.Flag_recv_Sync = 1;		//��ǳɹ����յ���������
				Tim4_InfraredDev.Repeat_Number = 0;			//�����������������
			}						 
		}
	//ֻҪ�Ǵ������½��أ������յ������ر������
		Tim4_InfraredDev.Flag_recv_Rising = 0;
	}
}

#endif //PWM_IN_INFRARED

