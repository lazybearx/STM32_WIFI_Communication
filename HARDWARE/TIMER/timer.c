//#include "sys.h"
//#include "timer.h"

//void TIM2_Int_Init(u16 arr,u16 psc)
//{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
//	
//	//��ʱ��TIM3��ʼ��
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

//	//�ж����ȼ�NVIC����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_Init(GPIOB, &GPIO_InitStructure);
// GPIO_SetBits(GPIOB,GPIO_Pin_1);

//	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
//}












