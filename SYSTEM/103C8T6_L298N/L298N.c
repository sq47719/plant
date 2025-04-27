#include "L298N.h"


void Direct_Motor_Init()                            // 初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_L298N_GPIO_Port,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Pin=L298N_GPIO_Pin_num | L298N_GPIO_Pin_num1 | L298N_GPIO_Pin_num2 | L298N_GPIO_Pin_num3;
	GPIO_Init(L298N_GPIO_Port,&GPIO_InitStructure);      //L298N端口初始化
}



void Direct_Motor_Stop()      //电机停止
{
	L298N_IN1=0;
	L298N_IN2=0;
	L298N_IN3=0;
	L298N_IN2=0;
}


void Direct_Motor_Forward()   //电机正转
{
	L298N_IN1=1;
	L298N_IN2=0;
	L298N_IN3=1;
	L298N_IN2=0;
}
                      

void Direct_Motor_Back()      //电机反转
{
	L298N_IN1=0;
	L298N_IN2=1;
	L298N_IN3=0;
	L298N_IN2=1;
}

void Car_L298N_Forward()     //小车前进
{
	L298N_IN1=1;
	L298N_IN2=0;
	L298N_IN3=1;
	L298N_IN2=0;
}

void Car_L298N_Turn_Left()     //小车左转
{
	L298N_IN1=1;
	L298N_IN2=0;
	L298N_IN3=0;
	L298N_IN2=1;
}

void Car_L298N_Turn_Right()     //小车右转
{
	L298N_IN1=0;
	L298N_IN2=1;
	L298N_IN3=1;
	L298N_IN2=0;
}

void Car_L298N_Bak()           //小车后退
{
	L298N_IN1=0;
	L298N_IN2=1;
	L298N_IN3=0;
	L298N_IN2=1;
}
