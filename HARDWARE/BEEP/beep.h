#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"
 
// �������˿ڶ���
#define BEEP PBout(8)		   

// ��ʼ��
void BEEP_Init(void);	
// ���Ʒ������죬���Ե��ڴ�����Ƶ��
void BEEP_ON(uint8_t times, uint8_t ratio);	
		 				    
#endif

