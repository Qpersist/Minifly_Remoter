/******************* (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��SysTick.c
 * ����    ��SysTick ϵͳ�δ�ʱ��10us�жϺ�����,�ж�ʱ����������ã�
 *           ���õ��� 1us 10us 1ms �жϡ�         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-----------------
 *          |                 |
 *          |      ��         |
 *          |                 |
 *           -----------------
 * ��汾  ��ST3.5.0
 * ����    ������ 
 * ��̳    ��
 * �Ա�    ��
**********************************************************************************/

#include "SysTick.h"

static __IO u32 TimingDelay;
int16_t cnt_1ms=0,cnt_2ms=0,cnt_5ms=0,cnt_10ms=0,cnt_30ms=0;
/*  
* ��������SysTick_Init  
* ����  ������ϵͳ�δ�ʱ�� SysTick  
* ����  ����  
* ���  ����  
* ����  ���ⲿ����   
*/ 
void SysTick_IRQ(void)
{
		cnt_1ms++;
		cnt_2ms++;
		cnt_5ms++;
		cnt_10ms++;
		cnt_30ms++;
}
void SysTick_Init(void)   
{   
  /* SystemFrequency / 1000    1ms �ж�һ��  
   * SystemFrequency / 100000  10us �ж�һ��  
   * SystemFrequency / 1000000 1us �ж�һ��  
   */  
//  if (SysTick_Config(SystemFrequency / 100000)) // ST3.0.0 ��汾   
	if (SysTick_Config(SystemCoreClock / 1000000)) // ST3.5.0 ��汾   
	{    
	  /* Capture error */    
	  while (1);   
	}   
	  // �رյδ�ʱ��     
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;   
} 
/*
 * ��������Delay_us
 * ����  ��us��ʱ����,1usΪһ����λ
 * ����  ��- nTime
 * ���  ����
 * ����  ��Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1us = 1us
 *       ���ⲿ���� 
 */

void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}


/*
 * ��������TimingDelay_Decrement
 * ����  ����ȡ���ĳ���
 * ����  ����
 * ���  ����
 * ����  ���� SysTick �жϺ��� SysTick_Handler()����
 */  
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
	TimingDelay--;
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/






