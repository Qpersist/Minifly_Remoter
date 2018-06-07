
#include "led.h"
#include <stdio.h>
#include "usart.h"
#include "timer.h"
#include "NRF24L01.h"
#include "appconfig.h"
#include "DataTransfer.h"
#include "spi.h"
#include "SysTick.h"
#include "ADC.h"
#include "param.h"
#include "ANO_Drv_EEPROM.h"
#include "stmflash.h"
T_int16_xyz			g_t_Gyro_CMS;//两次综合后的传感器数据
T_int16_xyz			g_t_Accel_CMS;
T_int16_xyz			g_t_AccelAVG_CMS;
T_float_angle 		g_t_AttAngle_CMS;	//ATT函数计算出的姿态角
vs32				g_vs_Alt_CMS;
T_RC_Data 			g_t_Rc_D_CMS;		//遥控通道数据
T_RC_Control		g_t_Rc_C_CMS;		//遥控功能数据


u8 status;	//用于判断接收/发送状态
u8 txbuf[4]={0,1,2,3};	 //发送缓冲
u8 rxbuf[50];			 //接收缓冲





void Uart1_Init(u32 br_num);


void system_init(void)
{
//	LED_GPIO_Config();
	SysTick_Init();
//	LED1(ON);
//	Delay_us(600000);
//	LED1(OFF);
//	LED2(ON);
//	Delay_us(600000);;
//	LED2(OFF);
//	LED3(ON);
//	Delay_us(600000);
//	LED3(OFF);
//	LED4(ON);
//	Delay_us(600000);
//	LED4(OFF);
	
	Uart1_Init(115200);
//	USART_printf(USART1,(u8 *)"STM32 USART  TX text");
	NVIC_Configuration();
	
	Spi2_Init();
	Nrf24l01_Init(4,40);	
//	Param_Init();
	ANO_Param_Read();
	/*检测NRF模块与MCU的连接*/
	status = Nrf24l01_Check(); 
	if(status == SUCCESS)	  
	{
//		LED1(OFF);
	}
	else
	{
//		LED1(ON);
	}
	g_v_ADCInit();
}

int main(void)
{	
//	u8 i=0;
	system_init();
//		EE_Init();	
	while(1)
	{				
		g_v_AdcCalculate();
//		g_t_Rc_D_CMS.PITCH++;
//		g_t_Rc_D_CMS.ROLL++;
//		g_t_Rc_D_CMS.THROTTLE++;
//		g_t_Rc_D_CMS.YAW++;
		g_v_DataSendRC();
		Nrf_Check_Event();
//		if(10000==cnt_10ms)
//		{
			KeyCheck();
//			cnt_10ms=0;
//		}
	}
}



/*
 * 函数名：NVIC_Configuration
 * 描述  ：中断优先级配置
 * 输入  ：无
 * 输出  ：无	
 */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
//	/* Enable the TIM1 Interrupt */ 													
//    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	

}






