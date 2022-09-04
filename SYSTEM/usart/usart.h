#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "delay.h"
#include "misc.h"

//定义最大接收字节数 200
#define USART_REC_LEN  			200  	
//定义USART1最大接收字节数
#define USART1_REC_LEN  		200  	
//定义USART2最大接收字节数
#define USART2_REC_LEN  		200  	


#define UART2_BUFFER_SIZE 		256 

//使能（1）/禁止（0）串口1接收
#define EN_USART1_RX 			1		
//使能（1）/禁止（0）串口1接收
#define EN_USART2_RX 			1		

//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8  USART_RX_BUF[USART_REC_LEN]; 
//接收状态标记	
extern u16 USART_RX_STA;         		

//串口1初始化并启动
void USART1_Init(u32 bound);
//串口2初始化并启动
void USART2_Init(u32 bound);

//串口1的专用printf函数
void USART1_printf(char* fmt,...);
//串口2的专用printf函数
void USART2_printf(char* fmt,...); 


void USART2_Send_Data(u8 *buf,u8 len);
void TR_Receive(void);
uint8_t uart2Read(void);
uint16_t uart2Available(void);
void USART2_IRQHandler(void);

void UART1_Put_Char(unsigned char DataToSend);
void UART1_Put_String(unsigned char *Str);

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
#endif


