#include "L298N.h"


void Direct_Motor_Init()                            // ��ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_L298N_GPIO_Port,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Pin=L298N_GPIO_Pin_num | L298N_GPIO_Pin_num1 | L298N_GPIO_Pin_num2 | L298N_GPIO_Pin_num3;
	GPIO_Init(L298N_GPIO_Port,&GPIO_InitStructure);      //L298N�˿ڳ�ʼ��
}



void Direct_Motor_Stop()      //���ֹͣ
{
	L298N_IN1=0;
	L298N_IN2=0;
	L298N_IN3=0;
	L298N_IN2=0;
}


void Direct_Motor_Forward()   //�����ת
{
	L298N_IN1=1;
	L298N_IN2=0;
	L298N_IN3=1;
	L298N_IN2=0;
}
                      

void Direct_Motor_Back()      //�����ת
{
	L298N_IN1=0;
	L298N_IN2=1;
	L298N_IN3=0;
	L298N_IN2=1;
}

void Car_L298N_Forward()     //С��ǰ��
{
	L298N_IN1=1;
	L298N_IN2=0;
	L298N_IN3=1;
	L298N_IN2=0;
}

void Car_L298N_Turn_Left()     //С����ת
{
	L298N_IN1=1;
	L298N_IN2=0;
	L298N_IN3=0;
	L298N_IN2=1;
}

void Car_L298N_Turn_Right()     //С����ת
{
	L298N_IN1=0;
	L298N_IN2=1;
	L298N_IN3=1;
	L298N_IN2=0;
}

void Car_L298N_Bak()           //С������
{
	L298N_IN1=0;
	L298N_IN2=1;
	L298N_IN3=0;
	L298N_IN2=1;
}
