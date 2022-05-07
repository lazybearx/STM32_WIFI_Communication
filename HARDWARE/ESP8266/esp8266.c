#include "esp8266.h"
#include "string.h"
#include "bsp_usart.h"
#include "usart3.h"
#include "delay.h"

char a[]="AT+CWMODE=1";
char b[]="AT+RST";
char c[]="AT+CWJAP=\"lazybearx\",\"12345678\"";                
char d[]="AT+CIPMUX=1";
char e[]="AT+CIPSTART=0,\"TCP\",\"115.29.109.104\",6539";


void ESP8266_Init(void)
{
	//设置工作模式 1：station模式   2：AP模式  3：兼容 AP+station模式
	esp8266_send_cmd1((u8 *)a);
	delay_ms(1000);
	delay_ms(1000);
	
	//重启
	esp8266_send_cmd1((u8 *)b);
  delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

	//连接WIFI
	esp8266_send_cmd1((u8 *)c);
  delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

	
	esp8266_send_cmd1((u8 *)d);
  delay_ms(1000);
	delay_ms(1000);

	//连接TCP服务端
	esp8266_send_cmd1((u8 *)e);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

}

void esp8266_send_cmd1(u8 *cmd)
{
  u3_printf("%s\r\n",cmd);	//发送命令，需要加换行符
}
 

