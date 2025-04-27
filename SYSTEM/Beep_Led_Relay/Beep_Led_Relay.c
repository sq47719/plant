#include "Beep_Led_Relay.h"
#include "delay.h"
#include "stm32f10x.h"
#include "math.h" 
		  
void Led1_init(void)  //LED1���ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED1_GPIO_Port,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Pin=LED1_GPIO_Pin_num;
	GPIO_Init(LED1_GPIO_Port,&GPIO_InitStructure);      //LED1�˿ڳ�ʼ��
}

void Relay_init(void)  //�̵�����ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_Relay_GPIO_Port,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Pin=Relay_GPIO_Pin_num|Relay_GPIO_Pin_num1;
	GPIO_Init(Relay_GPIO_Port,&GPIO_InitStructure);     
}
