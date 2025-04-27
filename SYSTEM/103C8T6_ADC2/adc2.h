#ifndef __ADC2_H
#define __ADC2_H	
#include "sys.h"
#include "stdio.h"

/******************************************
完成对ADC采集的控制只需要直接修改头文件内的相关
引脚定义即可
然后修改Get_Adc2_Convert_Data函数中的参数计算公式即可

当需要额外增加ADC2的采集通道时
重新额外定义一个ADC2_Init1();然后吧宏定义区分一组即可
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
