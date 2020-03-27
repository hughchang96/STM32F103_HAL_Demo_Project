/**
  ******************************************************************************
  * @file    protocol_serialport.h
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

#ifndef  __PROTOCOL_SERIALPORT_H__
#define  __PROTOCOL_SERIALPORT_H__

/* INCLUDE -------------------------------------------------------------------*/
#include "device_config.h"

#if(0)
#include "tool.h"
#include "error.h"
#include "global_variable.h"

/* Exported_Functions --------------------------------------------------------*/
uint32_t Import_Frame(USART_RECVDATA *buffer);
void GetFrame(uint32_t error, USART_RECVDATA *SERIALPORT_SENDDATA);
/* Exported constants --------------------------------------------------------*/

#endif //SERIALPORT
#endif //__PROTOCOL_SERIALPORT_H__
