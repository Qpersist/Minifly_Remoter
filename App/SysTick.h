#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
void TimingDelay_Decrement(void);
void SysTick_IRQ(void);
#define Delay_ms(x) Delay_us(1000*x)	 //µ¥Î»ms
extern int16_t cnt_1ms,cnt_2ms,cnt_5ms,cnt_10ms,cnt_30ms;
#endif /* __SYSTICK_H */
