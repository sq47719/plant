#include "E18_D80.h"



void E18_D80_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_E18_D80_GPIO_Port,ENABLE);//使能时钟

//	GPIO_InitStructure.GPIO_Pin  = E18_D80_GPIO_Pin_Num1|E18_D80_GPIO_Pin_Num1|E18_D80_GPIO_Pin_Num1|E18_D80_GPIO_Pin_Num0;//人体识别   需要几个初始化几个IO口
	GPIO_InitStructure.GPIO_Pin  = E18_D80_GPIO_Pin_Num0|E18_D80_GPIO_Pin_Num1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(E18_D80_GPIO_Port, &GPIO_InitStructure);//初始化GPIO
}

void Two_E18_D80_Get_Result(_Bool *E18_D80_GPIO_Pin_Num0_Flag,_Bool *E18_D80_GPIO_Pin_Num1_Flag)   //可以根据E18_D80的数量来修改形参数量
{
	if(E18_D80_0==0)   //根据光电管识别到物体后的电平进行设定   由于识别到是低电平所以设定为0
	{
		delay_ms(10);
		if(E18_D80_0==0)
		*E18_D80_GPIO_Pin_Num0_Flag=1;
	}
	else
		*E18_D80_GPIO_Pin_Num0_Flag=0;
	
	if(E18_D80_1==0)   //根据光电管识别到物体后的电平进行设定
	{
		delay_ms(10);
		if(E18_D80_1==0)
		*E18_D80_GPIO_Pin_Num1_Flag=1;
	}
	else
		*E18_D80_GPIO_Pin_Num1_Flag=0;
}

void One_E18_D80_Get_Result(_Bool *E18_D80_GPIO_Pin_Num0_Flag)   //可以根据E18_D80的数量来修改形参数量
{
	if(E18_D80_0==0)   //根据光电管识别到物体后的电平进行设定   由于识别到是低电平所以设定为0
	{
		delay_ms(10);
		if(E18_D80_0==0)
		*E18_D80_GPIO_Pin_Num0_Flag=1;
	}
	else
		*E18_D80_GPIO_Pin_Num0_Flag=0;
}
