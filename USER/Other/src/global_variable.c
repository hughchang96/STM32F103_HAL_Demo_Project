/**
  ******************************************************************************
  * @file    global_variable.c
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

#include "global_variable.h"
#include "main.h"
#if(DOG_IWDG)
/* 滴答计时器计数 */
uint32_t sysTick;
/* 看门狗上次喂狗时间 */
uint32_t iwdg_LastFeedTime;
#endif //DOG_IWDG
#if(PWM_IN_GET)
PWM_INPIT_CAPTURE_TIME PWM_INPIT_CAPTURE_TIM5_CHANNEL1;
#endif //PWM_IN_GET
#if(PWM_IN_INFRARED)
PWM_INFRARED_REMOTE_DECODE Tim4_InfraredDev;
#endif //PWM_IN_INFRARED
#if(RTC_CLOCK)
uint32_t RTCEx_BKUPRead_Value;
RTC_DateTypeDef DATE;
RTC_TimeTypeDef TIME;
#endif //RTC_CLOCK
#if(STANDBY_MODE)
uint16_t key_press_long;
uint16_t key_press_short;
#endif //STANDBY_MODE
#if(ADC_DMA)
uint32_t Adc_Dma_Buff[COLLECT_NUMBER];
#endif //ADC_DMA

/* 主串口接收缓冲结构体 */
USART_BUFF SERIALPORT_RECVBUFF;

/* 主串口模块 */
MODULEUART_HandleTypeDef MODULEUART_SERIALPORT;


/* GPIO */
#if(LED)
const Gpio_HandleTypeDef GPIOx_LED0 = {LED0_GPIO_Port, LED0_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_LOW};
const Gpio_HandleTypeDef GPIOx_LED1 = {LED1_GPIO_Port, LED1_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_LOW};
#endif //LED
#if(KEY)
const Gpio_HandleTypeDef GPIOx_KEYUP = {KEYUP_GPIO_Port, KEYUP_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_TOP};
const Gpio_HandleTypeDef GPIOx_KEYDO = {KEYDO_GPIO_Port, KEYDO_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_LOW};
const Gpio_HandleTypeDef GPIOx_KEYLE = {KEYLE_GPIO_Port, KEYLE_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_LOW};
const Gpio_HandleTypeDef GPIOx_KEYRI = {KEYRI_GPIO_Port, KEYRI_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_LOW};
#endif //KEY
#if(BEEP)
const Gpio_HandleTypeDef GPIOx_BEEP = {BEEP_GPIO_Port, BEEP_Pin, LEVELINIT_DISABLE, EFFECTLEVEL_TOP};
#endif //BEEP
