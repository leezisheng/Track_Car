#include "delay.h"

//�밴RCC�����õ�AHBʱ��Ƶ����д�������λMHz��
#define AHB_INPUT  72 

// ��ȷ��us������ʱ
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	//ʱ�����	
	SysTick->LOAD=nus*9; 	
	//��ռ�����	
	SysTick->VAL=0x00;    
	//��ʼ����	
	SysTick->CTRL=0x01 ;	
	
	do
	{
		temp=SysTick->CTRL;
	}
	//�ȴ�ʱ�䵽�� 
	while((temp&0x01)&&!(temp&(1<<16)));		  
	
	//�رռ�����
	SysTick->CTRL=0;	
	 //��ռ�����
	SysTick->VAL =0X00;      					 
}


//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		 
	
	//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->LOAD=(u32)nms*9000;	
	//��ռ�����
	SysTick->VAL =0x00;
	//��ʼ���� 
	SysTick->CTRL=0x01;	 
	do
	{
		temp=SysTick->CTRL;
	}
	//�ȴ�ʱ�䵽��
	while((temp&0x01)&&!(temp&(1<<16)));	
	
	//�رռ�����
	SysTick->CTRL&=0;
	//��ռ�����	  
	SysTick->VAL =0X00;       						    
} 

// ����ȷ��s������ʱ
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

// ����ȷ����ʱ
 void Delay(u16 count)
 {
   u16 i=0;
   for(;i<count;i++);
 }

