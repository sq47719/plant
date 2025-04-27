#include "Zigbee.h"

/***************************************************************
����1����Zigbee������ݵķ�����غ���
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

void Zigbee_Uart1_Receive_Message(char *Tem_Parameter,char *Him_Parameter)  //�β��������ݴ�������ݸ��������޸�
{
	char Zigbee_Receive_Message_Buffer[8];
	Zigbee_Uart1_Receive_Data_Control(Zigbee_Receive_Message_Buffer);
	*Tem_Parameter=Zigbee_Receive_Message_Buffer[1];  //��1��ʼ����Ϊ��һ��Ԫ����'$'
	*Him_Parameter=Zigbee_Receive_Message_Buffer[2];
}

/***************************************************************
����2����Zigbee������ݵķ�����غ���
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

void Zigbee_Uart2_Receive_Message(char *Tem_Parameter,char *Him_Parameter)  //�β��������ݴ�������ݸ��������޸�
{
	char Zigbee_Receive_Message_Buffer[8];
	Zigbee_Uart2_Receive_Data_Control(Zigbee_Receive_Message_Buffer);
	*Tem_Parameter=Zigbee_Receive_Message_Buffer[1];  //��1��ʼ����Ϊ��һ��Ԫ����'$'
	*Him_Parameter=Zigbee_Receive_Message_Buffer[2];
}
/***************************************************************
����3����Zigbee������ݵķ�����غ���
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

void Zigbee_Uart3_Receive_Message(char *Tem_Parameter,char *Him_Parameter)  //�β��������ݴ�������ݸ��������޸�
{
	char Zigbee_Receive_Message_Buffer[8];
	Zigbee_Uart3_Receive_Data_Control(Zigbee_Receive_Message_Buffer);
	*Tem_Parameter=Zigbee_Receive_Message_Buffer[1];  //��1��ʼ����Ϊ��һ��Ԫ����'$'
	*Him_Parameter=Zigbee_Receive_Message_Buffer[2];
}

