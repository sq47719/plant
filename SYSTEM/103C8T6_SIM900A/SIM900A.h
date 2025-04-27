#ifndef _SIM900A_H
#define _SIM900A_H


#include "usart.h"
#include "usart2.h" 
#include "usart3.h"

void Sim900A_Uart1_Init(void);
void Sim900A_GSM_Uart1_Send_Message(void);

void Sim900A_Uart2_Init(void);
void Sim900A_GSM_Uart2_Send_Message(void);

void Sim900A_Uart2_Init(void);
void Sim900A_GSM_Uart2_Send_Message(void);
#endif
