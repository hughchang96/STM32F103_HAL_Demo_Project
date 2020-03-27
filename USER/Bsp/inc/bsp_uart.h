/**
  ******************************************************************************
  * @file    bsp_uart.h
  * @author  ’≈ª¢
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
*/

#ifndef  __BSP_UART_H__
#define  __BSP_UART_H__


/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"
#include "global_variable.h"


/* Exported_Functions --------------------------------------------------------*/
void UART_NVIC_Init(UART_HandleTypeDef *huart, 	USART_BUFF *recv_data);
void USART_IDLE_Receive(UART_HandleTypeDef *huart);

/* Exported constants --------------------------------------------------------*/


#endif //__BSP_UART_H__
