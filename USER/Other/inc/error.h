/**
  ******************************************************************************
  * @file    error.h
  * @author  �Ż�
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention��	
  *
	*
  ******************************************************************************
*/
#ifndef  __ERROR_H__
#define  __ERROR_H__

/* INCLUDE -------------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
#define ERROR_NO 0x000000 //�޴���
/*  DT0 ---------------------------------------------------------------------- */
#define ERROR_DT0_PROTOCOL 0x000000//Э�����
#define ERROR_DT0_SERIALPORT 0x010000 //�����ڴ���
#define ERROR_DT0_ENCRYPT 0x020000 //����оƬ����
#define ERROR_DT0_BT 0x030000 //����оƬ����


/*  DT1 ---------------------------------------------------------------------- */
/*  ͨѶЭ����� */
#define ERROR_DT1_NOSTARTBIT 0x000100//δ��⵽��ʼλ
#define ERROR_DT1_DATANOTENOUGH 0x000200//δ���յ�����֡
#define ERROR_DT1_ENDBIT 0x000300//֡����λ����
#define ERROR_DT1_CHECKCODE 0x000400//֡У�������
#define ERROR_DI1_CMDABNORMAL 0x000500//�쳣��Ӧ������
#define ERROR_DI1_CMDNOTMATCH 0x000600//��Ӧ�����벻ƥ��
#define ERROR_DI1_NOCMD 0x000700//�޴�������
#define ERROR_DI1_DATAFORMAT 0x000800//�������ʽ���� 
#define ERROR_DI1_NOMODULE 0x000900//�޶�Ӧģ��
#define ERROR_DI1_GETFRAME 0x000A00//��֡ʧ��

/* ģ����� */
#define ERROR_DI1_INIT 0x001000//ģ���ʼ������
#define ERROR_DI1_TRANSMIT 0x001500//ģ�鴫�����ݴ���
#define ERROR_DI1_RECEIVE_TIMEOUT 0x001600//ģ��������ݳ�ʱ
#define ERROR_DI1_TXDATA 0x001700//��������ݴ���
#define ERROR_DI1_RXDATA 0x001900//���յ���������
#define ERROR_DI1_NOENOUGHRXSIZE 0x001A00//���ջ���������
#define ERROR_DI1_ABORT 0x001B00//���յ���ģ����ֹ����
#define ERROR_DI1_POWERCLOSED 0x001C00//ģ���Դδ�򿪣���Ҫ��ǰ�ֶ��򿪵�Դ������ģ��ִ��ĳЩ����ʱ����Ҫ��ǰ�򿪵�Դ����һЩ�������簲ȫ��Ԫ2.0ִ�з�ӡ��д����Ҫ��ǰ�򿪵�Դ��������֤��
#define ERROR_DI1_MODULERETURN 0x800000//ģ�鷵�ش����

/*  DT2 ---------------------------------------------------------------------- */


#endif //__ERROR_H__
