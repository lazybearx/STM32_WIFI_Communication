#include "delay.h"
#include "usart.h"
#include "dht11.h"

u8 DHT11_hem_high,DHT11_hem_low,DHT11_temp_high,DHT11_temp_low; 

//GPIO输入模式
void DHT11_Input(void){
  GPIO_InitTypeDef  GPIO_InitStruct; 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟
	
  GPIO_InitStruct.GPIO_Pin = DHT11_PIN; //选择端口号
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 (输入)
	
	GPIO_Init(DHT11_GPIO, &GPIO_InitStruct);
}
//GPIO输出模式
void DHT11_Output(void){
    GPIO_InitTypeDef GPIO_InitStruct;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
    GPIO_InitStruct.GPIO_Pin = DHT11_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
    GPIO_Init(DHT11_GPIO,&GPIO_InitStruct);
}
//主机启动等待响应
void DHT11_Start(void){
    DHT11_Output();
    DHT11_ResetBits();
    delay_ms(20);
    DHT11_SetBits();
    delay_us(40);
}
//读取一个字节数据
u16 DHT11_ReadByte(void){
    u8 data=0;//存储数据
    u8 i;//读取数据位数
    u8 flag;//标志量
    //DHT11_Input();
    for ( i = 0; i < 8; i++)//依次读取8位
    {
        flag=1;
        while (!DHT11_ReadBits()&&flag++);
        delay_us(30);
        data<<=1;//temp的值左移一位
        if(DHT11_ReadBits()==1)//读取到PA9为高电平
        {
            data |=1;//或运算,有1得1
        }
        //等待低电平,进入下一位数据接收
        flag=1;
        while (DHT11_ReadBits()&&flag++);
    }
    return data; //返回接收到的数据
}
//检测DHT11响应信号,并读取数据
u16 DHT11_Check_ReadData(void){
    u8 flag=1;
    u8 temp_high,temp_low,hem_high,hem_low,Check;
		DHT11_hem_high   = 0;
		DHT11_hem_low    = 0;
		DHT11_temp_high  = 0;
		DHT11_temp_low   = 0;
	
		DHT11_Start();
	
    DHT11_Input();
    //检测DHT11响应信号
    if(DHT11_ReadBits() == 0){
      flag=1;
			while(!DHT11_ReadBits()&&flag++);//等待响应信号结束
		
      flag = 1;//高电平传输数据,等待DHT11传输完毕,持续26us - 28us表示的是0;持续70us表示的是1
			while(DHT11_ReadBits()&&flag++);
			hem_high = DHT11_ReadByte();//湿度的高八位
			hem_low  = DHT11_ReadByte();//湿度的低八位
			temp_high  = DHT11_ReadByte();//温度的高八位
			temp_low   = DHT11_ReadByte();//温度的低八位
			Check = DHT11_ReadByte();//用于校验
     
			if(Check == ( temp_high + temp_low + hem_high + hem_low ))//校验和
			{
				DHT11_hem_high = hem_high;//写入湿度整数变量
				DHT11_hem_low = hem_low;//写入湿度小数变量
				DHT11_temp_high = temp_high;//写入温度整数变量
				DHT11_temp_low  = temp_low;//写入温度小数变量
			
				return 1;//返回1,表示成功采集
			}
    else
    {
      return 0;
    }
  }
    return 0;
}

//获取温度值
u16 DHT11_GetTemp(void) 
{
  /* 左移8位再或运算*/
  /* DHT11只能采集整数数据*/
  
  return(DHT11_temp_high <<8 | DHT11_temp_low);
}

//获取湿度值
u16 DHT11_GetHem(void)
{
  // [把DHT11_hem_high左移8位]
  return(DHT11_hem_high <<8 | DHT11_hem_low);

}

