#include "ASR01.h"



//���º�����ASR01ģ������š�ͨ�Žӿڳ�ʼ����������Ҫ���ڼ��Ͷ�Ӧ�����ĸ�

//��������ģ��Ĳ�����ͨ������Ϊ9600

/*********************************************
����ʶ��ģ��Ĵ�������ѡ���ĸ��������ڶ�Ӧ���ڵ�.c�ļ���
���䴮���ж�����ɴ�����  


�������ֱ��Ӧ��
void  ASR01_Uart1_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)

�ֱ���3������.c�ļ���
**********************************************/


void ASR01_Uart1_init(u32 *boun)
{
	Usart1_Init(*boun);
}

void ASR01_Uart2_init(u32 *boun)
{
	Usart2_Init(*boun);
}

void ASR01_Uart3_init(u32 *boun)
{
	Usart3_Init(*boun);
}

