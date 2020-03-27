/**
  ******************************************************************************
  * @file    app_pwm.h
  * @author  �Ż�
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
  * @brief  ������ TIM3 PWM PB5 PWM Generation CH2
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
  * @brief  ����ң����
  * @param  void
  * @retval void
  */
void App_Infrared_Remote(void)
{
	uint8_t sta=0;       
	uint8_t t1,t2;
	
	if(Tim4_InfraredDev.Flag_recv_Key == 1 )//�õ�һ��������������Ϣ��
	{ 
		t1 = Tim4_InfraredDev.Key_Value >> 24;			//�õ���ַ��
		t2 = (Tim4_InfraredDev.Key_Value >> 16 ) & 0xff;	//�õ���ַ���� 
		if((t1 == (uint8_t)~t2) && t1 == 0)//����ң��ʶ����(ID)����ַ ���жϵ�ַ�Ƿ���ȷ�ٻ�ȡ����
		{ 
			t1 = Tim4_InfraredDev.Key_Value >> 8;
			t2 = Tim4_InfraredDev.Key_Value; 	
			if(t1 == (uint8_t)~t2)
				sta = t1;//��ֵ��ȷ	 
		}   
		if((sta == 0) || (Tim4_InfraredDev.Flag_recv_Sync == 0))//�������ݴ���/ң���Ѿ�û�а����ˣ��ڵõ�һ����������Ϣ�������Ϊʱ��̫�þ���Ϊ��������Ч��
										//��ô�͵������Ч������ʶ�ˣ�����ң����ֹͣ���µ�ʱ�򻹻�ȥ������һ�η��İ��������������
		{
		 	Tim4_InfraredDev.Flag_recv_Key = 0;//������յ���Ч������ʶ
			Tim4_InfraredDev.Repeat_Number = 0;		//�����������������
		}
    USER_PRINTF("0x%02x", sta);
	}  
}
#endif //PWM_IN_INFRARED

#endif //PWM
