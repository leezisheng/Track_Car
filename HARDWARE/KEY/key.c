#include "key.h"
 	    
//按键初始化函数 
//PA15和PC5 设置成输入



////按键处理函数

void KEYPAD4x4_Init(void){ //微动开关的接口初始化
	
	GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);// 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);// 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
  GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);  //启用PD0和PD1端口作为GPIO
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//JTAG-DP 失能 + SW-DP 使能

  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;//PD 0 2 4 6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOd
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD

				
}

void KEYPAD4x4_Init2(void){ //微动开关的接口初始化2（用于IO工作方式反转）
	  GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7; //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻       
  	GPIO_Init(GPIOD,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; //选择端口号（0~15或all）                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式 //上拉电阻  
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）     
	  GPIO_Init(GPIOD,&GPIO_InitStructure);
				
}
int Read_GPIOs(void)
{
	int gpio=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)*128+
		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)*64+
	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)*32+
	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)*16+
	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)*8+
	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)*4+
	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)*2+
	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
	return gpio&0xff;
}

u8 KEYPAD4x4_Read (void){//键盘处理函数
	u8 a=0,b=0;//定义变量
	KEYPAD4x4_Init();//初始化IO
	GPIO_ResetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7);
	GPIO_SetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6);
	if(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) ||  	//查寻键盘口的值是否变化
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6))
	{
		delay_ms (20);//延时20毫秒
		if(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) ||  	//查寻键盘口的值是否变化
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6))
		{
	    a = Read_GPIOs();//键值放入寄存器a
		}
		KEYPAD4x4_Init2();//IO工作方式反转
		GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7);
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6);
		delay_ms(10);//必要的延时，以保证读取的电平稳定
		b =Read_GPIOs();//将第二次取得值放入寄存器b
		a = a|b;//将两个数据相或
		switch(a){//对比数据值
			case 0xee: b = 1; break;//对比得到的键值给b一个应用数据
			case 0xed: b = 5; break;
			case 0xeb: b = 9; break;
			case 0xe7: b = 13; break;
			case 0xde: b = 2; break;
			case 0xdd: b = 6; break;
			case 0xdb: b = 10; break;
			case 0xd7: b = 14; break;
			case 0xbe: b = 3; break;
			case 0xbd: b = 7; break;
			case 0xbb: b = 11; break;
			case 0xb7: b = 15; break;
			case 0x7e: b = 4; break;
			case 0x7d: b = 8; break;
			case 0x7b: b = 12; break;
			case 0x77: b = 16; break;
			default: b = 0; break;//键值错误处理
		}
		while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1) ||  	//等待按键放开
			!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) || 
			!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) || 
			!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7));
		delay_ms (20);//延时20毫秒
	}
return b;//将b作为返回值
} 

