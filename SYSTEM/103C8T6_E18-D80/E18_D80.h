#ifndef __E18_D80_H
#define __E18_D80_H	 


/*****************************************

��ɫ ����
��ɫ �ź�
��ɫ GND

***************************************************/

#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"

#define RCC_APB2Periph_E18_D80_GPIO_Port             RCC_APB2Periph_GPIOA
#define E18_D80_GPIO_Pin_Num0                        GPIO_Pin_0
#define E18_D80_GPIO_Pin_Num1                        GPIO_Pin_1


#define E18_D80_GPIO_Port                            GPIOA



#define E18_D80_0  GPIO_ReadInputDataBit(E18_D80_GPIO_Port,E18_D80_GPIO_Pin_Num0)//��ȡ����ʶ��0
#define E18_D80_1  GPIO_ReadInputDataBit(E18_D80_GPIO_Port,E18_D80_GPIO_Pin_Num1)//��ȡ����ʶ��1   ����ӿ�������
#define E18_D80_2  GPIO_ReadInputDataBit(E18_D80_GPIO_Port,E18_D80_GPIO_Pin_Num2)//��ȡ����ʶ��2
#define E18_D80_3  GPIO_ReadInputDataBit(E18_D80_GPIO_Port,E18_D80_GPIO_Pin_Num3)//��ȡ����ʶ��3


void E18_D80_Init(void);
void Two_E18_D80_Get_Result(_Bool *E18_D80_GPIO_Pin_Num0_Flag,_Bool *E18_D80_GPIO_Pin_Num1_Flag);
void One_E18_D80_Get_Result(_Bool *E18_D80_GPIO_Pin_Num0_Flag);

#endif
