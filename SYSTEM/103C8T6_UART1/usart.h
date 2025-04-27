#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"
#include "gps.h"     //������Ҫ��ͷ�ļ�
#include "TCS34725_Colour.h"
 /************************************************
��Ȩ��С��Ӳ��
���ںţ�΢��������С��Ӳ�����ڹ��ں���������������
************************************************/		

#define  RCC_APB2Periph_Usart1_GPIO_Port    RCC_APB2Periph_GPIOA
#define  Uart1_GPIO_Pin_Num_TX              GPIO_Pin_9
#define  Uart1_GPIO_Pin_Num_RX              GPIO_Pin_10
#define  Uart1_GPIO_Port                    GPIOA

#define   RCC_APB2Periph_Usart_USART1       RCC_APB2Periph_USART1
#define   Usart_Num_1                       USART1
#define   Usart_Num_1_IRQn                  USART1_IRQn
#define   USART_REC_LEN  		                200  	//�����������ֽ��� 200

#define   USART1_MAX_SEND_LEN               600   //����������ֽ��� 600



void Usart1_Init(u32 bound);  //����1��ʼ��  

void UART1_SendByte(u16 Data);  //���ڷ����ֽ�����
void UART1Write(char* data);    //���ڷ����ַ���
void UART1Write_Hex(char* data, int len);   //���ڷ���Hex
void USART_SendString(USART_TypeDef* USARTx, char *DataString);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...); //ESP8266����ģ����Ʒ��ͺ���
void u1_printf(char*,...) ;   
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);//   ��stm32f10x_usart.c���涨��   ʹ�÷�ʽ���磺USART_SendData (Usart_Num_1,0x0D);

void  Usart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer);  //���ڽ��յ����ݴ���
void  ASR01_Uart1_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag);
void Zigbee_Uart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer);


#endif
