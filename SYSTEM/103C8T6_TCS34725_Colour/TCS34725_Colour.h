#ifndef __TCS34725_COLOUR_H
#define __TCS34725_COLOUR_H	



/************************************************************
                    颜色识别引脚说明
										
PinA(s0)  默认是高电平   串口模式    CT是串口的发    DR是串口的收
PinB(S1)  默认是高电平   MCU+TCS34725模式   SDA、SDL两个引脚不需要链接
默认的波特率是9600
供电电压3V-5V
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
