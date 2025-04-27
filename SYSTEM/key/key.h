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


#define KEY0  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num1)//��ȡ����1  
#define KEY2  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num2)//��ȡ����1
#define KEY3  GPIO_ReadInputDataBit(Key1_GPIO_Port,Key1_GPIO_Pin_num3)//��ȡ����1
 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define KEY2_PRES   3	//KEY_2����(��WK_UP/KEY_UP)
#define KEY3_PRES   4

/*************����ȥƤ������ض���********
������ȥƤ���ư�����������ض���
******************************************/
#define  RCC_APB2Periph_QuPi_key1_GPIO_Port     RCC_APB2Periph_GPIOB
#define  QuPi_Key_GPIO_Port                     GPIOB
#define  QuPi_Key_GPIO_Pin_num                  GPIO_Pin_14

#define QuPi_KEY  GPIO_ReadInputDataBit(QuPi_Key_GPIO_Port,QuPi_Key_GPIO_Pin_num)//��ȡȥƤ�����Ƿ���

/************����������ȥƤ������ض���*****/

//���ݶ���������IO�ڣ��趨������������ʼ������   ����ʹ�õİ������ö�Ӧ�ĳ�ʼ������
void KEY_Init(void);//IO��ʼ��
void KEY1_Init(void); 

u8   KEY_Scan(u8);  	//����ɨ�躯��			
void Limit_Value_Set_1(u16 *B_Ma); //�趨1��������ֵ
void Limit_Value_Set_2(u16 *T_Ma,u16 *H_Ma);//�趨2������ֵ

void Key_Control_Handle(_Bool *Key_0_Press_Fla,_Bool *Key_1_Press_Fla,u8 *Key_0_Num);  //�������ƴ�����
void One_Key_Control_Handle(_Bool *Key_0_Press_Fla);//һ����������

void Weight_QuPi_KEY_Init(void); //     ����ȥƤ����IO��ʼ��		
void Weight_QuPi_Key_Handle(void);    //����ȥƤ�������ƴ�����
#endif
