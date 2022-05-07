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
char strTemp[30];  //声明字符数组strTemp,初始化元素30
char strHumi[30];  //声明字符数组strHumi,初始化元素30
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
	//TIM2_Int_Init(4999,7199);//定时器初始化。10Khz的计数频率，计数到5000为500ms
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
	Adc_Init();
	//printf("初始化完成\n");
	//USART3_RX_STA=0;
	
	while (1)
	{	 
				
				temp_t=(float)adcx*3.3/4096;
				adcx=Get_Adc(ADC_Channel_0);
				printf("adcx:%d\n\r",adcx);
				printf("temp:%f\n\r",temp_t);
				sprintf((char *)adc,"%d",adcx);//将浮点数转换为字符
				sprintf((char *)vol,"%0.3f",temp_t);//将浮点数转换为字符
//	if(USART3_RX_STA&0x8000)    //如果消息接收完成，则处理
//		{
//			if(strstr((const char*)USART3_RX_BUF,"on"))  //这里是看接收到的消息中有没有自己设置的命令“on”，strstr()函数不会用的可以搜一下
//				{
//					GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//				}
//			if(strstr((const char*)USART3_RX_BUF,"off")) 
//			{
//				GPIO_SetBits(GPIOC,GPIO_Pin_13);
//			}
//			if(strstr((const char*)USART3_RX_BUF,"TH")) 
//			{
//				printf("温度:%d度\n  湿度是:%d百分比\n",DHT11_GetTemp()/256,DHT11_GetHem()/256);
//			}
//			USART3_RX_STA=0;   //消息处理完成，开始重新接收
//			memset(USART3_RX_BUF,0,600);         //将接收区清0
//		}	
	
	if(DHT11_Check_ReadData())
		{
			
			//sprintf(strTemp,"温度:%d",DHT11_GetTemp()/256);   //调用Sprintf函数把DHT11的温度数据格式化到字符串数组变量strTemp中
			//sprintf(strHumi,"湿度:%d",DHT11_GetHem()/256);    //调用Sprintf函数把DHT11的湿度数据格式化到字符串数组变量strHumi中
			Temp_Senser.temperature=DHT11_GetTemp()/256;
			Temp_Senser.humidity=DHT11_GetHem()/256;
			
			OLED_ShowCHinese(18,0,0);//温
		  OLED_ShowCHinese(33,0,1);//度
			OLED_ShowNum(2,3,Temp_Senser.temperature,5,15);      //输出温度
			OLED_ShowString(38,3, (u8 *)"C",15);
			OLED_ShowCHinese(77,0,2);//湿
		  OLED_ShowCHinese(92,0,3);//度
		  OLED_ShowNum(60,3,Temp_Senser.humidity,5,15);
		  OLED_ShowString(95,3, (u8 *)"%",15);
			OLED_ShowCHinese(18,6,9);//空
			OLED_ShowCHinese(33,6,10);//气
			OLED_ShowString(48,7,adc,3);
				//OLED_ShowNum(48,7,adcx,5,15);
			
			//用串口显示DHT11的采集数据
			printf("温度:%d度\n  湿度是:%d百分比\n",DHT11_GetTemp()/256,DHT11_GetHem()/256); 
			delay_ms(1000);
			
			if(Temp_Senser.temperature>=THRESHOLD)
			{	
				delay_ms(500);
				OLED_Clear(); 
				OLED_ShowCHinese(18,0,8);//高
				OLED_ShowCHinese(33,0,0);//温
				//LED0=~LED0;
			}
		}
//		else
//		{
//		printf("系统采集失败,一定是哪个环节出了问题!\n");
//		OLED_ShowCHinese(77,0,6);//故
//		OLED_ShowCHinese(92,0,7);//障
//		}
  delay_ms(500);  //延时
  delay_ms(500); 
  delay_ms(500);  
	}
}
////定时器2中断服务程序
//void TIM2_IRQHandler(void)   //TIM2中断
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
//		{
//		DHT11_Read_Data(&Temp_Senser.temperature,&Temp_Senser.humidity);
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志 
//		}
//}
