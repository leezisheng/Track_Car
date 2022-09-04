#include "xunji.h"
#include "stm32f10x.h"  


/* ѭ��GPIO��ʼ�� */
void XUNJI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //����GPIO_InitTypeDef�ṹ��

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);  //��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			// ����ʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;  //�������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//----------------------------------------------------------------------------------------------


// ����Ѱ������
// S_Trail_Input�ĵ���λ�ֱ��Ӧ[PB5��PB4��PB3��PB1]��״ֵ̬
// δ��������(���յ������)����Ӧ״̬ = 0
// ��������(δ���յ������)����Ӧ״̬ = 1
//----------------------------------------------------
xunji_status_enum XUNJI_detect_line(void)
{
	static xunji_status_enum temp_status;
	
	temp_status = (xunji_status_enum)(Sensor1_Status*10000+Sensor2_Status*1000+Sensor3_Status*100+Sensor4_Status*10+Sensor5_Status);
	
	return temp_status;
}


