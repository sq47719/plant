#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "OLED_I2C.h"
#include "stdio.h"


#define ADC_Num    ADC1
#define RCC_APB2Periph_AD1_GPIO_Port         RCC_APB2Periph_GPIOA
#define RCC_APB2Periph_AD_Num                RCC_APB2Periph_ADC1
#define ADC1_GPIO_Pin_Num                    GPIO_Pin_1
#define ADC1_GPIO_Port                       GPIOA
#define ADC1_Channel_num                     ADC_Channel_1



#define RCC_APB2Periph_AD1_GPIO_Port_1         RCC_APB2Periph_GPIOB
#define RCC_APB2Periph_AD_Num_1                RCC_APB2Periph_ADC1
#define ADC1_GPIO_Pin_Num_1                    GPIO_Pin_0
#define ADC1_GPIO_Port_1                       GPIOB
#define ADC1_Channel_num_1                     ADC_Channel_8


#define RCC_APB2Periph_AD1_GPIO_Port_2         RCC_APB2Periph_GPIOB
#define RCC_APB2Periph_AD_Num_2                RCC_APB2Periph_ADC1
#define ADC1_GPIO_Pin_Num_2                    GPIO_Pin_1
#define ADC1_GPIO_Port_2                       GPIOB
#define ADC1_Channel_num_2                     ADC_Channel_9

#define RCC_APB2Periph_AD1_GPIO_Port_3         RCC_APB2Periph_GPIOA
#define RCC_APB2Periph_AD_Num_3                RCC_APB2Periph_ADC1
#define ADC1_GPIO_Pin_Num_3                    GPIO_Pin_5
#define ADC1_GPIO_Port_3                       GPIOA
#define ADC1_Channel_num_3                     ADC_Channel_5

#define RCC_APB2Periph_AD1_GPIO_Port_4         RCC_APB2Periph_GPIOA
#define RCC_APB2Periph_AD_Num_4                RCC_APB2Periph_ADC1
#define ADC1_GPIO_Pin_Num_4                    GPIO_Pin_4
#define ADC1_GPIO_Port_4                       GPIOA
#define ADC1_Channel_num_4                     ADC_Channel_4

void Adc_Init(void);
void Adc_Init1(void);
void Adc_Init2(void);
void Adc_Init3(void);
void Adc_Init4(void);
u16  Get_Adc(u8 ch); 
u16  Get_Adc_Average(u8 ch,u8 times); 
void Get_Adc_Convert_Data(float *Smo);
void Get_adc(float *Smo);
void Get_adc1(int *water_high);
void Get_adc2(float *co2);
void Get_adc3(float *Smo);
void Get_adc4(float *Smo);
#endif 
