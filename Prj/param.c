#include "param.h"
//#include "board.h"

#include "ANO_Drv_EEPROM.h"

#define EE_RcDataTrimROLL	1
#define EE_RcDataTrimPITCH	2
#define EE_RcDataTrimYAW	3
#define EE_RcDataTrimTHROTTLE	4

int16_t DataTrim[8];

void Param_Init(void)
{	
	READ_CONF();	
}

void SAVE_RC_OFFSET(void)
{
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimROLL], DataTrim[ROLL]);
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimPITCH], DataTrim[PITCH]);
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimYAW], DataTrim[YAW]);
	EE_WriteVariable(VirtAddVarTab[EE_RcDataTrimTHROTTLE], DataTrim[THROTTLE]);
}
void READ_RC_OFFSET(void)
{
	uint16_t temp[4];
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimROLL], &temp[0]);
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimPITCH], &temp[1]);
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimYAW], &temp[2]);
	EE_ReadVariable(VirtAddVarTab[EE_RcDataTrimTHROTTLE], &temp[3]);
	
	for(u8 i=0;i<4;i++)
		DataTrim[i] = temp[i];
}

void READ_CONF(void)
{
	READ_RC_OFFSET();
}
