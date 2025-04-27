#ifndef __ZIGBEE_H
#define __ZIGBEE_H	 


#include "usart.h"
#include "usart2.h"
#include "usart3.h"


void Zigbee_Uart1_Init(void);
void Zigbee_Uart1_Host_Send_Message(char *Message_Buffer);
void Zigbee_Uart1_Receive_Message(char *Tem_Parameter,char *Him_Parameter);  //形参数量根据传输的数据个数进行修改
	
void Zigbee_Uart2_Init(void);
void Zigbee_Uart2_Host_Send_Message(char *Message_Buffer);
void Zigbee_Uart2_Receive_Message(char *Tem_Parameter,char *Him_Parameter);

void Zigbee_Uart3_Init(void);
void Zigbee_Uart3_Host_Send_Message(char *Message_Buffer);
void Zigbee_Uart3_Receive_Message(char *Tem_Parameter,char *Him_Parameter);
#endif
