#include "E18_D80.h"



void E18_D80_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_E18_D80_GPIO_Port,ENABLE);//ʹ��ʱ��

//	GPIO_InitStructure.GPIO_Pin  = E18_D80_GPIO_Pin_Num1|E18_D80_GPIO_Pin_Num1|E18_D80_GPIO_Pin_Num1|E18_D80_GPIO_Pin_Num0;//����ʶ��   ��Ҫ������ʼ������IO��
	GPIO_InitStructure.GPIO_Pin  = E18_D80_GPIO_Pin_Num0|E18_D80_GPIO_Pin_Num1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(E18_D80_GPIO_Port, &GPIO_InitStructure);//��ʼ��GPIO
}

void Two_E18_D80_Get_Result(_Bool *E18_D80_GPIO_Pin_Num0_Flag,_Bool *E18_D80_GPIO_Pin_Num1_Flag)   //���Ը���E18_D80���������޸��β�����
{
	if(E18_D80_0==0)   //���ݹ���ʶ�������ĵ�ƽ�����趨   ����ʶ���ǵ͵�ƽ�����趨Ϊ0
	{
		delay_ms(10);
		if(E18_D80_0==0)
		*E18_D80_GPIO_Pin_Num0_Flag=1;
	}
	else
		*E18_D80_GPIO_Pin_Num0_Flag=0;
	
	if(E18_D80_1==0)   //���ݹ���ʶ�������ĵ�ƽ�����趨
	{
		delay_ms(10);
		if(E18_D80_1==0)
		*E18_D80_GPIO_Pin_Num1_Flag=1;
	}
	else
		*E18_D80_GPIO_Pin_Num1_Flag=0;
}

void One_E18_D80_Get_Result(_Bool *E18_D80_GPIO_Pin_Num0_Flag)   //���Ը���E18_D80���������޸��β�����
{
	if(E18_D80_0==0)   //���ݹ���ʶ�������ĵ�ƽ�����趨   ����ʶ���ǵ͵�ƽ�����趨Ϊ0
	{
		delay_ms(10);
		if(E18_D80_0==0)
		*E18_D80_GPIO_Pin_Num0_Flag=1;
	}
	else
		*E18_D80_GPIO_Pin_Num0_Flag=0;
}
