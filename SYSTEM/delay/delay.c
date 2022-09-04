#include "delay.h"

//请按RCC中设置的AHB时钟频率填写到这里（单位MHz）
#define AHB_INPUT  72 

// 精确的us级别延时
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	//时间加载	
	SysTick->LOAD=nus*9; 	
	//清空计数器	
	SysTick->VAL=0x00;    
	//开始倒数	
	SysTick->CTRL=0x01 ;	
	
	do
	{
		temp=SysTick->CTRL;
	}
	//等待时间到达 
	while((temp&0x01)&&!(temp&(1<<16)));		  
	
	//关闭计数器
	SysTick->CTRL=0;	
	 //清空计数器
	SysTick->VAL =0X00;      					 
}


//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		 
	
	//时间加载(SysTick->LOAD为24bit)
	SysTick->LOAD=(u32)nms*9000;	
	//清空计数器
	SysTick->VAL =0x00;
	//开始倒数 
	SysTick->CTRL=0x01;	 
	do
	{
		temp=SysTick->CTRL;
	}
	//等待时间到达
	while((temp&0x01)&&!(temp&(1<<16)));	
	
	//关闭计数器
	SysTick->CTRL&=0;
	//清空计数器	  
	SysTick->VAL =0X00;       						    
} 

// 不精确的s级别延时
void delay_s(u16 s)
{	 		  
	while(s != 0 )
	{
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		s--;
	}
} 

// 不精确的延时
 void Delay(u16 count)
 {
   u16 i=0;
   for(;i<count;i++);
 }

