#ifndef __L298N_H
#define __L298N_H	  

#include "sys.h"

#define  RCC_APB2Periph_L298N_GPIO_Port     RCC_APB2Periph_GPIOA    //本次系统是采用GPIOA完成按键控制
#define  L298N_GPIO_Port                    GPIOA
#define  L298N_GPIO_Pin_num                 GPIO_Pin_0
#define  L298N_GPIO_Pin_num1                GPIO_Pin_1
#define  L298N_GPIO_Pin_num2                GPIO_Pin_2
#define  L298N_GPIO_Pin_num3                GPIO_Pin_3


#define L298N_IN1 PAout(0)
#define L298N_IN2 PAout(1)
#define L298N_IN3 PAout(2)
#define L298N_IN4 PAout(3)

void Direct_Motor_Init(void);
void Direct_Motor_Stop(void);
void Direct_Motor_Forward(void);
void Direct_Motor_Back(void);


void Car_L298N_Forward(void);
void Car_L298N_Turn_Left(void);
void Car_L298N_Turn_Right(void);
void Car_L298N_Bak(void);


#endif
