

#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define ON  0
#define OFF 1

//带参宏，可以像内联函数一样使用
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)

#define LED2(a)	if (a)	\
				GPIO_SetBits(GPIOA,GPIO_Pin_2);\
				else		\
				GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define LED3(a)	if (a)	\
				GPIO_SetBits(GPIOB,GPIO_Pin_3);\
				else		\
				GPIO_ResetBits(GPIOB,GPIO_Pin_3)
				
#define LED4(a)	if (a)	\
				GPIO_SetBits(GPIOB,GPIO_Pin_12);\
				else		\
				GPIO_ResetBits(GPIOB,GPIO_Pin_12)
					
					
#define LED1_turn() GPIO_WriteBit(GPIOC, GPIO_Pin_13,\
					(BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))));  

#define LED2_turn() GPIO_WriteBit(GPIOA, GPIO_Pin_2,\
					(BitAction)((1-GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2))));					

#define LED3_turn() GPIO_WriteBit(GPIOB, GPIO_Pin_3,\
					(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_3))));
	
#define LED4_turn() GPIO_WriteBit(GPIOB, GPIO_Pin_12,\
					(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12))));					
void LED_GPIO_Config(void);

#endif /* __LED_H */
