/**
  ******************************************************************************
  * @file    protocol_serialport.c
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
#include "protocol_serialport.h"

#if(0)
#include "string.h"
/**
  * @brief  解析从串口下行的帧数据
  * @param  buffer：串口接收数据结构体地址
  * @retval 错误号
  */
uint32_t Import_Frame(USART_RECVDATA *buffer)
{
	uint16_t start = 0;
	uint8_t cs = 0;
	for(start = 0;start<sizeof(buffer);start++)
	{	
		if(!(buffer->data[start] == 0xCA && buffer->data[start] == buffer->data[start+6]))//判断起始位与标志位
		{			
			currentFrameCount = buffer->datacount;
			USER_ERROR("ERROR_DT1_NOSTARTBIT");
			return ERROR_DT1_NOSTARTBIT;
		}
		else
			break;
	}
	/* 命令类型  */
	protocol_App_Down.cmdType = (buffer->data[start+1]<<8) + buffer->data[start+2];
	/* 命令序号  */
	protocol_App_Down.cmdNo = buffer->data[start+3];
	/* 数据域长度，低字节在前，高字节在后  */
	protocol_App_Down.dataCount = (buffer->data[start+5]<<8) + buffer->data[start+4];
	/*  判断数据长度是否正确 */
	if (buffer->datacount < start + 9 + protocol_App_Down.dataCount)
	{
		currentFrameCount = start + 1;
		USER_ERROR("ERROR_DT1_DATANOTENOUGH");
		return ERROR_DT1_DATANOTENOUGH;
	}
	/* 数据域  */
	protocol_App_Down.data = &buffer->data[start+7];
	/* 判断结束位  */
	if(buffer->data[protocol_App_Down.dataCount+start+8] != 0xAC)
	{
		currentFrameCount = start + 1;
		USER_ERROR("ERROR_DT1_ENDBIT");
		return ERROR_DT1_ENDBIT;
	}
	/* 校验码  */
	cs = Tool_CheckSum(buffer->data, start, 7 + protocol_App_Down.dataCount);
	if (cs != buffer->data[start + 7 + protocol_App_Down.dataCount])
	{
		currentFrameCount = start + 1;
		USER_ERROR("ERROR_DT1_CHECKCODE");
		return ERROR_DT1_CHECKCODE;
	}
	currentFrameCount = start + 9 + protocol_App_Down.dataCount;
	return ERROR_NO;
}

/**
	* @brief  组织发送帧
  * @param  errorno：错误号
  * @retval void
  */
void GetFrame(uint32_t error, USART_RECVDATA *SERIALPORT_SENDDATA)
{

		/* 依据错误号，设置命令类型、数据域 */
		if (error != ERROR_NO)
		{
			//错误
			protocol_App_Up.cmdType = protocol_App_Down.cmdType + 0xC000;
			memcpy(protocol_App_Up.data, &error, 3);
			protocol_App_Up.dataCount = 3;
		}
		else
		{
			//正确
			protocol_App_Up.cmdType = protocol_App_Down.cmdType + 0x8000;
		}
		//组织发送帧
		protocol_App_Up.cmdNo = protocol_App_Down.cmdNo;
		//数据域调整位置/*  */
		memmove(&SERIALPORT_SENDDATA->data[7], SERIALPORT_SENDDATA->data, protocol_App_Up.dataCount);//当拷贝区域重叠，目标地址>源地址时，使用memcpy出错
		//起始位/*  */
		SERIALPORT_SENDDATA->data[0] = PROTOCOL_APP_STARTBIT;
		//命令类型/*  */
		SERIALPORT_SENDDATA->data[1] = protocol_App_Up.cmdType >> 8;
		SERIALPORT_SENDDATA->data[2] = protocol_App_Up.cmdType;
		//命令序号/*  */
		SERIALPORT_SENDDATA->data[3] = protocol_App_Up.cmdNo;
		//数据域长度/*  */
		SERIALPORT_SENDDATA->data[4] = protocol_App_Up.dataCount;
		SERIALPORT_SENDDATA->data[5] = protocol_App_Up.dataCount >> 8;
		//标识符（起始位）/*  */
		SERIALPORT_SENDDATA->data[6] = PROTOCOL_APP_STARTBIT;
		/* 校验位 */
		SERIALPORT_SENDDATA->data[7 + protocol_App_Up.dataCount] = Tool_CheckSum(SERIALPORT_SENDDATA->data, 0, 7 + protocol_App_Up.dataCount);
		/* 结束位 */
		SERIALPORT_SENDDATA->data[8 + protocol_App_Up.dataCount] = PROTOCOL_APP_ENDBIT;
		/* 帧长度 */
		SERIALPORT_SENDDATA->datacount = 9 + protocol_App_Up.dataCount;
}

#endif //SERIALPORT


