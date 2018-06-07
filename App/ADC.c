#include "ADC.h"
#include "param.h"
#include "stmflash.h"
/*

THR 	- PA0	-	ADC12_IN0
YAW		-	PA1	-	ADC12_IN1
PITCH	-	PA2	-	ADC12_IN2
ROLL	-	PA3	-	ADC12_IN3
POWER	-	PA4	-	ADC12_IN4
KEY_L	-	PB0	-	ADC12_IN8
KEY_R	-	PB1	-	ADC12_IN9

*/
#define ADC1_DR_Address    ((u32)0x4001244cu)

__IO uint16_t g_u16a7_ADCValue_CMS[7];

uint16_t KeyDataL,KeyDataR;
void g_v_ADCInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* Enable ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	/* Configure PC.01  as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		


	
	/* DMA channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 //ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&g_u16a7_ADCValue_CMS;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 7;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址固定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	/* ADC1 configuration */
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	 //禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//开启连续转换模式，即不停地进行ADC转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不使用外部触发转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 7;	 	//要转换的通道数目
	ADC_Init(ADC1, &ADC_InitStructure);
	
	/*配置ADC时钟，为PCLK2的6分频，即12MHz,ADC频率最高不能超过14MHz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
	/*配置ADC1的通道11为55.	5个采样周期，序列为1 */ 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 6, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 7, ADC_SampleTime_55Cycles5);



	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	
	/*复位校准寄存器 */   
	ADC_ResetCalibration(ADC1);
	/*等待校准寄存器复位完成 */
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	/* ADC校准 */
	ADC_StartCalibration(ADC1);
	/* 等待校准完成*/
	while(ADC_GetCalibrationStatus(ADC1));
	
	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//PWM max    3600
//油门1000 - 4000   ad 0-2048
//YAW 1000 - 2000   ad 0-2048
//PIT 1000 - 2000   ad 0-2048
//ROL 1000 - 2000   ad 0-2048
void KeyCheck(void)
{
	static u8 keyFlagL = 1, keyFlagR = 1;
	static u16 timeDelayFlag = 0;
	KeyDataL = (float)g_u16a7_ADCValue_CMS[5];
	KeyDataR = (float)g_u16a7_ADCValue_CMS[6];	
	if(timeDelayFlag)
		timeDelayFlag --;	
	
	if(KeyDataL<100)	//THR+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10000;
		
		if((KeyDataL<100 ) && timeDelayFlag == 1)	
		{
			DataTrim[THROTTLE] -= 2;
			ANO_Param_Save();
			keyFlagL = 0;		
		}
	}
	else if(KeyDataL>750 && KeyDataL<900)	//YAW-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>750 && KeyDataL<900 && timeDelayFlag == 1)
		{
			DataTrim[YAW] += 2;
			ANO_Param_Save();
			keyFlagL = 0;		
		}
	}
	else if(KeyDataL>1080 && KeyDataL<1200 )	//THR-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>1080 && KeyDataL<1200 && timeDelayFlag == 1)
		{
			DataTrim[THROTTLE] += 2;
			ANO_Param_Save();
			keyFlagL = 0;		
		}
	}
	else if(KeyDataL>900 && KeyDataL<1080 )	//YAW+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataL>900 && KeyDataL<1080 && timeDelayFlag == 1)
		{
			DataTrim[YAW] -= 2;
			ANO_Param_Save();
			keyFlagL = 0;
		}
	}
