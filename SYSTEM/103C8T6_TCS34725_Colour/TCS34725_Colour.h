#ifndef __TCS34725_COLOUR_H
#define __TCS34725_COLOUR_H	



/************************************************************
                    ��ɫʶ������˵��
										
PinA(s0)  Ĭ���Ǹߵ�ƽ   ����ģʽ    CT�Ǵ��ڵķ�    DR�Ǵ��ڵ���
PinB(S1)  Ĭ���Ǹߵ�ƽ   MCU+TCS34725ģʽ   SDA��SDL�������Ų���Ҫ����
Ĭ�ϵĲ�������9600
�����ѹ3V-5V
**************************************************************/
#include "usart.h"
#include "usart2.h" 
#include "usart3.h" 
#include "delay.h"
extern _Bool TCS34725_Colour_Receive_Flag;

typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} RGB;

void TCS34725_Colour_Uart1_Init(void);
void TCS34725_Colour_Uart1_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag);

void TCS34725_Colour_Uart2_Init(void);
void TCS34725_Colour_Uart2_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag);

void TCS34725_Colour_Uart3_Init(void);
void TCS34725_Colour_Uart3_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag);

#endif
