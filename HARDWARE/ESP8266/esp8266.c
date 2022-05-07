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
	//���ù���ģʽ 1��stationģʽ   2��APģʽ  3������ AP+stationģʽ
	esp8266_send_cmd1((u8 *)a);
	delay_ms(1000);
	delay_ms(1000);
	
	//����
	esp8266_send_cmd1((u8 *)b);
  delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

	//����WIFI
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

	//����TCP�����
	esp8266_send_cmd1((u8 *)e);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

}

void esp8266_send_cmd1(u8 *cmd)
{
  u3_printf("%s\r\n",cmd);	//���������Ҫ�ӻ��з�
}
 

