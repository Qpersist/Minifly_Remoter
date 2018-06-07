#include "SPI_IO.h"


void Spi1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
unsigned char Spi_RW(unsigned char uchar)
{
	unsigned char bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++)  
   	{
		SPI_MOSI(uchar & 0x80);         
		uchar = (uchar << 1);          
		SPI_SCK(1);                      
		uchar |= SPI_MISO_IN;       		  
		SPI_SCK(0);            		    
   	}
    return(uchar);           		   
}
