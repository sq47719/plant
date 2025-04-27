#ifndef __ADC2_H
#define __ADC2_H	
#include "sys.h"
#include "stdio.h"

/******************************************
��ɶ�ADC�ɼ��Ŀ���ֻ��Ҫֱ���޸�ͷ�ļ��ڵ����
���Ŷ��弴��
Ȼ���޸�Get_Adc2_Convert_Data�����еĲ������㹫ʽ����

����Ҫ��������ADC2�Ĳɼ�ͨ��ʱ
���¶��ⶨ��һ��ADC2_Init1();Ȼ��ɺ궨������һ�鼴��
*******************************************/
#define ADC2_Num    ADC2
#define RCC_APB2Periph_AD2_GPIO_Port         RCC_APB2Periph_GPIOB
#define RCC_APB2Periph_AD2_Num                RCC_APB2Periph_ADC2
#define ADC2_GPIO_Pin_Num                    GPIO_Pin_0
#define ADC2_GPIO_Port                       GPIOB
#define ADC2_Channel_num                     ADC_Channel_8


void Adc2_Init(void);
u16  Get_Adc2(u8 ch); 
u16  Get_Adc2_Average(u8 ch,u8 times); 
void Get_Adc2_Convert_Data(float *Bea);
#endif 
