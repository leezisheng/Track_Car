/*
	ʹ�ÿ��������ţ�
		1. LED��PB5��PE5
		2. ֱ��������򼰱��٣�
			��1��PWM �� PB0��PB1
			��2������ �� PA1 PA2 PA3 PA4 GPIO
		3. OLED��IIC-GPIOB GPIO_Pin_6��GPIOB GPIO_Pin_7
	
	ʹ��оƬ���輰�������
		1. LED ��GPIO
		2. ��� �� 
			��1�� �� PA1 PA2 PA3 PA4 ��GPIO
			��2�� �� TIM3 CH3 CH4�� arr = 999 ,psc = 0
		3. OLED��IIC1-GPIOB GPIO_Pin_6��GPIOB GPIO_Pin_7
*/
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "i2c.h"
#include "sys.h"
#include "pwm.h"
#include "motor.h"
#include "xunji.h"
#include "oled0561.h"
#include "hc05.h"
 
/* -------------------------------�ⲿ����-------------------------------------- */

//���ջ���,���USART_REC_LEN���ֽ�
extern u8  USART3_RX_BUF[USART3_REC_LEN];
//����״̬���	 0-14λΪ�����ֽ�����15λ������ɱ�־λ
extern u16 USART3_RX_STA;     

/* -------------------------------�ⲿ����-------------------------------------- */

/* -------------------------------��������-------------------------------------- */

// �弶�����ʼ��
static void BSP_Init(void);
// ������ʾ����
static void Error_Show(void);
// ����ģʽ1��ѭ��ģʽ
void work_mode_xunji(void);
// ����ģʽ1������ģʽ
void work_mode_bluetooth(void);


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
	// ������ʼ����ע���ֻ��뵥Ƭ�����������Ӳ�������Ҫ9600
	usart3_init(9600);

	
//	// IIC��ʼ��
//	I2C_Configuration();
//	// OLED��ʼ��
//	OLED0561_Init();
	
	
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
		delay_ms(50);
		LED_PE5 = 0;
		delay_ms(50);
		LED_PE5 = 1;
	}
}

// ����ģʽ1��ѭ��ģʽ
void work_mode_xunji(void)
{
	car_status = XUNJI_detect_line();
	
	switch(car_status)
	{
		// δ���ֺ��ߣ����ˣ�, 00000
		case Back_Status:
			CarBack();
			return;
		
		// �м䷢�ֺ��� , 01110/00100/01100/00110
		case Center_Status_1:
			CarGo();
			return;
		case Center_Status_2:
			CarGo();
			return;
		case Center_Status_3:
			CarGo();
			return;
		case Center_Status_4:
			CarGo();
			return;
		
		// ��෢�ֺ���
		case Left_Status_1:
			CarLeft();
			return;
		case Left_Status_2:
			CarLeft();
			return;
		
		// ���ֺ��ߴ�ת
		case BigLeft_Status:
			CarBigLeft();
			return;
		
		// �Ҳ෢�ֺ���
		case Right_Status_1:
			CarRight();
		    return;
		case Right_Status_2:
			CarRight();
		    return;
		
		// �ҷ��ֺ��ߴ�ת 
		case BigRight_Status:
			CarBigRight();
			return;
		
		// ȫ�����ֺ���
		case Line_Status:
			CarStop();
			return;
		
		default:
			Error_Show();
			return;
	}
}

void work_mode_bluetooth(void)
{
   if(USART3_RX_STA&0x8000)
	 {
		 // ͣ��
		if(USART3_RX_BUF[0]=='0')
		 {
			CarStop();
		 }
		 // ��1���̵�
		if(USART3_RX_BUF[0]=='1')
		 {
			LED_PE5 = 1;	 
		 }
		 // ��2���̵�
		if(USART3_RX_BUF[0]=='2')
		 {
			LED_PB5 = 1;	
		 }
		 // ��2���̵�
		if(USART3_RX_BUF[0]=='3')
		 {
			LED_PB5 = 1;
			LED_PE5 = 1;
		 }
		 // ��2���̵�
		if(USART3_RX_BUF[0]=='4')
		 {
			LED_PB5 = 0;
			LED_PE5 = 0;		 
		 }
		 // ��ת
		if(USART3_RX_BUF[0]=='5')
		 {
			CarLeft();		  
		 }
		 // ��ת
		if(USART3_RX_BUF[0]=='6')
		 {
			CarRight();		  
		 }
		 // ǰ��
		if(USART3_RX_BUF[0]=='7')
		 {
			CarGo();		  
		 }	
		 // ����
		 if(USART3_RX_BUF[0]=='8')
		 {
			CarBack();
		 }
	 }
}
