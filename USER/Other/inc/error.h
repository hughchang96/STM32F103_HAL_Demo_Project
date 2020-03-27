/**
  ******************************************************************************
  * @file    error.h
  * @author  张虎
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention：	
  *
	*
  ******************************************************************************
*/
#ifndef  __ERROR_H__
#define  __ERROR_H__

/* INCLUDE -------------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
#define ERROR_NO 0x000000 //无错误
/*  DT0 ---------------------------------------------------------------------- */
#define ERROR_DT0_PROTOCOL 0x000000//协议错误
#define ERROR_DT0_SERIALPORT 0x010000 //主串口错误
#define ERROR_DT0_ENCRYPT 0x020000 //加密芯片错误
#define ERROR_DT0_BT 0x030000 //蓝牙芯片错误


/*  DT1 ---------------------------------------------------------------------- */
/*  通讯协议错误 */
#define ERROR_DT1_NOSTARTBIT 0x000100//未检测到起始位
#define ERROR_DT1_DATANOTENOUGH 0x000200//未接收到完整帧
#define ERROR_DT1_ENDBIT 0x000300//帧结束位错误
#define ERROR_DT1_CHECKCODE 0x000400//帧校验码错误
#define ERROR_DI1_CMDABNORMAL 0x000500//异常响应命令码
#define ERROR_DI1_CMDNOTMATCH 0x000600//响应命令码不匹配
#define ERROR_DI1_NOCMD 0x000700//无此命令码
#define ERROR_DI1_DATAFORMAT 0x000800//数据域格式错误 
#define ERROR_DI1_NOMODULE 0x000900//无对应模块
#define ERROR_DI1_GETFRAME 0x000A00//组帧失败

/* 模块错误 */
#define ERROR_DI1_INIT 0x001000//模块初始化错误
#define ERROR_DI1_TRANSMIT 0x001500//模块传输数据错误
#define ERROR_DI1_RECEIVE_TIMEOUT 0x001600//模块接收数据超时
#define ERROR_DI1_TXDATA 0x001700//传输的数据错误
#define ERROR_DI1_RXDATA 0x001900//接收到错误数据
#define ERROR_DI1_NOENOUGHRXSIZE 0x001A00//接收缓冲区不足
#define ERROR_DI1_ABORT 0x001B00//接收到该模块中止命令
#define ERROR_DI1_POWERCLOSED 0x001C00//模块电源未打开，需要提前手动打开电源（部分模块执行某些功能时，需要提前打开电源并做一些操作，如安全单元2.0执行封印读写，需要提前打开电源并密码验证）
#define ERROR_DI1_MODULERETURN 0x800000//模块返回错误号

/*  DT2 ---------------------------------------------------------------------- */


#endif //__ERROR_H__
