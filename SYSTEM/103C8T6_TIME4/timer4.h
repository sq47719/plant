
#ifndef _TIMER4_H
#define _TIMER4_H

#include "mqtt.h" 
#include "utils_hmac.h"
#include "wifi.h" 
#include "usart2.h" 


#define  RCC_APB1Periph_Timer_TIM4           RCC_APB1Periph_TIM4
#define  Timer_Tim4                          TIM4
#define  Timer_Tim4_IRQn                     TIM4_IRQn



void TIM4_Init(unsigned short int, unsigned short int);

#endif
