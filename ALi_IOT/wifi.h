
#ifndef __WIFI_H
#define __WIFI_H

#include "usart2.h"	   	
#include "delay.h"	    //包含需要的头文件
#include "usart.h"	    //包含需要的头文件
#include "stm32f10x.h"  //包含需要的头文件


#define RCC_APB2Periph_ALi_GPIO_Port               RCC_APB2Periph_GPIOA   
#define ALi_GPIO_Pin_Num_Rst                       GPIO_Pin_8  
#define ALi_GPIO_Port                              GPIOA  

#define RESET_IO(x)    GPIO_WriteBit(ALi_GPIO_Port, ALi_GPIO_Pin_Num_Rst, (BitAction)x)  //控制WiFi的复位


#define SSID   "sabermm"                             //路由器SSID名称
#define PASS   "walp1314"                           //路由器密码

extern int ServerPort;
extern char ServerIP[128];                    //存放服务器IP或是域名

void ALi_ESP8266_GPIO_Init(void);
//以上这个函数是在主函数中调用

void WiFi_ResetIO_Init(void);
char WiFi_SendCmd(char *cmd, int timeout);
char WiFi_Reset(int timeout);
char WiFi_JoinAP(int timeout);
char WiFi_Connect_Server(int timeout);
char WiFi_Smartconfig(int timeout);
char WiFi_WaitAP(int timeout);
char WiFi_Connect_IoTServer(void);


#endif


