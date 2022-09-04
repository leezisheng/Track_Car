#include "xunji.h"
#include "stm32f10x.h"  


/* 循迹GPIO初始化 */
void XUNJI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //定义GPIO_InitTypeDef结构体

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);  //开启引脚时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			// 复用时钟使能
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;  //上拉输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//----------------------------------------------------------------------------------------------


// 黑线寻迹函数
// S_Trail_Input的低三位分别对应[PB5、PB4、PB3，PB1]的状态值
// 未碰到黑线(接收到红外光)：对应状态 = 0
// 碰到黑线(未接收到红外光)：对应状态 = 1
//----------------------------------------------------
xunji_status_enum XUNJI_detect_line(void)
{
	static xunji_status_enum temp_status;
	
	temp_status = (xunji_status_enum)(Sensor1_Status*10000+Sensor2_Status*1000+Sensor3_Status*100+Sensor4_Status*10+Sensor5_Status);
	
	return temp_status;
}


