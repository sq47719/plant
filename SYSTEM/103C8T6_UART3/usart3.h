#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "gps.h"     //������Ҫ��ͷ�ļ�
#include "usart.h"
#include "TCS34725_Colour.h"
		

#define  RCC_APB2Periph_Usart3_GPIO_Port    RCC_APB2Periph_GPIOB
#define  Uart3_GPIO_Pin_Num_TX              GPIO_Pin_10
#define  Uart3_GPIO_Pin_Num_RX              GPIO_Pin_11
#define  Uart3_GPIO_Port                    GPIOB

#define   RCC_APB1Periph_Usart_USART3       RCC_APB1Periph_USART3
#define   Usart_Num_3                       USART3
#define   Usart_Num_3_IRQn                  USART3_IRQn
#define   USART_REC_LEN  		                200  	//�����������ֽ��� 200
#define   USART3_MAX_SEND_LEN               600   //����������ֽ��� 600



void Usart3_Init(u32 bound);  //����3��ʼ��  

void UART3_SendByte(u16 Data);  //���ڷ����ֽ�����
void UART3Write(char* data);    //���ڷ����ַ���
void UART3Write_Hex(char* data, int len);   //���ڷ���Hex

void  Usart3_Receive_Data_Control(char *Uart3_Receive_Data_Buffer);  //���ڽ��յ����ݴ���
void  u3_printf(char* fmt,...);   //�������ʱ  ��Ҫ�޸�printf�������з��ͣ����øú���

void USART_SendString(USART_TypeDef* USARTx, char *DataString);  //��uart.c�ж���
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);//   ��stm32f10x_usart.c���涨��   ʹ�÷�ʽ���磺USART_SendData (Usart_Num_1,0x0D);

void  ASR01_Uart3_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag); //����ģ��Ĵ�����
void  Zigbee_Uart3_Receive_Data_Control(char *Uart3_Receive_Data_Buffer);
#endif













