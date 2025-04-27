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


//语音播报指令的格式为  "A8:02/00001*MP3"


void JR6001_Uart1_Handle(char *Instruct,_Bool Voice_Sppch_flag)
{
	if(Voice_Sppch_flag==1)
	UART1Write(Instruct);     //当整个系统只需要用一个串口，使用该函数进行字符串的发送需要在uart.c中，将fputc()函数的串口号修改一下
  delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart1_Voice_Add()
{
  UART1Write("B0");   //音量增加指令
	delay_ms(1000);
	delay_ms(1000);
	UART1Write("B0");
}


void JR6001_Uart2_Handle(char *Instruct,_Bool Voice_Sppch_flag)
{
//	if(Voice_Sppch_flag==1)
//	UART2Write(Instruct);     //当整个系统只需要用一个串口，使用该函数进行字符串的发送需要在uart.c中，将fputc()函数的串口号修改一下
//	delay_ms(1000);
//	delay_ms(1000);
	
	if(Voice_Sppch_flag==1)
	u2_printf(Instruct);  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart2_Voice_Add()
{
//  UART2Write("B0");   
//	delay_ms(1000);
//	delay_ms(1000);
	
	u2_printf("B0");  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
	u2_printf("B0");  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
	u2_printf("B0");  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart3_Handle(char *Instruct,_Bool Voice_Sppch_flag)
{
//	if(Voice_Sppch_flag==1)
//	UART3Write(Instruct);     //当整个系统只需要用一个串口，使用该函数进行字符串的发送需要在uart.c中，将fputc()函数的串口号修改一下
//	delay_ms(1000);
//	delay_ms(1000);
	if(Voice_Sppch_flag==1)
	u3_printf(Instruct);  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
}

void JR6001_Uart3_Voice_Add()
{
//  UART3Write("B0");     
//	delay_ms(1000);
//	delay_ms(1000);
	
	u3_printf("B0");  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
	u3_printf("B0");  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
	u3_printf("B0");  //当上面的发送函数使用之后，不需要修改fputc()函数，可以直接调用这个发送函数
	delay_ms(1000);
	delay_ms(1000);
}
