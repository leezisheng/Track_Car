#include "sys.h"
#include "usart.h"	  
#include "string.h"

//usart2
volatile uint8_t rx2Buffer[UART2_BUFFER_SIZE]; 
volatile uint8_t rxBufferNum  = 0;
volatile uint8_t h_u32RecCnt = 0; 
static volatile uint8_t rx2BufferRTail  = 0;
u8 str1[9];

int x_axis=0;
int y_axis=0;

//usart1
volatile static unsigned char TxBuffer[256];
volatile static unsigned char TxCounter=0;
volatile static unsigned char count=0; 
extern void CopeSerial1Data(unsigned char ucData);

//usart3
unsigned char Re_buf[11],temp_buf[11],counter=0;
unsigned char sign,t,he;
unsigned char Temp[11];


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void UART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  
}

void UART1_Put_String(unsigned char *Str)
{
	while(*Str)
	{
		if(*Str=='\r')UART1_Put_Char(0x0d);
			else if(*Str=='\n')UART1_Put_Char(0x0a);
				else UART1_Put_Char(*Str);
		Str++;
	}
}

void USART1_printf (char *fmt, ...){ 
	char buffer[USART1_REC_LEN+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART1_REC_LEN+1, fmt, arg_ptr);
	
	while ((i < USART1_REC_LEN) && (i < strlen(buffer)))
	{
        USART_SendData(USART1, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
	}
	
	va_end(arg_ptr);
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
} 

#endif	



#if EN_USART2_RX   //���ʹ���˽���

/*
USART2������س���
*/

u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
////����״̬
////bit15��	������ɱ�־
////bit14��	���յ�0x0d
////bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	  

///*
//USART2ר�õ�printf����
//��ͬʱ����2�����ϴ���ʱ��printf����ֻ����������֮һ����������Ҫ�Դ�������printf����
//���÷�����USART2_printf("123"); //��USART2�����ַ�123
//*/
void USART2_printf (char *fmt, ...){ 
	char buffer[USART2_REC_LEN+1];  // ���ݳ���
	u8 i = 0;	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, USART2_REC_LEN+1, fmt, arg_ptr);
	while ((i < USART2_REC_LEN) && (i < strlen(buffer))){
        USART_SendData(USART2, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
	}
	va_end(arg_ptr);
}


//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void USART2_Init(u32 bound)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,Dʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ�� 
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ
 
	 
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); ; //��ʼ������
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
   
}


//����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���
void USART2_Send_Data(u8 *buf,u8 len)
{
	u8 t; 
	for(t=0;t<len;t++)		//ѭ����������
	{		   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART2,buf[t]);
	}	 
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);  
}
  
void TR_Receive(void)
{
	unsigned char BufC; 
	if(uart2Available())
	{
		BufC = uart2Read(); //��һ���ֽ�
		if((BufC==0x41))//�ж��Ƿ�Ϊ֡ ͷ
		{ 
			BufC = uart2Read(); //��һ���ֽ�
			if((BufC==0x42))
			{
				str1[2] = uart2Read()-0x30; 
				str1[3] = uart2Read()-0x30; 
				str1[4] = uart2Read()-0x30; 
				str1[5] = uart2Read()-0x30; 
				str1[6] = uart2Read()-0x30; 
				str1[7] = uart2Read()-0x30;  
				str1[8] = uart2Read()-0x30; 
				x_axis=str1[2]*100+str1[3]*10+str1[4];
				y_axis=str1[5]*100+str1[6]*10+str1[7];
				printf("x_axis��%d",x_axis);    //ʹ�õ�������λ��
				printf("\r\n");
				printf(" y_axis��%d\n",y_axis); 
				printf("\r\n");
				printf(" ���� ��%d\n",str1[8]); 
				printf("\r\n");
			}
			 
		}
	} 
}

/**
* @brief      UartRead
* @param[out]  Ret 1 Byte Data.
* @param[in]  void.
*/
uint8_t uart2Read(void)
{
    uint8_t ch ;
    while  (!h_u32RecCnt);

    ch = rx2Buffer[rx2BufferRTail];
    rx2BufferRTail++;
    if (rx2BufferRTail>=UART2_BUFFER_SIZE)
    {
        rx2BufferRTail  = 0;
    } 
    h_u32RecCnt--;
    return ch;
}

uint16_t uart2Available(void)
{
    return h_u32RecCnt;
}

void USART2_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
	{
		rx2Buffer[rxBufferNum] = USART_ReceiveData(USART2); //����8 Bit����
		rxBufferNum++;
		if (rxBufferNum >= UART2_BUFFER_SIZE ) rxBufferNum = 0;
		h_u32RecCnt++;
  } 
} 

#endif	

