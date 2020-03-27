/**
  ******************************************************************************
  * @file    protocol_serialport.c
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
#include "protocol_serialport.h"

#if(0)
#include "string.h"
/**
  * @brief  �����Ӵ������е�֡����
  * @param  buffer�����ڽ������ݽṹ���ַ
  * @retval �����
  */
uint32_t Import_Frame(USART_RECVDATA *buffer)
{
	uint16_t start = 0;
	uint8_t cs = 0;
	for(start = 0;start<sizeof(buffer);start++)
	{	
		if(!(buffer->data[start] == 0xCA && buffer->data[start] == buffer->data[start+6]))//�ж���ʼλ���־λ
		{			
			currentFrameCount = buffer->datacount;
			USER_ERROR("ERROR_DT1_NOSTARTBIT");
			return ERROR_DT1_NOSTARTBIT;
		}
		else
			break;
	}
	/* ��������  */
	protocol_App_Down.cmdType = (buffer->data[start+1]<<8) + buffer->data[start+2];
	/* �������  */
	protocol_App_Down.cmdNo = buffer->data[start+3];
	/* �����򳤶ȣ����ֽ���ǰ�����ֽ��ں�  */
	protocol_App_Down.dataCount = (buffer->data[start+5]<<8) + buffer->data[start+4];
	/*  �ж����ݳ����Ƿ���ȷ */
	if (buffer->datacount < start + 9 + protocol_App_Down.dataCount)
	{
		currentFrameCount = start + 1;
		USER_ERROR("ERROR_DT1_DATANOTENOUGH");
		return ERROR_DT1_DATANOTENOUGH;
	}
	/* ������  */
	protocol_App_Down.data = &buffer->data[start+7];
	/* �жϽ���λ  */
	if(buffer->data[protocol_App_Down.dataCount+start+8] != 0xAC)
	{
		currentFrameCount = start + 1;
		USER_ERROR("ERROR_DT1_ENDBIT");
		return ERROR_DT1_ENDBIT;
	}
	/* У����  */
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
	* @brief  ��֯����֡
  * @param  errorno�������
  * @retval void
  */
void GetFrame(uint32_t error, USART_RECVDATA *SERIALPORT_SENDDATA)
{

		/* ���ݴ���ţ������������͡������� */
		if (error != ERROR_NO)
		{
			//����
			protocol_App_Up.cmdType = protocol_App_Down.cmdType + 0xC000;
			memcpy(protocol_App_Up.data, &error, 3);
			protocol_App_Up.dataCount = 3;
		}
		else
		{
			//��ȷ
			protocol_App_Up.cmdType = protocol_App_Down.cmdType + 0x8000;
		}
		//��֯����֡
		protocol_App_Up.cmdNo = protocol_App_Down.cmdNo;
		//���������λ��/*  */
		memmove(&SERIALPORT_SENDDATA->data[7], SERIALPORT_SENDDATA->data, protocol_App_Up.dataCount);//�����������ص���Ŀ���ַ>Դ��ַʱ��ʹ��memcpy����
		//��ʼλ/*  */
		SERIALPORT_SENDDATA->data[0] = PROTOCOL_APP_STARTBIT;
		//��������/*  */
		SERIALPORT_SENDDATA->data[1] = protocol_App_Up.cmdType >> 8;
		SERIALPORT_SENDDATA->data[2] = protocol_App_Up.cmdType;
		//�������/*  */
		SERIALPORT_SENDDATA->data[3] = protocol_App_Up.cmdNo;
		//�����򳤶�/*  */
		SERIALPORT_SENDDATA->data[4] = protocol_App_Up.dataCount;
		SERIALPORT_SENDDATA->data[5] = protocol_App_Up.dataCount >> 8;
		//��ʶ������ʼλ��/*  */
		SERIALPORT_SENDDATA->data[6] = PROTOCOL_APP_STARTBIT;
		/* У��λ */
		SERIALPORT_SENDDATA->data[7 + protocol_App_Up.dataCount] = Tool_CheckSum(SERIALPORT_SENDDATA->data, 0, 7 + protocol_App_Up.dataCount);
		/* ����λ */
		SERIALPORT_SENDDATA->data[8 + protocol_App_Up.dataCount] = PROTOCOL_APP_ENDBIT;
		/* ֡���� */
		SERIALPORT_SENDDATA->datacount = 9 + protocol_App_Up.dataCount;
}

#endif //SERIALPORT


