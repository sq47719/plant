
#ifndef _TIMER2_H
#define _TIMER2_H

#include "servor.h"

#define  RCC_APB1Periph_Timer_TIM2           RCC_APB1Periph_TIM2
#define  Timer_Tim2                          TIM2
#define  Timer_Tim2_IRQn                     TIM2_IRQn

extern unsigned  char Ms_HcSR_Count;  // 在计算超声波测距的时候用 

void TIM2_init(unsigned short int arr, unsigned short int psc);
void Open_Timer_Num_2(void);         //打开定时器   在计算超声波测距的时候用    当不用定时器2进行定时测距时，需要更换
void Close_Timer_Num_2(void);        //关闭定时器   在计算超声波测距的时候用    当不用定时器2进行定时测距时，需要更换
#endif
