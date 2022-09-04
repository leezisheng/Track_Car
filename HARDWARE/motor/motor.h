#ifndef  __MOTOR_H
#define  __MOTOR_H
#include "stm32f10x.h"
#include "pwm.h"
#include "sys.h"

/* 设置GPIOA1接口输出高电平*/
#define IN1_up GPIO_SetBits(GPIOA, GPIO_Pin_1)
/* 设置GPIOA1接口输出低电平*/
#define IN1_down  GPIO_ResetBits(GPIOA,GPIO_Pin_1)

/* 设置GPIOA2接口输出高电平*/
#define IN2_up GPIO_SetBits(GPIOA, GPIO_Pin_2)
/* 设置GPIOA2接口输出低电平*/
#define IN2_down  GPIO_ResetBits(GPIOA,GPIO_Pin_2)

/* 设置GPIOA3接口输出高电平*/
#define IN3_up GPIO_SetBits(GPIOA, GPIO_Pin_3)
/* 设置GPIOA3接口输出低电平*/
#define IN3_down  GPIO_ResetBits(GPIOA,GPIO_Pin_3)

/* 设置GPIOA4接口输出高电平*/
#define IN4_up GPIO_SetBits(GPIOA, GPIO_Pin_4)
/* 设置GPIOA4接口输出低电平*/
#define IN4_down  GPIO_ResetBits(GPIOA,GPIO_Pin_4)

void IO_A_Init(void);
void CarGo(void);
void CarStop(void);
void CarBack(void);
void CarLeft(void);
void CarBigLeft(void);  //大右转
void CarRight(void);
void CarBigRight(void);   //大左转


#endif
