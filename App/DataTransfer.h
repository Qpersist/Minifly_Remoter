#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_

#include "stm32f10x.h"



extern u8 g_u8a50_DataSend_SMS[50];


void g_v_DataSendStatus(void);	
void g_v_DataSendSenser(void);	
void g_v_DataSendRC(void);

#endif
