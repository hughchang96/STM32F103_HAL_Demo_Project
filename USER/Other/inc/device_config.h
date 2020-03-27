/**
  ******************************************************************************
  * @file    device_config.h
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

#ifndef  __DEVICE_CONFIG_H__
#define  __DEVICE_CONFIG_H__

// <<< Use Configuration Wizard in Context Menu >>>

/* DEBUG_MODE -------------------------------------------------------------------*/
//<h>DEBUG_MODE
//<e>DEBUG_MODE
//</e>
//<i>是否开启测试模式
#define DEBUG_MODE 1
//</h>
//<i>选择是否开启测试模式

/* 模块配置 -----------------------------------------------------------------------*/

//<h>MODULE_CHOICE

/* -------------主串口---------------- */
//<e>SERIALPORT
#define SERIALPORT 1
#if(SERIALPORT)
	//<o>波特率
	//<9600=> 9600  
	//<115200=> 115200
	//<1152000=> 1152000 
	#define BAUD_RATE 9600
	//<o>字节超时时间(ms)
	#define SERIALPORT_BYTETIMEOUT	20
	//<o>总超时时间(ms)
	#define SERIALPORT_TOTALTIMEOUT	3000
#endif //SERIALPORT
//</e>
//<i>与上位机通信串口:USART1,字节中断+idle

/* -------------按键---------------- */
//<e>KEY
#define KEY 1
#if(KEY)
	//<h>按键检测方式
	//<e>KEY_EXIT
	//</e>
	//<i>中断模式
	#define KEY_EXIT 1
	
	//<e>KEY_SCAN
	//</e>
	//<i>电平扫描
	#define KEY_SCAN 1
	//</h>
#endif //KEY
//</e>	
//<i>按键实验（线中断 扫描电平）

/* -------------LED---------------- */
//<e>LED
#define LED 0
//</e>
//<i> LED

/* -------------蜂鸣器---------------- */
//<e>BEEP
#define BEEP 0
//</e>
//<i>蜂鸣器


/* -------------独立看门狗---------------- */
//<e>DOG_IWDG
#define DOG_IWDG 0
#if(DOG_IWDG)
//<o>看门狗最大喂食间隔(ms)
#define IWDG_FEEDTIME	4000
#endif //DOG_IWDG
//</e>
//<i>如果不在最大喂食间隔内喂食则复位重启

/* -------------窗口看门狗---------------- */
//<e>DOG_WWDG
#define DOG_WWDG 0
//</e>
//<i>如果不在规定窗口期内喂狗则复位重启，开启中断后自动在递减到64之前喂狗避免复位

/* -------------定时器---------------- */
//<e>TIM
#define TIM 1 //定时器
//</e>
//<i>使用定时器实现LED灯的反转

/* -------------PWM---------------- */
//<e>PWM
#define PWM 1 //定时器
#if(PWM)
//<e>PWM_OUT
#define PWM_OUT 0
//</e>
//<i>输出比较：呼吸灯 
//<e>PWM_IN
#define PWM_IN 1
//<e>PWM_IN_INFRARED
#define PWM_IN_INFRARED 0
//</e>
//<i>红外遥控器接收
//<e>PWM_IN_GET
#define PWM_IN_GET 0
//</e>
//<i>输入捕获：获取脉宽、频率、周期等
//</e>
#endif //PWM
//</e>
//<i>PWM输出比较：呼吸灯 输入捕获：获取脉宽、频率、周期等

/* -------------实时时钟---------------- */
//<e>RTC_CLOCK
#define RTC_CLOCK 1
#if(RTC_CLOCK)
//<o>后备区域寄存器写入值
#define RTCEx_BKUP_Value 0x5051
//<i>用来判断是否需要重新初始化时间
	//<h>秒表实现方式
	//<e>STOP_WATCH_SECIT
	//</e>
	//<i>RTC基本配置已经包括了此功能的实现，这里只是控制是否将时间打印出来
	#define STOP_WATCH_SECIT 0
	
	//<e>STOP_WATCH_ALRAIT
	//</e>
	//<i>闹钟中断实现秒表
	#define STOP_WATCH_ALRAIT 0
	//</h>
#endif //RTC_CLOCK
//</e>
//<i>不建议禁用此模块，以免系统时间错误。使用systick实现秒中断：秒表

/* -------------待机唤醒---------------- */
//<e>STANDBY_MODE
#define STANDBY_MODE 1 //待机模式
//</e>
//<i>待机唤醒,需要打开KEY模块

/* -------------ADC模数转换---------------- */
//<e>ADC
#define STM_ADC 1 
//<e>ADC_DMA
#define ADC_DMA 1 
//<o>采集次数
#define COLLECT_NUMBER 10
//<o>采集的通道数
#define COLLECT_CHANNEL_NUMBER 1
//</e>
//</e>
//<i>DMA多通道采集采集

/* -------------ADC数模转换---------------- */
//<e>DAC
#define STM_DAC 1 
//</e>
//<i>DAC模拟输出电压 三角波

/* -------------I2C---------------- */
//<e>I2C
#define I2C 1 
//</e>
//<i>与 EEPROM 通过I2C进行数据读写,此模块没有I2C驱动，直接调用读写函数即可

//</h>
//<i>模块配置

// <s.20> Change ID
#define BOOTLOGO  "New Day -> New Life"

// <<< end of configuration section >>>

typedef enum
{
	MODULETYPE_ALL = 0x00, //所有模块
	MODULETYPE_SERIALPORT = 0x01,	//串口
	MODULETYPE_KEY = 0X02, //按键
	MODULETYPE_LED = 0X03, //指示灯
	MODULETYPE_BEEP = 0X04, //蜂鸣器
}MODULETYPE;


#endif //__DEVICE_CONFIG_H__
