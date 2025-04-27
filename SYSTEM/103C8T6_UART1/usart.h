#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"
#include "gps.h"     //包含需要的头文件
#include "TCS34725_Colour.h"
 /************************************************
版权：小常硬件
公众号：微信搜索“小常硬件“在公众号免费下载相关资料
************************************************/		

#define  RCC_APB2Periph_Usart1_GPIO_Port    RCC_APB2Periph_GPIOA
#define  Uart1_GPIO_Pin_Num_TX              GPIO_Pin_9
#define  Uart1_GPIO_Pin_Num_RX              GPIO_Pin_10
#define  Uart1_GPIO_Port                    GPIOA

#define   RCC_APB2Periph_Usart_USART1       RCC_APB2Periph_USART1
#define   Usart_Num_1                       USART1
#define   Usart_Num_1_IRQn                  USART1_IRQn
#define   USART_REC_LEN  		                200  	//定义最大接收字节数 200

#define   USART1_MAX_SEND_LEN               600   //定义最大发送字节数 600



void Usart1_Init(u32 bound);  //串口1初始化  

void UART1_SendByte(u16 Data);  //串口发送字节数据
void UART1Write(char* data);    //串口发送字符串
void UART1Write_Hex(char* data, int len);   //串口发送Hex
void USART_SendString(USART_TypeDef* USARTx, char *DataString);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...); //ESP8266无线模块控制发送函数
void u1_printf(char*,...) ;   
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);//   在stm32f10x_usart.c里面定义   使用方式例如：USART_SendData (Usart_Num_1,0x0D);

void  Usart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer);  //串口接收的数据处理
void  ASR01_Uart1_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag);
void Zigbee_Uart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer);


#endif
