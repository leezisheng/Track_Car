#include "motor.h"

void IO_A_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
    //选择端口号（0~15或all）   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   
	//选择IO接口工作方式 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	//设置IO接口速度（2/10/50MHz） 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);		 
}

/* 前进函数 */ 
void CarGo(void)
{
	/* 设置电机正反转方向 */
	IN1_up;
	IN2_down;
	IN3_up;
	IN4_down;
	
	/* 设置PWM占空比：控制速度 */
	TIM_SetCompare3(TIM3,500);
}

/* 停止函数 */ 
void CarStop(void)
{
	IN1_up;
	IN2_up;
	IN3_up;
	IN4_up;
}

/* 后退函数 */ 
void CarBack(void)
{
	/* 设置电机正反转方向 */
	IN2_up;
	IN1_down;
	IN4_up;
	IN3_down;
	
	/* 设置PWM占空比：控制速度 */
	TIM_SetCompare3(TIM3,500);
}

/* 左转函数 */ 
void CarLeft(void)
{
	/* 设置电机正反转方向 */
	IN2_up;
	IN1_down;
	IN3_up;
	IN4_down;
	
	/* 设置PWM占空比：控制速度 */
	TIM_SetCompare3(TIM3,500);
}

void CarBigLeft(void)
{
	/* 设置电机正反转方向 */
    IN2_up;
	IN1_down;
	IN3_up;
	IN4_down;
	
	/* 设置PWM占空比：控制速度 */
	TIM_SetCompare3(TIM3,800);
}

/* 右转函数 */ 
void CarRight(void)
{
	/* 设置电机正反转方向 */
	IN1_up;
	IN2_down;
	IN4_up;
	IN3_down;
	
	/* 设置PWM占空比：控制速度 */
	TIM_SetCompare3(TIM3,500);
}

void CarBigRight(void)
{
	/* 设置电机正反转方向 */
    IN1_up;
	IN2_down;
	IN4_up;
	IN3_down;
	
	/* 设置PWM占空比：控制速度 */
	TIM_SetCompare3(TIM3,800);
}

