#include "motor.h"

void IO_A_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
    //ѡ��˿ںţ�0~15��all��   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   
	//ѡ��IO�ӿڹ�����ʽ 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	//����IO�ӿ��ٶȣ�2/10/50MHz�� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);		 
}

/* ǰ������ */ 
void CarGo(void)
{
	/* ���õ������ת���� */
	IN1_up;
	IN2_down;
	IN3_up;
	IN4_down;
	
	/* ����PWMռ�ձȣ������ٶ� */
	TIM_SetCompare3(TIM3,500);
}

/* ֹͣ���� */ 
void CarStop(void)
{
	IN1_up;
	IN2_up;
	IN3_up;
	IN4_up;
}

/* ���˺��� */ 
void CarBack(void)
{
	/* ���õ������ת���� */
	IN2_up;
	IN1_down;
	IN4_up;
	IN3_down;
	
	/* ����PWMռ�ձȣ������ٶ� */
	TIM_SetCompare3(TIM3,500);
}

/* ��ת���� */ 
void CarLeft(void)
{
	/* ���õ������ת���� */
	IN2_up;
	IN1_down;
	IN3_up;
	IN4_down;
	
	/* ����PWMռ�ձȣ������ٶ� */
	TIM_SetCompare3(TIM3,500);
}

void CarBigLeft(void)
{
	/* ���õ������ת���� */
    IN2_up;
	IN1_down;
	IN3_up;
	IN4_down;
	
	/* ����PWMռ�ձȣ������ٶ� */
	TIM_SetCompare3(TIM3,800);
}

/* ��ת���� */ 
void CarRight(void)
{
	/* ���õ������ת���� */
	IN1_up;
	IN2_down;
	IN4_up;
	IN3_down;
	
	/* ����PWMռ�ձȣ������ٶ� */
	TIM_SetCompare3(TIM3,500);
}

void CarBigRight(void)
{
	/* ���õ������ת���� */
    IN1_up;
	IN2_down;
	IN4_up;
	IN3_down;
	
	/* ����PWMռ�ձȣ������ٶ� */
	TIM_SetCompare3(TIM3,800);
}

