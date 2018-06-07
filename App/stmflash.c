#include "stmflash.h"

int16_t DataTrim[8]={0,0,0,0,0,0,0,0};
void ANO_Param_Read(void)
{
	ANO_Flash_Read((u8 *)(DataTrim),sizeof(DataTrim));
//	if(ANO_Param.firstintiflag != FIRST_INIT_FLAG)//???????
//	{
//		ANO_Param_Init();
//	}
//	if(ANO_Param.firstintiflag != FIRST_INIT_FLAG)//???????
//	{
//		while(1);
//	}
}

void ANO_Param_Save(void)
{
	ANO_Flash_Write((u8 *)(DataTrim),sizeof(DataTrim));
//	g_v_PIDInit();
}

u16 save_pid_en = 0;
void PID_Save_Overtime(u16 ms,u16 dTms)
{
	if(save_pid_en!=0)
	{
		save_pid_en++;
	}
	
	if(save_pid_en>=(ms/dTms))
	{
		ANO_Param_Save();
		save_pid_en = 0;
	}

}


