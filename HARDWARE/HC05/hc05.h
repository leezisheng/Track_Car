#ifndef HC05_H_
#define HC05_H_
#include "sys.h"
#include "stdio.h"	

//定义最大接收字节数 200
#define USART3_REC_LEN  200  	

//接收缓冲,最大USART_REC_LEN个字节
extern u8  USART3_RX_BUF[USART3_REC_LEN];
//接收状态标记	 0-14位为接收字节数，15位接收完成标志位
extern u16 USART3_RX_STA;         

void usart3_init(u32 bound);

#endif

