#include "led.h"
#include <stm32f10x_rcc.h>

void LED_Init()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	//使能GPIOC时钟——>APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;//GPIOC13
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//初始化GPIOC13引脚，设置输出模式
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}
