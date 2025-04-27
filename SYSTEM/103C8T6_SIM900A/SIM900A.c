#include "SIM900A.h"




/*****************************************************
����1��ɶ�GSM�Ŀ���
********************************************************/
void Sim900A_GSM_Uart1_start_trans(void)
{
	USART_SendString(Usart_Num_1, "AT\r\n");
	delay_ms(1000);
  USART_SendString(Usart_Num_1, "AT+CMGD=1\r\n");//�رջ��� 
	delay_ms(1000);
	USART_SendString(Usart_Num_1, "AT+CSCS=\"GSM\"\r\n");
	delay_ms(1000);
	USART_SendString(Usart_Num_1, "AT+CMGF=1\r\n");
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
}


void Sim900A_Uart1_Init()
{
	Usart1_Init(9600);
}

void Sim900A_GSM_Uart1_Send_Message()
{
	
	char Tel_Bffer[24]="AT+CMGS=\"17735159752\"\r\n";
	char Police_Bffer[8]="Fire";
	
	Sim900A_GSM_Uart1_start_trans();
	USART_SendString(Usart_Num_1,Tel_Bffer);
	delay_ms(1000);
	delay_ms(1000);
	USART_SendString(Usart_Num_1,Police_Bffer);
	USART_SendData(Usart_Num_1,0X0D );
	delay_ms(1000);
	USART_SendData(Usart_Num_1,0X0A );
	delay_ms(1000);
	USART_SendData(Usart_Num_1,0X1A );
	delay_ms(1000);
	USART_SendData(Usart_Num_1,0X0D );
	delay_ms(1000);
	USART_SendData(Usart_Num_1,0X0A );
	while( USART_GetFlagStatus(Usart_Num_1, USART_FLAG_TXE) == RESET );
	USART_ReceiveData(Usart_Num_1);
	delay_ms(1);
	
}

/*****************************************************
����2��ɶ�GSM�Ŀ���
********************************************************/
void Sim900A_GSM_Uart2_start_trans(void)
{
	USART_SendString(Usart_Num_2, "AT\r\n");
	delay_ms(1000);
  USART_SendString(Usart_Num_2, "AT+CMGD=1\r\n");//�رջ��� 
	delay_ms(1000);
	USART_SendString(Usart_Num_2, "AT+CSCS=\"GSM\"\r\n");
	delay_ms(1000);
	USART_SendString(Usart_Num_2, "AT+CMGF=1\r\n");
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
}


void Sim900A_Uart2_Init()
{
	Usart2_Init(9600);
}

void Sim900A_GSM_Uart2_Send_Message()
{
	
	char Tel_Bffer[24]="AT+CMGS=\"17735159752\"\r\n";
	char Police_Bffer[8]="Fire";
	
	Sim900A_GSM_Uart2_start_trans();
	USART_SendString(Usart_Num_2,Tel_Bffer);
	delay_ms(1000);
	delay_ms(1000);
	USART_SendString(Usart_Num_2,Police_Bffer);
	USART_SendData(Usart_Num_2,0X0D );
	delay_ms(1000);
	USART_SendData(Usart_Num_2,0X0A );
	delay_ms(1000);
	USART_SendData(Usart_Num_2,0X1A );
	delay_ms(1000);
	USART_SendData(Usart_Num_2,0X0D );
	delay_ms(1000);
	USART_SendData(Usart_Num_2,0X0A );
	while( USART_GetFlagStatus(Usart_Num_2, USART_FLAG_TXE) == RESET );
	USART_ReceiveData(Usart_Num_2);
	delay_ms(1);
	
}


/*****************************************************
����3��ɶ�GSM�Ŀ���
********************************************************/
void Sim900A_GSM_Uart3_start_trans(void)
{
	USART_SendString(Usart_Num_3, "AT\r\n");
	delay_ms(1000);
  USART_SendString(Usart_Num_3, "AT+CMGD=1\r\n");//�رջ��� 
	delay_ms(1000);
	USART_SendString(Usart_Num_3, "AT+CSCS=\"GSM\"\r\n");
	delay_ms(1000);
	USART_SendString(Usart_Num_3, "AT+CMGF=1\r\n");
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
}


void Sim900A_Uart3_Init()
{
	Usart3_Init(9600);
}

void Sim900A_GSM_Uart3_Send_Message()
{
	
	char Tel_Bffer[24]="AT+CMGS=\"17735159752\"\r\n";
	char Police_Bffer[8]="Fire";
	
	Sim900A_GSM_Uart3_start_trans();
	USART_SendString(Usart_Num_3,Tel_Bffer);
	delay_ms(1000);
	delay_ms(1000);
	USART_SendString(Usart_Num_3,Police_Bffer);
	USART_SendData(Usart_Num_3,0X0D );
	delay_ms(1000);
	USART_SendData(Usart_Num_3,0X0A );
	delay_ms(1000);
	USART_SendData(Usart_Num_3,0X1A );
	delay_ms(1000);
	USART_SendData(Usart_Num_3,0X0D );
	delay_ms(1000);
	USART_SendData(Usart_Num_3,0X0A );
	while( USART_GetFlagStatus(Usart_Num_3, USART_FLAG_TXE) == RESET );
	USART_ReceiveData(Usart_Num_3);
	delay_ms(1);
	
}

