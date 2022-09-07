#ifndef __XUNJI_H
#define __XUNJI_H	 
#include "sys.h"
#include "stm32f10x.h"

#define Sensor1_Status 	PCin(1)//��1
#define Sensor2_Status 	PCin(2)//��2
#define Sensor3_Status 	PCin(3)//��
#define Sensor4_Status	PCin(4)//��1
#define Sensor5_Status 	PCin(5)//��2


// ����Ѱ������������ƣ�, ����������·ѭ��
typedef enum
{
	// δ���ֺ��ߣ����ˣ�, 00000
	Back_Status 	 = 00000,
	// �м䷢�ֺ��� , 01110/00100/01100/00110
	Center_Status_1  = 01110,
	Center_Status_2  = 00100,
	Center_Status_3  = 01100,
	Center_Status_4  = 00110,
	// ��෢�ֺ���
	Left_Status_1    = 11000,
	Left_Status_2    = 01000,
	// ���ֺ��ߴ�ת
	BigLeft_Status   = 10000,
	// �Ҳ෢�ֺ���
	Right_Status_1   = 00011,
	Right_Status_2   = 00010,
	// �ҷ��ֺ��ߴ�ת 
	BigRight_Status  = 00001,
	// ȫ�����ֺ���
	Line_Status      = 11111
}xunji_status_enum;


/* ѭ��GPIO��ʼ�� */
void XUNJI_Init(void);
/* ѭ���жϺ��� */
xunji_status_enum XUNJI_detect_line(void);

#endif