//	else if(KeyDataL>3200 && KeyDataL<3300 && keyFlagL)
//	{
//		if(!timeDelayFlag)
//			timeDelayFlag = 10;
//		
//		if(KeyDataL>3200 && KeyDataL<3300 && keyFlagL && timeDelayFlag == 1)
//		{
//			if(ano.f.STICKMODE)
//			{
//				ano.f.STICKMODE = 0;
//				ano.f.ACCELMODE = 1;
//			}
//			else if(ano.f.ACCELMODE)
//			{
//				ano.f.STICKMODE = 1;
//				ano.f.ACCELMODE = 0;
//			}
//			keyFlagL = 0;
//		}
//	}	
	else if(KeyDataL>4050)
	{
		keyFlagL = 1;
	}
	
	
	if(KeyDataR<100 && keyFlagR)	//PITCH+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR<100 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[PITCH] -= 2;
			ANO_Param_Save();
			keyFlagR = 0;		
		}
	}
	else if(KeyDataR>1900 && KeyDataR<2100 && keyFlagR)	//ROLL+
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>1900 && KeyDataR<2100 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[ROLL] -= 2;
			SAVE_RC_OFFSET();
			keyFlagR = 0;		
		}
	}
	else if(KeyDataR>2600 && KeyDataR<2800 && keyFlagR)	//PITCH-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>2600 && KeyDataR<2800 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[PITCH] += 2;
			SAVE_RC_OFFSET();
			keyFlagR = 0;	
		}			
	}
	else if(KeyDataR>2950 && KeyDataR<3150 && keyFlagR)	//ROLL-
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>2950 && KeyDataR<3150 && keyFlagR && timeDelayFlag == 1)
		{
			DataTrim[ROLL] += 2;
			SAVE_RC_OFFSET();
			keyFlagR = 0;
		}
	}
	else if(KeyDataR>3200 && KeyDataR<3300 && keyFlagR)
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>3200 && KeyDataR<3300 && keyFlagR && timeDelayFlag == 1)
		{
		}
	}
	else if(KeyDataR>3350 && KeyDataR<3450 && keyFlagR)
	{
		if(!timeDelayFlag)
			timeDelayFlag = 10;
		
		if(KeyDataR>3350 && KeyDataR<3450 && keyFlagR && timeDelayFlag == 1)
		{

		}
	}
	else if(KeyDataR>4050)
	{
		keyFlagR = 1;
	}
	
	
}
void g_v_AdcCalculate(void)
{
	g_t_Rc_D_CMS.THROTTLE = (g_u16a7_ADCValue_CMS[1] * 1000.0 / 2048 +1000);     //THR
	if(g_t_Rc_D_CMS.THROTTLE > 4000)
	{
		g_t_Rc_D_CMS.THROTTLE = 4000;
	}
	if(g_t_Rc_D_CMS.THROTTLE < 1000)
	{
		g_t_Rc_D_CMS.THROTTLE = 1000;
	}
	g_t_Rc_D_CMS.THROTTLE = 4000-g_t_Rc_D_CMS.THROTTLE+1000 ;
	
	g_t_Rc_D_CMS.YAW = g_u16a7_ADCValue_CMS[0] * 1000.0 / 2048 +1000;							//YAW
	if(g_t_Rc_D_CMS.YAW > 2000)
	{
		g_t_Rc_D_CMS.YAW = 2000;
	}
	if(g_t_Rc_D_CMS.YAW < 1000)
	{
		g_t_Rc_D_CMS.YAW = 1000;
	}
	g_t_Rc_D_CMS.YAW=2000-g_t_Rc_D_CMS.YAW+1000-10;

	g_t_Rc_D_CMS.ROLL = g_u16a7_ADCValue_CMS[3] * 1000.0 / 2048 +1000+30;						//ROLL
	if(g_t_Rc_D_CMS.ROLL > 2000)
	{
		g_t_Rc_D_CMS.ROLL = 2000;
	}
	if(g_t_Rc_D_CMS.ROLL < 1000)
	{
		g_t_Rc_D_CMS.ROLL = 1000;
	}	
	g_t_Rc_D_CMS.ROLL=2000-g_t_Rc_D_CMS.ROLL+1000;
	
	g_t_Rc_D_CMS.PITCH = (g_u16a7_ADCValue_CMS[2] * 1000.0 / 2048 +1000);						//PITCH
	if(g_t_Rc_D_CMS.PITCH > 2000)
	{
		g_t_Rc_D_CMS.PITCH = 2000;
	}
	if(g_t_Rc_D_CMS.PITCH < 1000)
	{
		g_t_Rc_D_CMS.PITCH = 1000;
	}	
	g_t_Rc_D_CMS.PITCH=2000-g_t_Rc_D_CMS.PITCH+1000-50;
	
}





