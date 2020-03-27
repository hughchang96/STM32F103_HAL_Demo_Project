/**
  ******************************************************************************
  * @file    bsp_uart.c
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
#include "stm32f1xx_hal.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "tool.h"


/**
  * @brief  使能串口接收 idle中断
  * @param  huart：需进行操作的串口结构体指针
  * @retval void
  */
void UART_NVIC_Init(UART_HandleTypeDef *huart, 	USART_BUFF *recv_data)
{
	/*使能串口空闲中断*/
	__HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);
	/*使能串口接收中断*/
	__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
#if(DEBUG_MODE)
	USER_PRINTF("Warnning: UART RECV ERROR!!");
	USER_PRINTF("huart_status  %x",HAL_UART_GetState(huart));	
	USER_PRINTF("huart_error  %x",HAL_UART_GetError(huart));
#endif //DEBUG_MODE
}


/**
  * @brief  串口IDLE中断回调函数
  * @param  huart：需进行IDLE中断的串口结构体指针
  * @retval void
  */
void USART_IDLE_Receive(UART_HandleTypeDef *huart)
{
	uint16_t i;
	USART_BUFF *recv_data;
	/* 判断中断来自哪个外设串口 */
	if(huart->Instance == USART1)
	{
		recv_data = &SERIALPORT_RECVBUFF;
	}
	if(huart->Instance == UART5)
	{
//		recv_data = &BT_RECVDATA;
	}
	/* 接收字节 */
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET)
	{	
		recv_data->buff[recv_data->count++] = (uint16_t)READ_REG(huart->Instance->DR);
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
	}
	/* 是否产生空闲中断 */
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET)
	{
		if(huart->Instance == USART1)
		{
			recv_data->flag++;
		}
		if(huart->Instance == UART5)
		{
#if(DEBUG_MODE)
			for( i = 0; i < recv_data->count; i++ )
			printf("%c", recv_data->buff[i]);
			printf("\r\n");		
		}
#endif
		__HAL_UART_CLEAR_IDLEFLAG(huart);
	}
}


#if(DEBUG_MODE)
/**
  * @brief  Retargets the C library printf function to the USART.
  */
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(MODULEUART_SERIALPORT.huartx, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
#endif //DEBUG_MODE

