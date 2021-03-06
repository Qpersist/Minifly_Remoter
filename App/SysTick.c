/******************* (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：SysTick.c
 * 描述    ：SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
 *           常用的有 1us 10us 1ms 中断。         
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |                 |
 *          |      无         |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ：王祥 
 * 论坛    ：
 * 淘宝    ：
**********************************************************************************/

#include "SysTick.h"

static __IO u32 TimingDelay;
int16_t cnt_1ms=0,cnt_2ms=0,cnt_5ms=0,cnt_10ms=0,cnt_30ms=0;
/*  
* 函数名：SysTick_Init  
* 描述  ：启动系统滴答定时器 SysTick  
* 输入  ：无  
* 输出  ：无  
* 调用  ：外部调用   
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
  /* SystemFrequency / 1000    1ms 中断一次  
   * SystemFrequency / 100000  10us 中断一次  
   * SystemFrequency / 1000000 1us 中断一次  
   */  
//  if (SysTick_Config(SystemFrequency / 100000)) // ST3.0.0 库版本   
	if (SysTick_Config(SystemCoreClock / 1000000)) // ST3.5.0 库版本   
	{    
	  /* Capture error */    
	  while (1);   
	}   
	  // 关闭滴答定时器     
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;   
} 
/*
 * 函数名：Delay_us
 * 描述  ：us延时程序,1us为一个单位
 * 输入  ：- nTime
 * 输出  ：无
 * 调用  ：Delay_us( 1 ) 则实现的延时为 1 * 1us = 1us
 *       ：外部调用 
 */

void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}


/*
 * 函数名：TimingDelay_Decrement
 * 描述  ：获取节拍程序
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在 SysTick 中断函数 SysTick_Handler()调用
 */  
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
	TimingDelay--;
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/







