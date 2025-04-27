#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "gps.h"     //包含需要的头文件
#include "usart.h"
#include "TCS34725_Colour.h"
		

#define  RCC_APB2Periph_Usart3_GPIO_Port    RCC_APB2Periph_GPIOB
#define  Uart3_GPIO_Pin_Num_TX              GPIO_Pin_10
#define  Uart3_GPIO_Pin_Num_RX              GPIO_Pin_11
#define  Uart3_GPIO_Port                    GPIOB

#define   RCC_APB1Periph_Usart_USART3       RCC_APB1Periph_USART3
#define   Usart_Num_3                       USART3
#define   Usart_Num_3_IRQn                  USART3_IRQn
#define   USART_REC_LEN  		                200  	//定义最大接收字节数 200
#define   USART3_MAX_SEND_LEN               600   //定义最大发送字节数 600



void Usart3_Init(u32 bound);  //串口3初始化  

void UART3_SendByte(u16 Data);  //串口发送字节数据
void UART3Write(char* data);    //串口发送字符串
void UART3Write_Hex(char* data, int len);   //串口发送Hex

void  Usart3_Receive_Data_Control(char *Uart3_Receive_Data_Buffer);  //串口接收的数据处理
void  u3_printf(char* fmt,...);   //多个串口时  需要修改printf函数进行发送，调用该函数

void USART_SendString(USART_TypeDef* USARTx, char *DataString);  //在uart.c中定义
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);//   在stm32f10x_usart.c里面定义   使用方式例如：USART_SendData (Usart_Num_1,0x0D);

void  ASR01_Uart3_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag); //语音模块的处理函数
void  Zigbee_Uart3_Receive_Data_Control(char *Uart3_Receive_Data_Buffer);
#endif













