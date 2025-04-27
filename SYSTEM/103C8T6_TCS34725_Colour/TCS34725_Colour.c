#include "TCS34725_Colour.h"


/**************************************************
ʹ�ô���1��ɶ�TCS34725ģ����ƶ�Ӧ�ĺ�����ʼ��
*****************************************************/
_Bool TCS34725_Colour_Receive_Flag=0;
RGB TCS34725_Colour_rgb={0,0,0};// ���ڴ��RGB����

//����1���Ͷ��ֽ�����+У��͸���ɫʶ�𴫸���
void TCS34725_Colour_Uart1_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//�ۼ�Length-1ǰ������
		UART1_SendByte(Buffer[i++]);
	}
}
//����1����ָ�����ɫʶ�𴫸���
void TCS34725_Colour_Uart1_Send_Com(u16 data)
{
		u8 bytes[3]={0};
	  bytes[0]=0xa5;
	  bytes[1]=data;//�����ֽ�
	  TCS34725_Colour_Uart1_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}

//����1����TCS34725��ʼ��
void TCS34725_Colour_Uart1_Init()
{
	Usart1_Init(9600);
	TCS34725_Colour_Uart1_Send_Com(0x01);//���Ͷ�RGBָ��
}

//����1�жϽ��յ����ݺ� ������
/*******************************************************
����ɫʶ������ȡ��Ӧ��RGB����
Ȼ�󽫴���1�жϽ��յ���RGB���������º����н��д���
�����ж�RGBֵ�������ɫ��־λ�����Ը�����ɫ�����������º������β����������޸�
**********************************************************/
void TCS34725_Colour_Uart1_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag) //�βε�����������Ҫʶ�����ɫ������������
{
	u8 sum=0,TCS34725_Colour_Receive_Num;
	static char TCS34725_Colour_Receive_Data_Buffer[8]={0};
	
	if(TCS34725_Colour_Receive_Flag)  //���ڽ�����ϱ�־
	{
		Usart1_Receive_Data_Control(TCS34725_Colour_Receive_Data_Buffer);  //������1�жϽ��յ������ݶ�ȡ���д���
		
		for(TCS34725_Colour_Receive_Num=0;TCS34725_Colour_Receive_Num<(TCS34725_Colour_Receive_Data_Buffer[3]+4);TCS34725_Colour_Receive_Num++)//rgb_data[3]=3
			sum+=TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num];
			if(sum==TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num])//У����ж�
			{
				TCS34725_Colour_rgb.Red=TCS34725_Colour_Receive_Data_Buffer[4];
				TCS34725_Colour_rgb.Green=TCS34725_Colour_Receive_Data_Buffer[5];
				TCS34725_Colour_rgb.Blue=TCS34725_Colour_Receive_Data_Buffer[6];
			}
			if(TCS34725_Colour_rgb.Blue>TCS34725_Colour_rgb.Green&&TCS34725_Colour_rgb.Green>TCS34725_Colour_rgb.Red&&TCS34725_Colour_rgb.Red>30&&TCS34725_Colour_rgb.Blue>90)
			{
				*Colour_Num0_Flag=1;  //��ɫʶ�𵽡���ɫ��־��
			}
		  if(TCS34725_Colour_rgb.Blue>250&&TCS34725_Colour_rgb.Green>250&&TCS34725_Colour_rgb.Red>250)
			{
				*Colour_Num1_Flag=1;  //��ɫʶ�𵽡���ɫ��־��
				delay_ms(10);
			}
			TCS34725_Colour_Receive_Flag=0;//����������ϱ�־
	}
}

/**************************************************
ʹ�ô���2��ɶ�TCS34725ģ����ƶ�Ӧ�ĺ�����ʼ��
*****************************************************/

//����2���Ͷ��ֽ�����+У��͸���ɫʶ�𴫸���
void TCS34725_Colour_Uart2_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//�ۼ�Length-1ǰ������
		UART2_SendByte(Buffer[i++]);
	}
}
//����2����ָ�����ɫʶ�𴫸���
void TCS34725_Colour_Uart2_Send_Com(u16 data)
{
		u8 bytes[3]={0};
	  bytes[0]=0xa5;
	  bytes[1]=data;//�����ֽ�
	  TCS34725_Colour_Uart2_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}

//����2����TCS34725��ʼ��
void TCS34725_Colour_Uart2_Init()
{
	Usart2_Init(9600);
	TCS34725_Colour_Uart2_Send_Com(0x01);//���Ͷ�RGBָ��
}

