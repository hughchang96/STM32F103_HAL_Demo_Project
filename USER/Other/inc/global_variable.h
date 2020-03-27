/**
  ******************************************************************************
  * @file    global_variable.h
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
#ifndef  __GLOBAL_VARIABLE_H__
#define  __GLOBAL_VARIABLE_H__
/* INCLUDE -------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "device_config.h"
/* definition constant  --------------------------------------------------------*/
/* 缓冲区大小 */
#define BUFF_SIZE 3072

/* GPIO相关 */
#define LEVELINIT_ENABLE 0x01	//需要电平初始化
#define LEVELINIT_DISABLE 0x00	//不需要电平初始化
#define EFFECTLEVEL_TOP 0x01	//高电平使能
#define EFFECTLEVEL_LOW 0x00	//低电平使能
/* definition Data type  --------------------------------------------------------*/
/* 串口数据缓冲结构体 */
typedef struct  
{
	uint16_t flag; //接收到的命令数
	uint16_t count; //接收到的字节数
	uint8_t buff[BUFF_SIZE]; //缓存空间
}USART_BUFF;

/* GPIOX配置结构体 ----------------------------------------------*/
typedef struct  
{
	GPIO_TypeDef *GPIOx; /* GPIOA/GPIOB/GPIOC/GPIOD/GPIOE/GPIOF/GPIOG */
	uint16_t GPIO_Pin; /* GPIO_Pin_0~GPIO_Pin_15 */
	uint8_t LevelInit;	/* 初始化是否需要使能 0：不使能；1：使能 */
	uint8_t EffectLevel; /* 使能电平 0：低电平使能；1：高电平使能 */
}Gpio_HandleTypeDef;

#if(PWM_GET)
/* PWM输入捕获计时结构体 ----------------------------------------------*/
typedef struct  
{
	uint16_t Channel_HighTime; //高电平时间
	uint16_t Channel_Period; //周期数
	uint16_t Channel_RisingTimeLast; //最新的上升沿时间
	uint16_t Channel_RisingTimeNow; //上升沿时间
	uint16_t Channel_FallingTime; //下降沿时间
	uint16_t Channel_Percent; //高点平占整个周期的百分比
	uint8_t  Channel_Edge; //标志按键的状态 下降：1 上升：0
}PWM_INPIT_CAPTURE_TIME;
#endif //PWM_GET
#if(PWM_IN_INFRARED)
/* 红外遥控器解码 -------------------------------------------------------- */
typedef struct  
{
	/* 标志类 */
	uint16_t Flag_recv_Sync; //接收到同步码头
	uint16_t Flag_recv_Key; //接收到一个完整的按键信息
	uint16_t Flag_recv_Rising; //接收到高电平标志
	/* 计数类 */
	uint16_t Keep_Time; //高电平持续时间 
	uint16_t Repeat_Number; //连发码次数，即重复上一按键的次数
	/* 键值 */
	uint32_t Key_Value; //解析出来的键值
}PWM_INFRARED_REMOTE_DECODE;
#endif //PWM_IN_INFRARED
/* 模块信息结构体 ------------------------------------------------*/
/* 串口模块 */
typedef struct
{
	MODULETYPE moduleType;// 模块类型
	UART_HandleTypeDef *huartx;//UART配置
	uint32_t			RxTotalTimeout;	/*!< UART Rx Transfer Total Timeout */ //超时时间
	uint32_t			RxByteTimeout;	/*!< UART Rx Transfer Byte Timeout */ //字节间超时时间
	Gpio_HandleTypeDef gpioPower;//电源引脚
	GPIO_PinState lastPowerState;//上次电源状态 ENABLE/DISABLE
	uint32_t errorBase;//基本错误号
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


