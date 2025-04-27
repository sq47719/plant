#ifndef __ULTRASONSIC_H
#define __ULTRASONSIC_H
#include "timer2.h"




#define RCC_APB2Periph_Usr04_GPIO_Port       RCC_APB2Periph_GPIOB
#define Usr04_GPIO_Port                      GPIOB
#define Usr04_GPIO_Pin_Num_Tx                GPIO_Pin_13
#define Usr04_GPIO_Pin_Num_Rx                GPIO_Pin_14




void Hcsr04_Timer2_Init(void);   //超声波测距  定时器2测距定时初始化
void Hcsr04GetLength(float *Leng );
#endif
