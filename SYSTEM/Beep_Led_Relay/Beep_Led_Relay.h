#ifndef __BEEP_LED_RELAY_H  //if no define
#define __BEEP_LED_RELAY_H
#include "stm32f10x.h"



/***********�������궨��*************
GPIO_A�˿ڿ���BEEP
�������Ҫ�õ����Խ�����Ҫ�õ�������
************************/

#define RCC_APB2Periph_Beep_GPIO_Port    RCC_APB2Periph_GPIOC
#define Beep_GPIO_Pin_num                GPIO_Pin_15
#define Beep_GPIO_Port                   GPIOC


#define Beep PCout(15)


/**********LED�궨��*************
GPIO_A�˿ڿ���LED
�������Ҫ�õ����Խ�����Ҫ�õ�������
************************/

#define RCC_APB2Periph_LED0_GPIO_Port    RCC_APB2Periph_GPIOA
#define LED0_GPIO_Pin_num                GPIO_Pin_0
#define LED0_GPIO_Pin_num1               GPIO_Pin_1
#define LED0_GPIO_Pin_num2               GPIO_Pin_2
#define LED0_GPIO_Pin_num3               GPIO_Pin_3
#define LED0_GPIO_Port                   GPIOA

#define Led0_0 PAout(0)
#define Led0_1 PAout(1)
#define Led0_2 PAout(2)
#define Led0_3 PAout(3)


/**********LED�궨��*************
GPIO_B�˿ڿ���LED
�������Ҫ�õ����Խ�����Ҫ�õ�������
************************/

#define RCC_APB2Periph_LED1_GPIO_Port    RCC_APB2Periph_GPIOA
#define LED1_GPIO_Pin_num                GPIO_Pin_11
#define LED1_GPIO_Port                   GPIOA

#define Led1_0 PAout(11)


/**********�̵����궨��*************
GPIO_B�˿ڿ��Ƽ̵���
�������Ҫ�õ����Խ�����Ҫ�õ�������
************************/

#define RCC_APB2Periph_Relay_GPIO_Port    RCC_APB2Periph_GPIOB
#define Relay_GPIO_Pin_num                GPIO_Pin_8
#define Relay_GPIO_Pin_num1               GPIO_Pin_9
#define Relay_GPIO_Pin_num2               GPIO_Pin_10
#define Relay_GPIO_Port                   GPIOB

#define Relay_0 PBout(8)
#define Relay_1 PBout(9)
#define Relay_2 PBout(10)


void Beep_init(void);    //���������ų�ʼ��
void Led0_init(void);  //LED0���ų�ʼ��
void Led1_init(void);  //LED1���ų�ʼ��
void Relay_init(void);  //�̵�����ʼ��
#endif
