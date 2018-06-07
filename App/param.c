#include "param.h"
#include "stmflash.h"

#include "ANO_Drv_EEPROM.h"

#define EE_RcDataTrimROLL	1
#define EE_RcDataTrimPITCH	2
#define EE_RcDataTrimYAW	3
#define EE_RcDataTrimTHROTTLE	4
#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
#define SIZE sizeof(DataTrim)		//数组长度
	
//uint16_t DataTrim[8]={0,0,0,0,0,0,0,0};

void Param_Init(void)
{	
	READ_CONF();	
}

void SAVE_RC_OFFSET(void)
{
//	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimROLL], DataTrim[ROLL]);
//	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimPITCH], DataTrim[PITCH]);
//	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimYAW], DataTrim[YAW]);
//	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimTHROTTLE], DataTrim[THROTTLE]);
//					STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)DataTrim,SIZE);
}
void READ_RC_OFFSET(void)
{
//	uint16_t temp[4];
//	u8 i=0;
//	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimROLL], &temp[0]);
//	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimPITCH], &temp[1]);
//	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimYAW], &temp[2]);
//	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimTHROTTLE], &temp[3]);
//	
//	for(i=0;i<4;i++)
//		DataTrim[i] = temp[i];
//	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)DataTrim,SIZE);
}

void READ_CONF(void)
{
	READ_RC_OFFSET();
}
