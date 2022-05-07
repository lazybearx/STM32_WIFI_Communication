#include "sys.h"
#include "string.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "oled.h"
#include "bmp.h"
#include "timer.h"
#include "adc.h"
//#include "usart3.h"
//#include "esp8266.h"
#define THRESHOLD 25
typedef struct{
	u16 temperature;
  u16 humidity;
	u16 set;

}Sensor;
Sensor Temp_Senser;
char strTemp[30];  //�����ַ�����strTemp,��ʼ��Ԫ��30
char strHumi[30];  //�����ַ�����strHumi,��ʼ��Ԫ��30
u16 temp;
u16 humi;
  u8 adc[25];
	u8 vol[25];
	u16 adcx;
	float temp_t;
int main(void)
{	Temp_Senser.set=0;
	//Temp_Senser.temperature=0;
  //Temp_Senser.humidity=0;
	delay_init();
	USART_Config();
	//usart3_init(115200);
	//ESP8266_Init();
	//TIM2_Int_Init(4999,7199);//��ʱ����ʼ����10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 
	Adc_Init();
	//printf("��ʼ�����\n");
	//USART3_RX_STA=0;
	
	while (1)
	{	 
				
				temp_t=(float)adcx*3.3/4096;
				adcx=Get_Adc(ADC_Channel_0);
				printf("adcx:%d\n\r",adcx);
				printf("temp:%f\n\r",temp_t);
				sprintf((char *)adc,"%d",adcx);//��������ת��Ϊ�ַ�
				sprintf((char *)vol,"%0.3f",temp_t);//��������ת��Ϊ�ַ�
//	if(USART3_RX_STA&0x8000)    //�����Ϣ������ɣ�����
//		{
//			if(strstr((const char*)USART3_RX_BUF,"on"))  //�����ǿ����յ�����Ϣ����û���Լ����õ����on����strstr()���������õĿ�����һ��
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//				}
//			if(strstr((const char*)USART3_RX_BUF,"off")) 
//			{
//				GPIO_SetBits(GPIOC,GPIO_Pin_13);
//			}
//			if(strstr((const char*)USART3_RX_BUF,"TH")) 
//			{
//				printf("�¶�:%d��\n  ʪ����:%d�ٷֱ�\n",DHT11_GetTemp()/256,DHT11_GetHem()/256);
//			}
//			USART3_RX_STA=0;   //��Ϣ������ɣ���ʼ���½���
//			memset(USART3_RX_BUF,0,600);         //����������0
//		}	
	
	if(DHT11_Check_ReadData())
		{
			
			//sprintf(strTemp,"�¶�:%d",DHT11_GetTemp()/256);   //����Sprintf������DHT11���¶����ݸ�ʽ�����ַ����������strTemp��
			//sprintf(strHumi,"ʪ��:%d",DHT11_GetHem()/256);    //����Sprintf������DHT11��ʪ�����ݸ�ʽ�����ַ����������strHumi��
			Temp_Senser.temperature=DHT11_GetTemp()/256;
			Temp_Senser.humidity=DHT11_GetHem()/256;
			
			OLED_ShowCHinese(18,0,0);//��
		  OLED_ShowCHinese(33,0,1);//��
			OLED_ShowNum(2,3,Temp_Senser.temperature,5,15);      //����¶�
			OLED_ShowString(38,3, (u8 *)"C",15);
			OLED_ShowCHinese(77,0,2);//ʪ
		  OLED_ShowCHinese(92,0,3);//��
		  OLED_ShowNum(60,3,Temp_Senser.humidity,5,15);
		  OLED_ShowString(95,3, (u8 *)"%",15);
			OLED_ShowCHinese(18,6,9);//��
			OLED_ShowCHinese(33,6,10);//��
			OLED_ShowString(48,7,adc,3);
				//OLED_ShowNum(48,7,adcx,5,15);
			
			//�ô�����ʾDHT11�Ĳɼ�����
			printf("�¶�:%d��\n  ʪ����:%d�ٷֱ�\n",DHT11_GetTemp()/256,DHT11_GetHem()/256); 
			delay_ms(1000);
			
			if(Temp_Senser.temperature>=THRESHOLD)
			{	
				delay_ms(500);
				OLED_Clear(); 
				OLED_ShowCHinese(18,0,8);//��
				OLED_ShowCHinese(33,0,0);//��
				//LED0=~LED0;
			}
		}
//		else
//		{
//		printf("ϵͳ�ɼ�ʧ��,һ�����ĸ����ڳ�������!\n");
//		OLED_ShowCHinese(77,0,6);//��
//		OLED_ShowCHinese(92,0,7);//��
//		}
  delay_ms(500);  //��ʱ
  delay_ms(500); 
  delay_ms(500);  
	}
}
////��ʱ��2�жϷ������
//void TIM2_IRQHandler(void)   //TIM2�ж�
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
//		{
//		DHT11_Read_Data(&Temp_Senser.temperature,&Temp_Senser.humidity);
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־ 
//		}
//}
