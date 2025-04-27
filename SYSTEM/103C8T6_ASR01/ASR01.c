#include "ASR01.h"



//以下函数是ASR01模块的引脚、通信接口初始化函数，需要串口几就对应调用哪个

//语音播报模块的波特率通常配置为9600

/*********************************************
语音识别模块的处理函数，选择哪个串口则在对应串口的.c文件中
在其串口中断中完成处理功能  


处理函数分别对应：
void  ASR01_Uart1_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)

分别在3个串口.c文件中
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

