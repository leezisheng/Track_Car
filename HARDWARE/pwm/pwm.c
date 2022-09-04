#include "pwm.h"

//TIM3 PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ�� pulse����ռ�ձ�
void PWM_Init(u16 arr,u16 psc)
{ 
     
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3�����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOBʱ��(LED��PB0����)

	
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;     // TIM_CH3\ TIM_CH4
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    // ��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;    //�����������ٶ�
    GPIO_Init(GPIOB,&GPIO_InitStrue);                //GPIO�˿ڳ�ʼ������

	// GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //ӳ�䣬��ӳ��ֻ����64��100��144�ŵ�Ƭ��
	// ��û����ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH 4�ֱ��ӦPB4��PB5,PB0,PB1 (GPIO_PartialRemap_TIM3)
	// ����ȫ��ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPC6��PC7,PC8,PC9 (GPIO_FullRemap_TIM3) 
	TIM_DeInit( TIM3 );
    TIM_TimeBaseInitStrue.TIM_Period=arr;    //�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;    //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;        //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        //TIM3��ʼ������(����PWM������)
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC3Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��3 PWM ģʽ����
		
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���
    	
	TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        // PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;// ���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;// ���ʹ��
    TIM_OC4Init(TIM3,&TIM_OCInitStrue);        //TIM3��ͨ��4 PWM ģʽ����

    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���
		

    TIM_ARRPreloadConfig( TIM3, ENABLE );
	//ʹ��TIM3
    TIM_Cmd(TIM3,ENABLE);        
}