//����2�жϽ��յ����ݺ� ������
/*******************************************************
����ɫʶ������ȡ��Ӧ��RGB����
Ȼ�󽫴���2�жϽ��յ���RGB���������º����н��д���
�����ж�RGBֵ�������ɫ��־λ�����Ը�����ɫ�����������º������β����������޸�
**********************************************************/
void TCS34725_Colour_Uart2_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag) //�βε�����������Ҫʶ�����ɫ������������
{
	u8 sum=0,TCS34725_Colour_Receive_Num;
	char TCS34725_Colour_Receive_Data_Buffer[8]={0};
	
	if(TCS34725_Colour_Receive_Flag)  //���ڽ�����ϱ�־
	{
		Usart2_Receive_Data_Control(TCS34725_Colour_Receive_Data_Buffer);  //������1�жϽ��յ������ݶ�ȡ���д���
		
		for(TCS34725_Colour_Receive_Num=0;TCS34725_Colour_Receive_Num<(TCS34725_Colour_Receive_Data_Buffer[3]+4);TCS34725_Colour_Receive_Num++)//rgb_data[3]=3
			sum+=TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num];
			if(sum==TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num])//У����ж�
			{
				TCS34725_Colour_rgb.Red=TCS34725_Colour_Receive_Data_Buffer[4];
				TCS34725_Colour_rgb.Green=TCS34725_Colour_Receive_Data_Buffer[5];
				TCS34725_Colour_rgb.Blue=TCS34725_Colour_Receive_Data_Buffer[6];
			}
			if(TCS34725_Colour_rgb.Blue>TCS34725_Colour_rgb.Green&&TCS34725_Colour_rgb.Green>TCS34725_Colour_rgb.Red&&TCS34725_Colour_rgb.Red>30&&TCS34725_Colour_rgb.Blue>90)
			{
				*Colour_Num0_Flag=1;  //��ɫʶ�𵽡���ɫ��־��
			}
		  if(TCS34725_Colour_rgb.Blue>250&&TCS34725_Colour_rgb.Green>250&&TCS34725_Colour_rgb.Red>250)
			{
				*Colour_Num1_Flag=1;  //��ɫʶ�𵽡���ɫ��־��
			}
			TCS34725_Colour_Receive_Flag=0;//����������ϱ�־
	}
}

/**************************************************
ʹ�ô���3��ɶ�TCS34725ģ����ƶ�Ӧ�ĺ�����ʼ��
*****************************************************/
//����3���Ͷ��ֽ�����+У��͸���ɫʶ�𴫸���
void TCS34725_Colour_Uart3_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//�ۼ�Length-1ǰ������
		UART3_SendByte(Buffer[i++]);
	}
}
//����3����ָ�����ɫʶ�𴫸���
void TCS34725_Colour_Uart3_Send_Com(u16 data)
{
		u8 bytes[3]={0};
	  bytes[0]=0xa5;
	  bytes[1]=data;//�����ֽ�
	  TCS34725_Colour_Uart3_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}
//����3����TCS34725��ʼ��
void TCS34725_Colour_Uart3_Init()
{
	Usart3_Init(9600);
	TCS34725_Colour_Uart3_Send_Com(0x01);//���Ͷ�RGBָ��
}

//����3�жϽ��յ����ݺ� ������
/*******************************************************
����ɫʶ������ȡ��Ӧ��RGB����
Ȼ�󽫴���3�жϽ��յ���RGB���������º����н��д���
�����ж�RGBֵ�������ɫ��־λ�����Ը�����ɫ�����������º������β����������޸�
**********************************************************/
void TCS34725_Colour_Uart3_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag) //�βε�����������Ҫʶ�����ɫ������������
{
	u8 sum=0,TCS34725_Colour_Receive_Num;
	char TCS34725_Colour_Receive_Data_Buffer[8]={0};
	
	if(TCS34725_Colour_Receive_Flag)  //���ڽ�����ϱ�־
	{
		Usart3_Receive_Data_Control(TCS34725_Colour_Receive_Data_Buffer);  //������1�жϽ��յ������ݶ�ȡ���д���
		
		for(TCS34725_Colour_Receive_Num=0;TCS34725_Colour_Receive_Num<(TCS34725_Colour_Receive_Data_Buffer[3]+4);TCS34725_Colour_Receive_Num++)//rgb_data[3]=3
			sum+=TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num];
			if(sum==TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num])//У����ж�
			{
				TCS34725_Colour_rgb.Red=TCS34725_Colour_Receive_Data_Buffer[4];
				TCS34725_Colour_rgb.Green=TCS34725_Colour_Receive_Data_Buffer[5];
				TCS34725_Colour_rgb.Blue=TCS34725_Colour_Receive_Data_Buffer[6];
			}
			if(TCS34725_Colour_rgb.Blue>TCS34725_Colour_rgb.Green&&TCS34725_Colour_rgb.Green>TCS34725_Colour_rgb.Red&&TCS34725_Colour_rgb.Red>30&&TCS34725_Colour_rgb.Blue>90)
			{
				*Colour_Num0_Flag=1;  //��ɫʶ�𵽡���ɫ��־��
			}
		  if(TCS34725_Colour_rgb.Blue>250&&TCS34725_Colour_rgb.Green>250&&TCS34725_Colour_rgb.Red>250)
			{
				*Colour_Num1_Flag=1;  //��ɫʶ�𵽡���ɫ��־��
			}
			TCS34725_Colour_Receive_Flag=0;//����������ϱ�־
	}
}
