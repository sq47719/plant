
#ifndef __WIFI_H
#define __WIFI_H

#include "usart2.h"	   	
#include "delay.h"	    //������Ҫ��ͷ�ļ�
#include "usart.h"	    //������Ҫ��ͷ�ļ�
#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�


#define RCC_APB2Periph_ALi_GPIO_Port               RCC_APB2Periph_GPIOA   
#define ALi_GPIO_Pin_Num_Rst                       GPIO_Pin_8  
#define ALi_GPIO_Port                              GPIOA  

#define RESET_IO(x)    GPIO_WriteBit(ALi_GPIO_Port, ALi_GPIO_Pin_Num_Rst, (BitAction)x)  //����WiFi�ĸ�λ


#define SSID   "sabermm"                             //·����SSID����
#define PASS   "walp1314"                           //·��������

extern int ServerPort;
extern char ServerIP[128];                    //��ŷ�����IP��������

void ALi_ESP8266_GPIO_Init(void);
//����������������������е���

void WiFi_ResetIO_Init(void);
char WiFi_SendCmd(char *cmd, int timeout);
char WiFi_Reset(int timeout);
char WiFi_JoinAP(int timeout);
char WiFi_Connect_Server(int timeout);
char WiFi_Smartconfig(int timeout);
char WiFi_WaitAP(int timeout);
char WiFi_Connect_IoTServer(void);


#endif


