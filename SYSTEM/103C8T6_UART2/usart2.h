
#ifndef __USART2_H
#define __USART2_H

#include "stdio.h"      
#include "stdarg.h"		 
#include "string.h"    
#include "gps.h"     //������Ҫ��ͷ�ļ�
#include "usart.h"     //������Ҫ��ͷ�ļ�
#include "TCS34725_Colour.h"
#include "timer4.h"


#define  RCC_APB2Periph_Usart2_GPIO_Port    RCC_APB2Periph_GPIOA
#define  Uart2_GPIO_Pin_Num_TX              GPIO_Pin_2
#define  Uart2_GPIO_Pin_Num_RX              GPIO_Pin_3
#define  Uart2_GPIO_Port                    GPIOA


#define   RCC_APB1Periph_Usart_USART2       RCC_APB1Periph_USART2
#define   Usart_Num_2                       USART2
#define   Usart_Num_2_IRQn                  USART2_IRQn
#define   USART_REC_LEN  		                200  	//�����������ֽ��� 200
#define   USART2_MAX_SEND_LEN               600   //����������ֽ��� 600




// ���µ�ȫ�ֱ����������� ALi�����ļ���Ҫ   С��
extern u16  point2 ;
extern char USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
#define WiFi_printf       u2_printf                   //����2���� WiFi
#define WiFi_RxCounter    point2                      //����2���� WiFi
#define WiFi_RX_BUF       USART2_RX_BUF               //����2���� WiFi
#define WiFi_RXBUFF_SIZE  USART_REC_LEN               //����2���� WiFi
extern    char connectFlag;      //�����������жϱ�־
//���϶�����ALi�����ļ�����Ҫ


extern unsigned char esp8266_buf[512];                //ESP8266������ȫ�ֱ���
extern unsigned short esp8266_cnt, esp8266_cntPre;

void Usart2_Init(u32 bound);  //����2��ʼ��  

void UART2_SendByte(u16 Data);  //���ڷ����ֽ�����
void UART2Write(char* data);    //���ڷ����ַ���
void UART2Write_Hex(char* data, int len);   //���ڷ���Hex

void  Usart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer);  //���ڽ��յ����ݴ���

void  u2_printf(char* fmt,...);
void USART_SendString(USART_TypeDef* USARTx, char *DataString);  //��uart.c�ж���
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);  //��ESP8266����ͨ��ģ����ʹ��
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);//   ��stm32f10x_usart.c���涨��   ʹ�÷�ʽ���磺USART_SendData (Usart_Num_1,0x0D);

void u2_TxData(unsigned char *data);  //���������ݷ���ʹ��

void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag);   //����ʶ��Ĵ�����
void Zigbee_Uart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer);

#endif


