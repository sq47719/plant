
#ifndef _TIMER3_H
#define _TIMER3_H

#include "mqtt.h" 


#define  RCC_APB1Periph_Timer_TIM3           RCC_APB1Periph_TIM3
#define  Timer_Tim3                          TIM3
#define  Timer_Tim3_IRQn                     TIM3_IRQn




void TIM3_init(unsigned short int arr, unsigned short int psc);
void TIM3_ENABLE_30S(void);
void TIM3_ENABLE_2S(void);
#endif
