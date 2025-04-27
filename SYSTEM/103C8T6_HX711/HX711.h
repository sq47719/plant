#ifndef _HX711_H
#define _HX711_H
#include "sys.h"
	

#define RCC_APB2Periph_HX711_GPIO_Port     RCC_APB2Periph_GPIOB
#define HX711_GPIO_Pin_Num_Data            GPIO_Pin_11
#define HX711_GPIO_Pin_Num_SCLK            GPIO_Pin_10
#define HX711_GPIO_Port                    GPIOB

/****************************
当引脚端口修改后以下引脚配置也需要进行修改
****************************/
#define DOUT PBout(11)                
#define SCK  PBout(10)
#define DIN  PBin(11)


#define GapValue 430     //该值与选择的压力传感器的量程有关，5Kg对应430    10Kg对应210    20Kg对应104   40kg对应106.5
extern u32 Weight_Maopi;
extern s32 Weight_Shiwu;

void HX711_InIt ( void );
void Get_Weight(void);
void Get_Maopi(void);
#endif
