
#ifndef __USART2_H
#define __USART2_H

#include "stdio.h"      
#include "stdarg.h"		 
#include "string.h"    
#include "gps.h"     //包含需要的头文件
#include "usart.h"     //包含需要的头文件
#include "TCS34725_Colour.h"
#include "timer4.h"


#define  RCC_APB2Periph_Usart2_GPIO_Port    RCC_APB2Periph_GPIOA
#define  Uart2_GPIO_Pin_Num_TX              GPIO_Pin_2
#define  Uart2_GPIO_Pin_Num_RX              GPIO_Pin_3
#define  Uart2_GPIO_Port                    GPIOA


#define   RCC_APB1Periph_Usart_USART2       RCC_APB1Periph_USART2
#define   Usart_Num_2                       USART2
#define   Usart_Num_2_IRQn                  USART2_IRQn
#define   USART_REC_LEN  		                200  	//定义最大接收字节数 200
#define   USART2_MAX_SEND_LEN               600   //定义最大发送字节数 600




// 以下的全局变量声明和是 ALi控制文件需要   小常
extern u16  point2 ;
extern char USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
#define WiFi_printf       u2_printf                   //串口2控制 WiFi
#define WiFi_RxCounter    point2                      //串口2控制 WiFi
#define WiFi_RX_BUF       USART2_RX_BUF               //串口2控制 WiFi
#define WiFi_RXBUFF_SIZE  USART_REC_LEN               //串口2控制 WiFi
extern    char connectFlag;      //阿里云连接判断标志
//以上定义在ALi控制文件中需要


extern unsigned char esp8266_buf[512];                //ESP8266的两个全局变量
extern unsigned short esp8266_cnt, esp8266_cntPre;

void Usart2_Init(u32 bound);  //串口2初始化  

void UART2_SendByte(u16 Data);  //串口发送字节数据
void UART2Write(char* data);    //串口发送字符串
void UART2Write_Hex(char* data, int len);   //串口发送Hex

void  Usart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer);  //串口接收的数据处理

void  u2_printf(char* fmt,...);
void USART_SendString(USART_TypeDef* USARTx, char *DataString);  //在uart.c中定义
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);  //在ESP8266无线通信模块中使用
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);//   在stm32f10x_usart.c里面定义   使用方式例如：USART_SendData (Usart_Num_1,0x0D);

void u2_TxData(unsigned char *data);  //阿里云数据发送使用

void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag);   //语音识别的处理函数
void Zigbee_Uart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer);

#endif


