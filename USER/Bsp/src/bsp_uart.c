/**
  ******************************************************************************
  * @file    bsp_uart.c
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
#include "stm32f1xx_hal.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "tool.h"


/**
  * @brief  ʹ�ܴ��ڽ��� idle�ж�
  * @param  huart������в����Ĵ��ڽṹ��ָ��
  * @retval void
  */
void UART_NVIC_Init(UART_HandleTypeDef *huart, 	USART_BUFF *recv_data)
{
	/*ʹ�ܴ��ڿ����ж�*/
	__HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);
	/*ʹ�ܴ��ڽ����ж�*/
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
  * @brief  ����IDLE�жϻص�����
  * @param  huart�������IDLE�жϵĴ��ڽṹ��ָ��
  * @retval void
  */
void USART_IDLE_Receive(UART_HandleTypeDef *huart)
{
	uint16_t i;
	USART_BUFF *recv_data;
	/* �ж��ж������ĸ����贮�� */
	if(huart->Instance == USART1)
	{
		recv_data = &SERIALPORT_RECVBUFF;
	}
	if(huart->Instance == UART5)
	{
//		recv_data = &BT_RECVDATA;
	}
	/* �����ֽ� */
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET)
	{	
		recv_data->buff[recv_data->count++] = (uint16_t)READ_REG(huart->Instance->DR);
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
	}
	/* �Ƿ���������ж� */
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

