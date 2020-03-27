/**
  ******************************************************************************
  * @file    tool.h
  * @author  ÕÅ»¢
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
*/
#ifndef  __TOOL_H__
#define  __TOOL_H__
/* INCLUDE -------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "device_config.h"

/* Exported constants --------------------------------------------------------*/
/* µ÷ÊÔºê */
#if(DEBUG_MODE)
	#define DEBUG_USER_PRINTF   1
	#define DEBUG_USER_INFO     1
	#define DEBUG_USER_DEBUG    1
	#define DEBUG_USER_ERROR    1
#endif //DEBUG_MODE

#if(DEBUG_USER_PRINTF)
	#define USER_PRINTF(format,...) printf(format "\r\n",##__VA_ARGS__)
#else
	#define USER_PRINTF(format,...)
#endif //USER_PRINTF

#if(DEBUG_USER_INFO)
	#define USER_INFO(format,...)   printf("[%s Line:%d function:%s]Info:"format "\r\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)
#else
	#define USER_INFO(format,...)
#endif //USER_INFO

#if(DEBUG_USER_DEBUG)
	#define USER_DEBUG(format,...)  printf("[%s Line:%d function:%s]Debug:"format "\r\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)
#else
	#define USER_DEBUG(format,...)
#endif //USER_DEBUG

#if(DEBUG_USER_ERROR)
	#define USER_ERROR(format,...)  printf("[%s Line:%d function:%s]Error:"format "\r\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)
#else
	#define USER_ERROR(format,...)
#endif //USER_ERROR
	
/* Exported_Functions */
uint32_t hex_to_int(uint8_t hex_h,uint8_t hex_l);
void int_to_hex(uint16_t a,uint8_t *b);
uint8_t Tool_CheckSum(uint8_t * pData, uint16_t offset, uint16_t count);

#endif //__TOOL_H__

