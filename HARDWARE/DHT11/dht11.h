#ifndef _DHT11_H
#define _DHT11_H
#include "sys.h"

#define DHT11_GPIO  GPIOB  //定义端口
#define DHT11_PIN    GPIO_Pin_12
#define DHT11_SetBits()  		GPIO_SetBits(DHT11_GPIO,DHT11_PIN)
#define DHT11_ResetBits()   GPIO_ResetBits(DHT11_GPIO,DHT11_PIN)
#define DHT11_ReadBits()    GPIO_ReadInputDataBit(DHT11_GPIO,DHT11_PIN)

void DHT11_Input(void);//输入模式
void DHT11_Output(void);//输出模式
void DHT11_Start(void);//复位端口
u16 DHT11_Check_ReadData(void);//检测DHT11响应信号,并读取数据
u16 DHT11_ReadByte(void);
u16 DHT11_GetTemp(void);  //温度变量的函数
u16 DHT11_GetHem(void); 
#endif
