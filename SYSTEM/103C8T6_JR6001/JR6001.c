#include "JR6001.h"



void JR6001_Uart1_init(u32 *boun)
{
		Usart1_Init(*boun);
}

void JR6001_Uart2_init(u32 *boun)
{
	 Usart2_Init(*boun);
}

void JR6001_Uart3_init(u32 *boun)
{ 
	 Usart3_Init(*boun);
}


//��������ָ��ĸ�ʽΪ  "A8:02/00001*MP3"


void JR6001_Uart1_Handle(char *Instruct,_Bool Voice_Sppch_flag)
{
	if(Voice_Sppch_flag==1)
	UART1Write(Instruct);     //������ϵͳֻ��Ҫ��һ�����ڣ�ʹ�øú��������ַ����ķ�����Ҫ��uart.c�У���fputc()�����Ĵ��ں��޸�һ��
  delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart1_Voice_Add()
{
  UART1Write("B0");   //��������ָ��
	delay_ms(1000);
	delay_ms(1000);
	UART1Write("B0");
}


void JR6001_Uart2_Handle(char *Instruct,_Bool Voice_Sppch_flag)
{
//	if(Voice_Sppch_flag==1)
//	UART2Write(Instruct);     //������ϵͳֻ��Ҫ��һ�����ڣ�ʹ�øú��������ַ����ķ�����Ҫ��uart.c�У���fputc()�����Ĵ��ں��޸�һ��
//	delay_ms(1000);
//	delay_ms(1000);
	
	if(Voice_Sppch_flag==1)
	u2_printf(Instruct);  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart2_Voice_Add()
{
//  UART2Write("B0");   
//	delay_ms(1000);
//	delay_ms(1000);
	
	u2_printf("B0");  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
	u2_printf("B0");  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
	u2_printf("B0");  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart3_Handle(char *Instruct,_Bool Voice_Sppch_flag)
{
//	if(Voice_Sppch_flag==1)
//	UART3Write(Instruct);     //������ϵͳֻ��Ҫ��һ�����ڣ�ʹ�øú��������ַ����ķ�����Ҫ��uart.c�У���fputc()�����Ĵ��ں��޸�һ��
//	delay_ms(1000);
//	delay_ms(1000);
	if(Voice_Sppch_flag==1)
	u3_printf(Instruct);  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart3_Voice_Add()
{
//  UART3Write("B0");     
//	delay_ms(1000);
//	delay_ms(1000);
	
	u3_printf("B0");  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
	u3_printf("B0");  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
	u3_printf("B0");  //������ķ��ͺ���ʹ��֮�󣬲���Ҫ�޸�fputc()����������ֱ�ӵ���������ͺ���
	delay_ms(1000);
	delay_ms(1000);
}
