/**
  ******************************************************************************
  * @file    bsp_wwdg.c
  * @author  �Ż�
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   
  ******************************************************************************
  * @attention:	WWDG ʱ����㣺	
	*		APB1ʱ��Ƶ�ʣ�36MHZ��/(4096*��Ƶϵ����8����= x MHZ��910us��		��1/1HZ = 1s��							
  *		x(910) * (127-�ϴ���ֵ(95))  <	 ˢ�´���(58.2-28.2) < x(910) * 64 = 58.2ms
  *				�ϴ���ʱ��(28.2)						  ����ι��ʱ��(30ms)			�´���ʱ��(58.2)
  ******************************************************************************
*/
#include "bsp_wwdg.h"
#if(DOG_WWDG)

#include "wwdg.h"
#include "tool.h"
/**
  * @brief  �����жϺ��Զ��ڵݼ���64֮ǰι��
  * @param  hwwdg�����ڿ��Ź�������Ϣ�ṹ��
  * @retval void
  */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
		HAL_WWDG_Refresh(hwwdg);
}
#endif //DOG_WWDG

