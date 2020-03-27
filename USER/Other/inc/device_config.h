/**
  ******************************************************************************
  * @file    device_config.h
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

#ifndef  __DEVICE_CONFIG_H__
#define  __DEVICE_CONFIG_H__

// <<< Use Configuration Wizard in Context Menu >>>

/* DEBUG_MODE -------------------------------------------------------------------*/
//<h>DEBUG_MODE
//<e>DEBUG_MODE
//</e>
//<i>�Ƿ�������ģʽ
#define DEBUG_MODE 1
//</h>
//<i>ѡ���Ƿ�������ģʽ

/* ģ������ -----------------------------------------------------------------------*/

//<h>MODULE_CHOICE

/* -------------������---------------- */
//<e>SERIALPORT
#define SERIALPORT 1
#if(SERIALPORT)
	//<o>������
	//<9600=> 9600  
	//<115200=> 115200
	//<1152000=> 1152000 
	#define BAUD_RATE 9600
	//<o>�ֽڳ�ʱʱ��(ms)
	#define SERIALPORT_BYTETIMEOUT	20
	//<o>�ܳ�ʱʱ��(ms)
	#define SERIALPORT_TOTALTIMEOUT	3000
#endif //SERIALPORT
//</e>
//<i>����λ��ͨ�Ŵ���:USART1,�ֽ��ж�+idle

/* -------------����---------------- */
//<e>KEY
#define KEY 1
#if(KEY)
	//<h>������ⷽʽ
	//<e>KEY_EXIT
	//</e>
	//<i>�ж�ģʽ
	#define KEY_EXIT 1
	
	//<e>KEY_SCAN
	//</e>
	//<i>��ƽɨ��
	#define KEY_SCAN 1
	//</h>
#endif //KEY
//</e>	
//<i>����ʵ�飨���ж� ɨ���ƽ��

/* -------------LED---------------- */
//<e>LED
#define LED 0
//</e>
//<i> LED

/* -------------������---------------- */
//<e>BEEP
#define BEEP 0
//</e>
//<i>������


/* -------------�������Ź�---------------- */
//<e>DOG_IWDG
#define DOG_IWDG 0
#if(DOG_IWDG)
//<o>���Ź����ιʳ���(ms)
#define IWDG_FEEDTIME	4000
#endif //DOG_IWDG
//</e>
//<i>����������ιʳ�����ιʳ��λ����

/* -------------���ڿ��Ź�---------------- */
//<e>DOG_WWDG
#define DOG_WWDG 0
//</e>
//<i>������ڹ涨��������ι����λ�����������жϺ��Զ��ڵݼ���64֮ǰι�����⸴λ

/* -------------��ʱ��---------------- */
//<e>TIM
#define TIM 1 //��ʱ��
//</e>
//<i>ʹ�ö�ʱ��ʵ��LED�Ƶķ�ת

/* -------------PWM---------------- */
//<e>PWM
#define PWM 1 //��ʱ��
#if(PWM)
//<e>PWM_OUT
#define PWM_OUT 0
//</e>
//<i>����Ƚϣ������� 
//<e>PWM_IN
#define PWM_IN 1
//<e>PWM_IN_INFRARED
#define PWM_IN_INFRARED 0
//</e>
//<i>����ң��������
//<e>PWM_IN_GET
#define PWM_IN_GET 0
//</e>
//<i>���벶�񣺻�ȡ����Ƶ�ʡ����ڵ�
//</e>
#endif //PWM
//</e>
//<i>PWM����Ƚϣ������� ���벶�񣺻�ȡ����Ƶ�ʡ����ڵ�

/* -------------ʵʱʱ��---------------- */
//<e>RTC_CLOCK
#define RTC_CLOCK 1
#if(RTC_CLOCK)
//<o>������Ĵ���д��ֵ
#define RTCEx_BKUP_Value 0x5051
//<i>�����ж��Ƿ���Ҫ���³�ʼ��ʱ��
	//<h>���ʵ�ַ�ʽ
	//<e>STOP_WATCH_SECIT
	//</e>
	//<i>RTC���������Ѿ������˴˹��ܵ�ʵ�֣�����ֻ�ǿ����Ƿ�ʱ���ӡ����
	#define STOP_WATCH_SECIT 0
	
	//<e>STOP_WATCH_ALRAIT
	//</e>
	//<i>�����ж�ʵ�����
	#define STOP_WATCH_ALRAIT 0
	//</h>
#endif //RTC_CLOCK
//</e>
//<i>��������ô�ģ�飬����ϵͳʱ�����ʹ��systickʵ�����жϣ����

/* -------------��������---------------- */
//<e>STANDBY_MODE
#define STANDBY_MODE 1 //����ģʽ
//</e>
//<i>��������,��Ҫ��KEYģ��

/* -------------ADCģ��ת��---------------- */
//<e>ADC
#define STM_ADC 1 
//<e>ADC_DMA
#define ADC_DMA 1 
//<o>�ɼ�����
#define COLLECT_NUMBER 10
//<o>�ɼ���ͨ����
#define COLLECT_CHANNEL_NUMBER 1
//</e>
//</e>
//<i>DMA��ͨ���ɼ��ɼ�

/* -------------ADC��ģת��---------------- */
//<e>DAC
#define STM_DAC 1 
//</e>
//<i>DACģ�������ѹ ���ǲ�

/* -------------I2C---------------- */
//<e>I2C
#define I2C 1 
//</e>
//<i>�� EEPROM ͨ��I2C�������ݶ�д,��ģ��û��I2C������ֱ�ӵ��ö�д��������

//</h>
//<i>ģ������

// <s.20> Change ID
#define BOOTLOGO  "New Day -> New Life"

// <<< end of configuration section >>>

typedef enum
{
	MODULETYPE_ALL = 0x00, //����ģ��
	MODULETYPE_SERIALPORT = 0x01,	//����
	MODULETYPE_KEY = 0X02, //����
	MODULETYPE_LED = 0X03, //ָʾ��
	MODULETYPE_BEEP = 0X04, //������
}MODULETYPE;


#endif //__DEVICE_CONFIG_H__
