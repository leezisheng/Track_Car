#include "sys.h"
#include "hc05.h"

//数组用来存储接收到的数据，而USART3_REC_LEN为最多能接收的字节限度
u8 USART3_RX_BUF[USART3_REC_LEN]; 
//接收状态标记	 0-14位为接收字节数，15位接收完成标志位
u16 USART3_RX_STA=0;         		

void usart3_init(u32 bound)
{ 
	  GPIO_InitTypeDef GPIO_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructurea;
	  USART_InitTypeDef USART_InitStruct;
	 
	  //使能串口3
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	  //使能GPIOB
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	  //串口3复位 不是必要的一步
	  USART_DeInit(USART3);
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	   //PB10设置为复用推挽输出
	  GPIO_Init(GPIOB,&GPIO_InitStructure);   
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	  //PB11设置为浮空输入
	  GPIO_Init(GPIOB,&GPIO_InitStructure);   
  
	  NVIC_InitStructurea.NVIC_IRQChannel=USART3_IRQn;
	  NVIC_InitStructurea.NVIC_IRQChannelCmd=ENABLE;
	  NVIC_InitStructurea.NVIC_IRQChannelPreemptionPriority=2;
	  NVIC_InitStructurea.NVIC_IRQChannelSubPriority=2;
	  //串口3中断的设置
	  NVIC_Init(&NVIC_InitStructurea);         
	  //串口3中断使能和中断类型设置
	  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
	  //串口波特率
	  USART_InitStruct.USART_BaudRate=bound;
	  //无硬件数据流控制
	  USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	  //收发模式
	  USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Rx;
	  //无奇偶校验位
	  USART_InitStruct.USART_Parity=USART_Parity_No;
	  //一个停止位
	  USART_InitStruct.USART_StopBits=USART_StopBits_1;
	  //字长为8位数据格式
	  USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	  //串口3的一些参数设置
	  USART_Init(USART3,&USART_InitStruct);                 
	 
	  //串口3使能
	  USART_Cmd(USART3,ENABLE);  
}
void USART3_IRQHandler()
{ 
	 //暂时缓存接收的数据
	 u8 res;
	
	 //判断是否为串口3接收中断
	 if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
	 {
		//接收到数据放进res
		res=USART_ReceiveData(USART3);
		//数据放进数组中，则可以用到main函数中了
		USART3_RX_BUF[USART3_RX_STA&0x7FFF]=res;
		//字节长度++
		USART3_RX_STA++;
		//接收数据错误,重新开始接收	+
		if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;
		//串口3接收完成
		USART3_RX_STA|=0x8000;
		//清除接收中断标志
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	  }
}


	