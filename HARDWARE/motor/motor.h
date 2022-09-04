#ifndef  __MOTOR_H
#define  __MOTOR_H
#include "stm32f10x.h"
#include "pwm.h"
#include "sys.h"

/* ����GPIOA1�ӿ�����ߵ�ƽ*/
#define IN1_up GPIO_SetBits(GPIOA, GPIO_Pin_1)
/* ����GPIOA1�ӿ�����͵�ƽ*/
#define IN1_down  GPIO_ResetBits(GPIOA,GPIO_Pin_1)

/* ����GPIOA2�ӿ�����ߵ�ƽ*/
#define IN2_up GPIO_SetBits(GPIOA, GPIO_Pin_2)
/* ����GPIOA2�ӿ�����͵�ƽ*/
#define IN2_down  GPIO_ResetBits(GPIOA,GPIO_Pin_2)

/* ����GPIOA3�ӿ�����ߵ�ƽ*/
#define IN3_up GPIO_SetBits(GPIOA, GPIO_Pin_3)
/* ����GPIOA3�ӿ�����͵�ƽ*/
#define IN3_down  GPIO_ResetBits(GPIOA,GPIO_Pin_3)

/* ����GPIOA4�ӿ�����ߵ�ƽ*/
#define IN4_up GPIO_SetBits(GPIOA, GPIO_Pin_4)
/* ����GPIOA4�ӿ�����͵�ƽ*/
#define IN4_down  GPIO_ResetBits(GPIOA,GPIO_Pin_4)

void IO_A_Init(void);
void CarGo(void);
void CarStop(void);
void CarBack(void);
void CarLeft(void);
void CarBigLeft(void);  //����ת
void CarRight(void);
void CarBigRight(void);   //����ת


#endif
