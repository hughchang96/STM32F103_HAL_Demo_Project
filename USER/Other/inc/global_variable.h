/**
  ******************************************************************************
  * @file    global_variable.h
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
#ifndef  __GLOBAL_VARIABLE_H__
#define  __GLOBAL_VARIABLE_H__
/* INCLUDE -------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "device_config.h"
/* definition constant  --------------------------------------------------------*/
/* ��������С */
#define BUFF_SIZE 3072

/* GPIO��� */
#define LEVELINIT_ENABLE 0x01	//��Ҫ��ƽ��ʼ��
#define LEVELINIT_DISABLE 0x00	//����Ҫ��ƽ��ʼ��
#define EFFECTLEVEL_TOP 0x01	//�ߵ�ƽʹ��
#define EFFECTLEVEL_LOW 0x00	//�͵�ƽʹ��
/* definition Data type  --------------------------------------------------------*/
/* �������ݻ���ṹ�� */
typedef struct  
{
	uint16_t flag; //���յ���������
	uint16_t count; //���յ����ֽ���
	uint8_t buff[BUFF_SIZE]; //����ռ�
}USART_BUFF;

/* GPIOX���ýṹ�� ----------------------------------------------*/
typedef struct  
{
	GPIO_TypeDef *GPIOx; /* GPIOA/GPIOB/GPIOC/GPIOD/GPIOE/GPIOF/GPIOG */
	uint16_t GPIO_Pin; /* GPIO_Pin_0~GPIO_Pin_15 */
	uint8_t LevelInit;	/* ��ʼ���Ƿ���Ҫʹ�� 0����ʹ�ܣ�1��ʹ�� */
	uint8_t EffectLevel; /* ʹ�ܵ�ƽ 0���͵�ƽʹ�ܣ�1���ߵ�ƽʹ�� */
}Gpio_HandleTypeDef;

#if(PWM_GET)
/* PWM���벶���ʱ�ṹ�� ----------------------------------------------*/
typedef struct  
{
	uint16_t Channel_HighTime; //�ߵ�ƽʱ��
	uint16_t Channel_Period; //������
	uint16_t Channel_RisingTimeLast; //���µ�������ʱ��
	uint16_t Channel_RisingTimeNow; //������ʱ��
	uint16_t Channel_FallingTime; //�½���ʱ��
	uint16_t Channel_Percent; //�ߵ�ƽռ�������ڵİٷֱ�
	uint8_t  Channel_Edge; //��־������״̬ �½���1 ������0
}PWM_INPIT_CAPTURE_TIME;
#endif //PWM_GET
#if(PWM_IN_INFRARED)
/* ����ң�������� -------------------------------------------------------- */
typedef struct  
{
	/* ��־�� */
	uint16_t Flag_recv_Sync; //���յ�ͬ����ͷ
	uint16_t Flag_recv_Key; //���յ�һ�������İ�����Ϣ
	uint16_t Flag_recv_Rising; //���յ��ߵ�ƽ��־
	/* ������ */
	uint16_t Keep_Time; //�ߵ�ƽ����ʱ�� 
	uint16_t Repeat_Number; //��������������ظ���һ�����Ĵ���
	/* ��ֵ */
	uint32_t Key_Value; //���������ļ�ֵ
}PWM_INFRARED_REMOTE_DECODE;
#endif //PWM_IN_INFRARED
/* ģ����Ϣ�ṹ�� ------------------------------------------------*/
/* ����ģ�� */
typedef struct
{
	MODULETYPE moduleType;// ģ������
	UART_HandleTypeDef *huartx;//UART����
	uint32_t			RxTotalTimeout;	/*!< UART Rx Transfer Total Timeout */ //��ʱʱ��
	uint32_t			RxByteTimeout;	/*!< UART Rx Transfer Byte Timeout */ //�ֽڼ䳬ʱʱ��
	Gpio_HandleTypeDef gpioPower;//��Դ����
	GPIO_PinState lastPowerState;//�ϴε�Դ״̬ ENABLE/DISABLE
	uint32_t errorBase;//���������
}MODULEUART_HandleTypeDef;


/* Exported variable --------------------------------------------------------*/

#if(DOG_IWDG)
extern uint32_t sysTick;
extern uint32_t iwdg_LastFeedTime;
#endif //DOG_IWDG
#if(STANDBY_MODE)
extern uint16_t key_press_long;
extern uint16_t key_press_short;
#endif //STANDBY_MODE
#if(ADC_DMA)
extern uint32_t Adc_Dma_Buff[COLLECT_NUMBER];
#endif //ADC_DMA
extern USART_BUFF SERIALPORT_RECVBUFF;
#if(SERIALPORT)
extern MODULEUART_HandleTypeDef MODULEUART_SERIALPORT;
#endif //SERIALPORT
#if(LED)
extern const Gpio_HandleTypeDef GPIOx_LED0;
extern const Gpio_HandleTypeDef GPIOx_LED1;
#endif //LED
#if(KEY)
extern const Gpio_HandleTypeDef GPIOx_KEYUP;
extern const Gpio_HandleTypeDef GPIOx_KEYDO;
extern const Gpio_HandleTypeDef GPIOx_KEYLE;
extern const Gpio_HandleTypeDef GPIOx_KEYRI;
#endif //KEY
#if(BEEP)
extern const Gpio_HandleTypeDef GPIOx_BEEP;
#endif //BEEP
#if(PWM_IN_GET)
extern PWM_INPIT_CAPTURE_TIME PWM_INPIT_CAPTURE_TIM5_CHANNEL1;
#endif //PWM_IN_GET
#if(PWM_IN_INFRARED)
extern PWM_INFRARED_REMOTE_DECODE Tim4_InfraredDev;
#endif //PWM_IN_INFRARED

#if(RTC_CLOCK)
extern uint32_t RTCEx_BKUPRead_Value;
extern RTC_DateTypeDef DATE;
extern RTC_TimeTypeDef TIME;
#endif //RTC_CLOCK

#endif //__GLOBAL_VARIABLE_H__


