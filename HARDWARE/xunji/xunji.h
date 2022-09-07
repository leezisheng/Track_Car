#ifndef __XUNJI_H
#define __XUNJI_H	 
#include "sys.h"
#include "stm32f10x.h"

#define Sensor1_Status 	PCin(1)//左1
#define Sensor2_Status 	PCin(2)//左2
#define Sensor3_Status 	PCin(3)//中
#define Sensor4_Status	PCin(4)//右1
#define Sensor5_Status 	PCin(5)//右2


// 黑线寻迹情况（二进制）, 仅适用于五路循迹
typedef enum
{
	// 未发现黑线（后退）, 00000
	Back_Status 	 = 00000,
	// 中间发现黑线 , 01110/00100/01100/00110
	Center_Status_1  = 01110,
	Center_Status_2  = 00100,
	Center_Status_3  = 01100,
	Center_Status_4  = 00110,
	// 左侧发现黑线
	Left_Status_1    = 11000,
	Left_Status_2    = 01000,
	// 左发现黑线大转
	BigLeft_Status   = 10000,
	// 右侧发现黑线
	Right_Status_1   = 00011,
	Right_Status_2   = 00010,
	// 右发现黑线大转 
	BigRight_Status  = 00001,
	// 全部发现黑线
	Line_Status      = 11111
}xunji_status_enum;


/* 循迹GPIO初始化 */
void XUNJI_Init(void);
/* 循迹判断函数 */
xunji_status_enum XUNJI_detect_line(void);

#endif



