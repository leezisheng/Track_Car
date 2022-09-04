/*
	ʹ�ÿ��������ţ�
		1. LED��PB5��PE5
		2. ֱ��������򼰱��٣�
			��1��PWM �� PB0��PB1
			��2������ �� PA1 PA2 PA3 PA4 GPIO
	
	ʹ��оƬ���輰�������
		1. LED ��GPIO
		2. ��� �� 
			��1�� �� PA1 PA2 PA3 PA4 ��GPIO
			��2�� �� TIM3 CH3 CH4�� arr = 999 ,psc = 0
*/
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "i2c.h"
#include "sys.h"
#include "pwm.h"
#include "motor.h"
#include "xunji.h"


/* -------------------------------�ⲿ����-------------------------------------- */





/* -------------------------------�ⲿ����-------------------------------------- */



/* -------------------------------��������-------------------------------------- */

// �弶�����ʼ��
static void BSP_Init(void);
// ������ʾ����
static void Error_Show(void);

/* -------------------------------ȫ�ֱ���-------------------------------------- */
// ѭ��״̬
xunji_status_enum car_status;


int main(void)
{	
	// ϵͳʱ�ӳ�ʼ��
	RCC_Configuration(); 
	// ����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 
 	
	// �����ʼ��
	BSP_Init();
	
	while(1)
	{
		car_status = XUNJI_detect_line();
    }
}

// �弶�����ʼ��
static void BSP_Init(void)
{
	// �����ʼ����ʼ
	LED_PB5 = 1;
	LED_PE5 = 1;
	
	
	// LED�˿ڳ�ʼ��
	LED_Init();			
	// PWM��ʼ��
	PWM_Init(999,0);
	// ���IO�ڳ�ʼ��
	IO_A_Init();
	// ѭ��GPIO��ʼ��
	XUNJI_Init();
	
	
	// 	�����ϵ���ʱ
	delay_ms(500);
	
	// �����ʼ������
	LED_PB5 = 0;
	LED_PE5 = 0;
}

// ������ʾ����
static void Error_Show(void)
{
	while(1)
	{
		LED_PB5 = 1;
		delay_ms(50);
		LED_PB5 = 0;
	}
}
 

