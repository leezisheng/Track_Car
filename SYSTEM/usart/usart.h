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

//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART1_RX 			1		

//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART_RX_BUF[USART_REC_LEN]; 
//����״̬���	
extern u16 USART_RX_STA;         		

//����1��ʼ��������
void USART1_Init(u32 bound);
//����1��ר��printf����
void USART1_printf(char* fmt,...);
void UART1_Put_Char(unsigned char DataToSend);
void UART1_Put_String(unsigned char *Str);

#endif


