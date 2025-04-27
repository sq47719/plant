#ifndef __SERVOR_H
#define	__SERVOR_H

#include "stm32f10x.h"
#include "timer2.h"


#define  RCC_APB2Periph_Servor_GPIO_Port      RCC_APB2Periph_GPIOA
#define  Servor_GPIO_Pin_Num_0                GPIO_Pin_8
#define  Servor_GPIO_Pin_Num_1                GPIO_Pin_15
#define  Servor_GPIO_Port                     GPIOA

#define  RCC_APB2Periph_Servor1_GPIO_Port     RCC_APB2Periph_GPIOB
#define  Servor1_GPIO_Pin_Num_0               GPIO_Pin_12
#define  Servor1_GPIO_Pin_Num_1               GPIO_Pin_13
#define  Servor1_GPIO_Pin_Num_2               GPIO_Pin_14
#define  Servor1_GPIO_Port                    GPIOB

#define  Time2_ARR                            TIM2->ARR

#define  Servor_Num_0_Set                     GPIO_SetBits(Servor_GPIO_Port,Servor_GPIO_Pin_Num_0);
#define  Servor_Num_0_Cler                    GPIO_ResetBits(Servor_GPIO_Port,Servor_GPIO_Pin_Num_0);

#define  Servor_Num_1_Set                     GPIO_SetBits(Servor_GPIO_Port,Servor_GPIO_Pin_Num_1);
#define  Servor_Num_1_Cler                    GPIO_ResetBits(Servor_GPIO_Port,Servor_GPIO_Pin_Num_1);

#define  Servor1_Num_0_Set                    GPIO_SetBits(Servor1_GPIO_Port,Servor1_GPIO_Pin_Num_0);
#define  Servor1_Num_0_Cler                   GPIO_ResetBits(Servor1_GPIO_Port,Servor1_GPIO_Pin_Num_0);

#define  Servor1_Num_1_Set                    GPIO_SetBits(Servor1_GPIO_Port,Servor1_GPIO_Pin_Num_1);
#define  Servor1_Num_1_Cler                   GPIO_ResetBits(Servor1_GPIO_Port,Servor1_GPIO_Pin_Num_1);

#define  Servor1_Num_2_Set                    GPIO_SetBits(Servor1_GPIO_Port,Servor1_GPIO_Pin_Num_2);
#define  Servor1_Num_2_Cler                   GPIO_ResetBits(Servor1_GPIO_Port,Servor1_GPIO_Pin_Num_2);

#define MAXPWM 2505		 //舵机最大PWM控制脉宽2.5ms宏定义


extern u16 Servor_CPWM_Set_Buffer[9];  //根据该数组的值实现对舵机PWM占空比的调节实现对舵机旋转角度的控制    该全局变量在数组中设定


void Servo1(void);  //完成对舵机角度的控制
void Servor_GPIO_Config_Time2_Init(void);	//初始化定时器2   初始化舵机的IO口


#endif /* __GPIO_H */
