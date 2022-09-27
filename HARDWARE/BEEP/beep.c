#include "beep.h" 
#include "delay.h"

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//ʹ��GPIOB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	

	 //BEEP-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				
	//�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	//�ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	//���ݲ�����ʼ��GPIOB.8
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 

	//���0���رշ��������
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}

// ���Ʒ������죬���Ե��ڴ�����Ƶ��
void BEEP_ON(uint8_t times, uint8_t ratio)
{
	for(uint8_t count=0;count<times;count++)
	{
		delay_ms(5);
		//���1���������������
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		delay_ms(ratio);
		//���0���رշ��������
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
	}
}



