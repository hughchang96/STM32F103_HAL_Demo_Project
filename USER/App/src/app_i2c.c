/**
  ******************************************************************************
  * @file    app_i2c.c
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
#include "app_i2c.h"
#if(I2C)

#include "tool.h"
#include "i2c.h"
#include "string.h"

#define ADDR_24LCxx 0xA0

/**
  * @brief  通过I2C来对EEPROM进行读写
  * @param  void
  * @retval void
  */
void App_I2c_EEPROM(void)
{
	uint16_t i;
	uint8_t WriteBuffer[256], ReadBuffer[256];
	
	USER_PRINTF("***************I2C Example********************");
	/* WriteBuffer init */
	for(i=0; i<256; i++)
			WriteBuffer[i]=i;
	/* wrinte date to EEPROM */
	 for(i=0;i<256;i+=8)
  {
		if(HAL_I2C_Mem_Write(&hi2c1, ADDR_24LCxx, i, I2C_MEMADD_SIZE_8BIT,&WriteBuffer[i],8, 3000) == HAL_OK)
				USER_PRINTF("EEPROM 24C02 Write Test OK");
		else
				USER_PRINTF("EEPROM 24C02 Write Test False");
  }
 
	/* read date from EEPROM */
	HAL_I2C_Mem_Read(&hi2c1, ADDR_24LCxx, 0, I2C_MEMADD_SIZE_8BIT,ReadBuffer,256, 3000);
	for(i=0; i<256; i++)
			printf(" 0x%02x ",ReadBuffer[i]);
	printf("\r\n");

	if(memcmp(WriteBuffer,ReadBuffer,256) == 0 ) /* check date */
			USER_PRINTF("EEPROM 24C02 Read Test OK");
	else
			USER_PRINTF("EEPROM 24C02 Read Test False");
}

#endif //I2C

