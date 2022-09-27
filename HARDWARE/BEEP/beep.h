#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"
 
// 蜂鸣器端口定义
#define BEEP PBout(8)		   

// 初始化
void BEEP_Init(void);	
// 控制蜂鸣器响，可以调节次数和频率
void BEEP_ON(uint8_t times, uint8_t ratio);	
		 				    
#endif

