����˵����
	ʹ��STM32F103ZET6�����壬����С���˶�
	����ģʽ1��ѭ��ģʽ-��·ѭ��
	����ģʽ2������ģʽ-HC05͸��ң��

ʹ�ÿ��������ţ�
	1. LED��PB5��PE5
	2. ֱ��������򼰱��٣�
		��1��PWM �� PB0��PB1
		��2������ �� PA1 PA2 PA3 PA4 GPIO
	3. OLED��IIC-GPIOB GPIO_Pin_6��GPIOB GPIO_Pin_7
	4. USART3-HC05 �� PB10-TX PB11-RX
	4. ADC �� PA5 PA6
	5. Beep �� PB8
	6. ѭ��ģ�� �� PC1 PC2 PC3 PC4 PC5
	7.������PE3 PE4
	
	GPIO : PA1 PA2 PA3 PA4 
	ADC  : PA5 PA6
	USART1 : PA9 PA10
	PWM  : PB0 PB1
	LED  : PB5 PE5
	OLED : PB6 PB7
	BEEP : PB8
	USART3-HC05 : PB10-TX PB11-RX
	ѭ��ģ��     : PC1 PC2 PC3 PC4 PC5
	������PE3 PE4

ʹ��оƬ���輰�������
	1. LED ��GPIO
	2. ��� �� 
		��1�� �� PA1 PA2 PA3 PA4 ��GPIO
		��2�� �� TIM3 CH3 CH4�� arr = 999 ,psc = 0
	3. OLED��IIC1-GPIOB �� I2C_SCL��GPIO_Pin_6��I2C_SDA��GPIOB GPIO_Pin_7
	4. USART3-HC05 ��������9600 PB10-TX PB11-RX
	5. ADC �� ADC1 PA5 PA6
	6. Beep �� GPIO PB8
	7. ѭ��ģ�� �� PC1 PC2 PC3 PC4 PC5
	8.������GPIO PE3 PE4 

��չ�ӿڣ�
	1. USART1�� USART1_TX-PA9   USART1_RX-PA10
