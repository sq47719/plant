
#ifndef _TIMER2_H
#define _TIMER2_H

#include "servor.h"

#define  RCC_APB1Periph_Timer_TIM2           RCC_APB1Periph_TIM2
#define  Timer_Tim2                          TIM2
#define  Timer_Tim2_IRQn                     TIM2_IRQn

extern unsigned  char Ms_HcSR_Count;  // �ڼ��㳬��������ʱ���� 

void TIM2_init(unsigned short int arr, unsigned short int psc);
void Open_Timer_Num_2(void);         //�򿪶�ʱ��   �ڼ��㳬��������ʱ����    �����ö�ʱ��2���ж�ʱ���ʱ����Ҫ����
void Close_Timer_Num_2(void);        //�رն�ʱ��   �ڼ��㳬��������ʱ����    �����ö�ʱ��2���ж�ʱ���ʱ����Ҫ����
#endif
