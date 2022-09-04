#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "delay.h"
#include "misc.h"

//�����������ֽ��� 200
#define USART_REC_LEN  			200  	
//����USART1�������ֽ���
#define USART1_REC_LEN  		200  	
//����USART2�������ֽ���
#define USART2_REC_LEN  		200  	


#define UART2_BUFFER_SIZE 		256 

//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART1_RX 			1		
//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1		

//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART_RX_BUF[USART_REC_LEN]; 
//����״̬���	
extern u16 USART_RX_STA;         		

//����1��ʼ��������
void USART1_Init(u32 bound);
//����2��ʼ��������
void USART2_Init(u32 bound);

//����1��ר��printf����
void USART1_printf(char* fmt,...);
//����2��ר��printf����
void USART2_printf(char* fmt,...); 


void USART2_Send_Data(u8 *buf,u8 len);
void TR_Receive(void);
uint8_t uart2Read(void);
uint16_t uart2Available(void);
void USART2_IRQHandler(void);

void UART1_Put_Char(unsigned char DataToSend);
void UART1_Put_String(unsigned char *Str);

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


