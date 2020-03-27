/**
  ******************************************************************************
  * @file    tool.h
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
#include "tool.h"

/**
  * @brief  2位16进制转10进制，高前低后：
  * @param  hex_h:高8位
	* @param  hex_l:低8位
  * @retval 十进制
  */
uint32_t hex_to_int(uint8_t hex_h,uint8_t hex_l)
{
	return (hex_h<<8)|hex_l;
}

/**
  * @brief 10进制转2位16进制，高前低后：
	* @param a:需要转化的10进制数
	* @param b:转换后的16进制两位指针
  * @retval void
  */
void int_to_hex(uint16_t a,uint8_t *b)
{
	b[0]=a>>8;//转16取高
	b[1]=(a<<24)>>24;//转16取低
}

/**
  * @brief  计算校验和	各字节的模256的和（各字节二进制算术和，不计超过256的溢出值）
  * @param  pData：指向数据的指针
						offset：偏移地址
						count：参与计算数据的数量
  * @retval 校验码
  */
uint8_t Tool_CheckSum(uint8_t * pData, uint16_t offset, uint16_t count)
{
	uint16_t i = 0;
	uint8_t cs = 0;
	for (i = 0; i < count; i++)
	{
		cs += pData[offset + i];
	}
	return cs;
}

