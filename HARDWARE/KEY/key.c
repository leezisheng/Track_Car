#include "key.h"
 	    
//������ʼ������ 
//PA15��PC5 ���ó�����



////����������

void KEYPAD4x4_Init(void){ //΢�����صĽӿڳ�ʼ��
	
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP��
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);// �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��
  GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);  //����PD0��PD1�˿���ΪGPIO
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//JTAG-DP ʧ�� + SW-DP ʹ��

  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;//PD 0 2 4 6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOd
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD

				
}

void KEYPAD4x4_Init2(void){ //΢�����صĽӿڳ�ʼ��2������IO������ʽ��ת��
	  GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
  	GPIO_Init(GPIOD,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; //ѡ��˿ںţ�0~15��all��                        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //ѡ��IO�ӿڹ�����ʽ //��������  
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��     
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

u8 KEYPAD4x4_Read (void){//���̴�����
	u8 a=0,b=0;//�������
	KEYPAD4x4_Init();//��ʼ��IO
	GPIO_ResetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7);
	GPIO_SetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6);
	if(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) ||  	//��Ѱ���̿ڵ�ֵ�Ƿ�仯
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6))
	{
		delay_ms (20);//��ʱ20����
		if(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) ||  	//��Ѱ���̿ڵ�ֵ�Ƿ�仯
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) || 
		!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6))
		{
	    a = Read_GPIOs();//��ֵ����Ĵ���a
		}
		KEYPAD4x4_Init2();//IO������ʽ��ת
		GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7);
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6);
		delay_ms(10);//��Ҫ����ʱ���Ա�֤��ȡ�ĵ�ƽ�ȶ�
		b =Read_GPIOs();//���ڶ���ȡ��ֵ����Ĵ���b
		a = a|b;//�������������
		switch(a){//�Ա�����ֵ
			case 0xee: b = 1; break;//�Աȵõ��ļ�ֵ��bһ��Ӧ������
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
			default: b = 0; break;//��ֵ������
		}
		while(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1) ||  	//�ȴ������ſ�
			!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) || 
			!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) || 
			!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7));
		delay_ms (20);//��ʱ20����
	}
return b;//��b��Ϊ����ֵ
} 

