#ifndef _TIMER1_H
#define _TIMER1_H
#include "sys.h"



#define RCC_APB2Periph_Timer_TIM1   RCC_APB2Periph_TIM1
#define Timer_Tim1                  TIM1
#define Timer_Tim1_IRQn             TIM1_UP_IRQn


void Timer_Init(u16 arr,u16 psc);
#endif
