/*
	使用开发板引脚：
		1. LED：PB5和PE5
		2. 直流电机变向及变速：
			（1）PWM ： PB0和PB1
			（2）变相 ： PA1 PA2 PA3 PA4 GPIO
		3. OLED：IIC-GPIOB GPIO_Pin_6、GPIOB GPIO_Pin_7
	
	使用芯片外设及其参数：
		1. LED ：GPIO
		2. 电机 ： 
			（1） （ PA1 PA2 PA3 PA4 ）GPIO
			（2） （ TIM3 CH3 CH4） arr = 999 ,psc = 0
		3. OLED：IIC1-GPIOB GPIO_Pin_6、GPIOB GPIO_Pin_7
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
 
/* -------------------------------外部变量-------------------------------------- */

//接收缓冲,最大USART_REC_LEN个字节
extern u8  USART3_RX_BUF[USART3_REC_LEN];
//接收状态标记	 0-14位为接收字节数，15位接收完成标志位
extern u16 USART3_RX_STA;     

/* -------------------------------外部函数-------------------------------------- */

/* -------------------------------函数声明-------------------------------------- */

// 板级外设初始化
static void BSP_Init(void);
// 错误提示函数
static void Error_Show(void);
// 工作模式1：循迹模式
void work_mode_xunji(void);
// 工作模式1：蓝牙模式
void work_mode_bluetooth(void);


/* -------------------------------全局变量-------------------------------------- */

// 循迹状态
xunji_status_enum car_status;


int main(void)
{	
	// 系统时钟初始化
	RCC_Configuration(); 
	// 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 
 	
	// 外设初始化
	BSP_Init();
	
	while(1)
	{
	
		
    }
}

// 板级外设初始化
static void BSP_Init(void)
{
	// 外设初始化开始
	LED_PB5 = 1;
	LED_PE5 = 1;
	
	// LED端口初始化
	LED_Init();			
	// PWM初始化
	PWM_Init(999,0);
	// 电机IO口初始化
	IO_A_Init();
	// 循迹GPIO初始化
	XUNJI_Init();
	// 蓝牙初始化，注意手机与单片机的蓝牙连接波特率是要9600
	usart3_init(9600);

	
//	// IIC初始化
//	I2C_Configuration();
//	// OLED初始化
//	OLED0561_Init();
	
	
	// 	器件上电延时
	delay_ms(500);
	
	// 外设初始化结束
	LED_PB5 = 0;
	LED_PE5 = 0;
}

// 错误提示函数
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

// 工作模式1：循迹模式
void work_mode_xunji(void)
{
	car_status = XUNJI_detect_line();
	
	switch(car_status)
	{
		// 未发现黑线（后退）, 00000
		case Back_Status:
			CarBack();
			return;
		
		// 中间发现黑线 , 01110/00100/01100/00110
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
		
		// 左侧发现黑线
		case Left_Status_1:
			CarLeft();
			return;
		case Left_Status_2:
			CarLeft();
			return;
		
		// 左发现黑线大转
		case BigLeft_Status:
			CarBigLeft();
			return;
		
		// 右侧发现黑线
		case Right_Status_1:
			CarRight();
		    return;
		case Right_Status_2:
			CarRight();
		    return;
		
		// 右发现黑线大转 
		case BigRight_Status:
			CarBigRight();
			return;
		
		// 全部发现黑线
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
		 // 停车
		if(USART3_RX_BUF[0]=='0')
		 {
			CarStop();
		 }
		 // 亮1号绿灯
		if(USART3_RX_BUF[0]=='1')
		 {
			LED_PE5 = 1;	 
		 }
		 // 亮2号绿灯
		if(USART3_RX_BUF[0]=='2')
		 {
			LED_PB5 = 1;	
		 }
		 // 亮2个绿灯
		if(USART3_RX_BUF[0]=='3')
		 {
			LED_PB5 = 1;
			LED_PE5 = 1;
		 }
		 // 关2个绿灯
		if(USART3_RX_BUF[0]=='4')
		 {
			LED_PB5 = 0;
			LED_PE5 = 0;		 
		 }
		 // 左转
		if(USART3_RX_BUF[0]=='5')
		 {
			CarLeft();		  
		 }
		 // 右转
		if(USART3_RX_BUF[0]=='6')
		 {
			CarRight();		  
		 }
		 // 前进
		if(USART3_RX_BUF[0]=='7')
		 {
			CarGo();		  
		 }	
		 // 后退
		 if(USART3_RX_BUF[0]=='8')
		 {
			CarBack();
		 }
	 }
}
