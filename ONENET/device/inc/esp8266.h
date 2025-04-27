#ifndef _ESP8266_H_
#define _ESP8266_H_



#include "usart2.h" 

#define RCC_APB2Periph_ESP8266_GPIO_Port       RCC_APB2Periph_GPIOA
#define Esp8266_GPIO_Pin_Num_RST               GPIO_Pin_8
#define Esp8266_GPIO_Port                      GPIOA

#define ESP8266_Rst_Clear                       GPIO_WriteBit(Esp8266_GPIO_Port, Esp8266_GPIO_Pin_Num_RST, Bit_RESET);
#define ESP8266_Rst_Set                         GPIO_WriteBit(Esp8266_GPIO_Port, Esp8266_GPIO_Pin_Num_RST, Bit_SET);

#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志


#define ESP8266_WIFI_INFO		"AT+CWJAP=\"iphones\",\"wpy807807\"\r\n"

void ESP8266_Uart2_Init(void);

void ESP8266_Clear(void);

_Bool ESP8266_SendCmd(char *cmd, char *res);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

#endif
