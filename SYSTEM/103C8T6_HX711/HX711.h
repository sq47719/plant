#ifndef _HX711_H
#define _HX711_H
#include "sys.h"
	

#define RCC_APB2Periph_HX711_GPIO_Port     RCC_APB2Periph_GPIOB
#define HX711_GPIO_Pin_Num_Data            GPIO_Pin_11
#define HX711_GPIO_Pin_Num_SCLK            GPIO_Pin_10
#define HX711_GPIO_Port                    GPIOB

/****************************
�����Ŷ˿��޸ĺ�������������Ҳ��Ҫ�����޸�
****************************/
#define DOUT PBout(11)                
#define SCK  PBout(10)
#define DIN  PBin(11)


#define GapValue 430     //��ֵ��ѡ���ѹ���������������йأ�5Kg��Ӧ430    10Kg��Ӧ210    20Kg��Ӧ104   40kg��Ӧ106.5
extern u32 Weight_Maopi;
extern s32 Weight_Shiwu;

void HX711_InIt ( void );
void Get_Weight(void);
void Get_Maopi(void);
#endif
