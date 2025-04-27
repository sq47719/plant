#include "Zigbee.h"

/***************************************************************
串口1控制Zigbee完成数据的发送相关函数
******************************************************************/
void Zigbee_Uart1_Init()
{
	Usart1_Init(9600);
}

void Zigbee_Uart1_Host_Send_Message(char *Message_Buffer)
{
    USART_SendString(Usart_Num_1,Message_Buffer);
	  delay_ms(50);
}

void Zigbee_Uart1_Receive_Message(char *Tem_Parameter,char *Him_Parameter)  //形参数量根据传输的数据个数进行修改
{
	char Zigbee_Receive_Message_Buffer[8];
	Zigbee_Uart1_Receive_Data_Control(Zigbee_Receive_Message_Buffer);
	*Tem_Parameter=Zigbee_Receive_Message_Buffer[1];  //从1开始是因为第一个元素是'$'
	*Him_Parameter=Zigbee_Receive_Message_Buffer[2];
}

/***************************************************************
串口2控制Zigbee完成数据的发送相关函数
******************************************************************/
void Zigbee_Uart2_Init()
{
	Usart2_Init(9600);
}

void Zigbee_Uart2_Host_Send_Message(char *Message_Buffer)
{
    USART_SendString(Usart_Num_2,Message_Buffer);
	  delay_ms(50);
}

void Zigbee_Uart2_Receive_Message(char *Tem_Parameter,char *Him_Parameter)  //形参数量根据传输的数据个数进行修改
{
	char Zigbee_Receive_Message_Buffer[8];
	Zigbee_Uart2_Receive_Data_Control(Zigbee_Receive_Message_Buffer);
	*Tem_Parameter=Zigbee_Receive_Message_Buffer[1];  //从1开始是因为第一个元素是'$'
	*Him_Parameter=Zigbee_Receive_Message_Buffer[2];
}
/***************************************************************
串口3控制Zigbee完成数据的发送相关函数
******************************************************************/
void Zigbee_Uart3_Init()
{
	Usart3_Init(9600);
}

void Zigbee_Uart3_Host_Send_Message(char *Message_Buffer)
{
    USART_SendString(Usart_Num_3,Message_Buffer);
	  delay_ms(50);
}

void Zigbee_Uart3_Receive_Message(char *Tem_Parameter,char *Him_Parameter)  //形参数量根据传输的数据个数进行修改
{
	char Zigbee_Receive_Message_Buffer[8];
	Zigbee_Uart3_Receive_Data_Control(Zigbee_Receive_Message_Buffer);
	*Tem_Parameter=Zigbee_Receive_Message_Buffer[1];  //从1开始是因为第一个元素是'$'
	*Him_Parameter=Zigbee_Receive_Message_Buffer[2];
}

