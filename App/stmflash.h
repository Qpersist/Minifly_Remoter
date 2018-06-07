#ifndef __STMFLASH_H
#define __STMFLASH_H

#include "stm32f10x.h"
#include "Drv_flash.h"
//#include "ANO_PID.h"
//#include "data.h"
/////////////////////////////////////////////////
//#define FIRST_INIT_FLAG 		0XAA


extern int16_t DataTrim[8];

/////////////////////////////////////////////////
extern struct _save_param_st_pk ANO_Param;

void ANO_Param_Init(void);
void ANO_Param_Read(void);
void ANO_Param_Save(void);
void PID_Save_Overtime(u16 ms,u16 dTms);//PID??????
#endif


