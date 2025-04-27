#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
#include "OLED_I2C.h"
#include "HX711.h"
	  

#define  RCC_APB2Periph_key1_GPIO_Port     RCC_APB2Periph_GPIOB
#define  Key1_GPIO_Port                    GPIOB
#define  Key1_GPIO_Pin_num                 GPIO_Pin_12
#define  Key1_GPIO_Pin_num1                GPIO_Pin_13
#define  Key1_GPIO_Pin_num2                GPIO_Pin_14
#define  Key1_GPIO_Pin_num3                GPIO_Pin_15


#define KEY0  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num1)//读取按键1  
#define KEY2  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num2)//读取按键1
#define KEY3  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num3)//读取按键1
 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	  2	//KEY1按下
#define KEY2_PRES   3	//KEY_2按下(即WK_UP/KEY_UP)
#define KEY3_PRES   4

/*************重量去皮按键相关定义********
以下是去皮控制按键的引脚相关定义
******************************************/
#define  RCC_APB2Periph_QuPi_key1_GPIO_Port     RCC_APB2Periph_GPIOB
#define  QuPi_Key_GPIO_Port                     GPIOB
#define  QuPi_Key_GPIO_Pin_num                  GPIO_Pin_14

#define QuPi_KEY  GPIO_ReadInputDataBit(QuPi_Key_GPIO_Port,QuPi_Key_GPIO_Pin_num)//读取去皮按键是否按下

/************以上是重量去皮按键相关定义*****/

//根据定义的两类的IO口，设定了两个按键初始化函数   根据使用的按键调用对应的初始化函数
void KEY_Init(void);//IO初始化
void KEY1_Init(void); 

u8   KEY_Scan(u8);  	//按键扫描函数			
void Limit_Value_Set_1(u16 *B_Ma); //设定1个参数阈值
void Limit_Value_Set_2(u16 *T_Ma,u16 *H_Ma);//设定2参数阈值

void Key_Control_Handle(_Bool *Key_0_Press_Fla,_Bool *Key_1_Press_Fla,u8 *Key_0_Num);  //按键控制处理函数
void One_Key_Control_Handle(_Bool *Key_0_Press_Fla);//一个按键控制

void Weight_QuPi_KEY_Init(void); //     重量去皮按键IO初始化		
void Weight_QuPi_Key_Handle(void);    //重量去皮按键控制处理函数
#endif
