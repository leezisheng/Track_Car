#include "beep.h" 
#include "delay.h"

//初始化PB8为输出口.并使能这个口的时钟		    
//蜂鸣器初始化
void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//使能GPIOB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	

	 //BEEP-->PB.8 端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				
	//推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	//速度为50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	//根据参数初始化GPIOB.8
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 

	//输出0，关闭蜂鸣器输出
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}

// 控制蜂鸣器响，可以调节次数和频率
void BEEP_ON(uint8_t times, uint8_t ratio)
{
	for(uint8_t count=0;count<times;count++)
	{
		delay_ms(5);
		//输出1，开启蜂鸣器输出
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		delay_ms(ratio);
		//输出0，关闭蜂鸣器输出
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
	}
}



