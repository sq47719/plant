#include "TCS34725_Colour.h"


/**************************************************
使用串口1完成对TCS34725模块控制对应的函数初始化
*****************************************************/
_Bool TCS34725_Colour_Receive_Flag=0;
RGB TCS34725_Colour_rgb={0,0,0};// 用于存放RGB数据

//串口1发送多字节数据+校验和给颜色识别传感器
void TCS34725_Colour_Uart1_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//累加Length-1前的数据
		UART1_SendByte(Buffer[i++]);
	}
}
//串口1发送指令给颜色识别传感器
void TCS34725_Colour_Uart1_Send_Com(u16 data)
{
		u8 bytes[3]={0};
	  bytes[0]=0xa5;
	  bytes[1]=data;//功能字节
	  TCS34725_Colour_Uart1_Send(bytes,3);//发送帧头、功能字节、校验和
}

//串口1控制TCS34725初始化
void TCS34725_Colour_Uart1_Init()
{
	Usart1_Init(9600);
	TCS34725_Colour_Uart1_Send_Com(0x01);//发送读RGB指令
}

//串口1中断接收到数据后 处理函数
/*******************************************************
当颜色识别完后读取对应的RGB数据
然后将串口1中断接收到的RGB数据在以下函数中进行处理
根据判断RGB值，输出颜色标志位，可以根据颜色的数量对以下函数的形参数量进行修改
**********************************************************/
void TCS34725_Colour_Uart1_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag) //形参的数量根据需要识别的颜色数量进行休整
{
	u8 sum=0,TCS34725_Colour_Receive_Num;
	static char TCS34725_Colour_Receive_Data_Buffer[8]={0};
	
	if(TCS34725_Colour_Receive_Flag)  //串口接收完毕标志
	{
		Usart1_Receive_Data_Control(TCS34725_Colour_Receive_Data_Buffer);  //将串口1中断接收到的数据读取进行处理
		
		for(TCS34725_Colour_Receive_Num=0;TCS34725_Colour_Receive_Num<(TCS34725_Colour_Receive_Data_Buffer[3]+4);TCS34725_Colour_Receive_Num++)//rgb_data[3]=3
			sum+=TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num];
			if(sum==TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num])//校验和判断
			{
				TCS34725_Colour_rgb.Red=TCS34725_Colour_Receive_Data_Buffer[4];
				TCS34725_Colour_rgb.Green=TCS34725_Colour_Receive_Data_Buffer[5];
				TCS34725_Colour_rgb.Blue=TCS34725_Colour_Receive_Data_Buffer[6];
			}
			if(TCS34725_Colour_rgb.Blue>TCS34725_Colour_rgb.Green&&TCS34725_Colour_rgb.Green>TCS34725_Colour_rgb.Red&&TCS34725_Colour_rgb.Red>30&&TCS34725_Colour_rgb.Blue>90)
			{
				*Colour_Num0_Flag=1;  //颜色识别到“蓝色标志”
			}
		  if(TCS34725_Colour_rgb.Blue>250&&TCS34725_Colour_rgb.Green>250&&TCS34725_Colour_rgb.Red>250)
			{
				*Colour_Num1_Flag=1;  //颜色识别到“白色标志”
				delay_ms(10);
			}
			TCS34725_Colour_Receive_Flag=0;//处理数据完毕标志
	}
}

/**************************************************
使用串口2完成对TCS34725模块控制对应的函数初始化
*****************************************************/

//串口2发送多字节数据+校验和给颜色识别传感器
void TCS34725_Colour_Uart2_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//累加Length-1前的数据
		UART2_SendByte(Buffer[i++]);
	}
}
//串口2发送指令给颜色识别传感器
void TCS34725_Colour_Uart2_Send_Com(u16 data)
{
		u8 bytes[3]={0};
	  bytes[0]=0xa5;
	  bytes[1]=data;//功能字节
	  TCS34725_Colour_Uart2_Send(bytes,3);//发送帧头、功能字节、校验和
}

//串口2控制TCS34725初始化
void TCS34725_Colour_Uart2_Init()
{
	Usart2_Init(9600);
	TCS34725_Colour_Uart2_Send_Com(0x01);//发送读RGB指令
}

//串口2中断接收到数据后 处理函数
/*******************************************************
当颜色识别完后读取对应的RGB数据
然后将串口2中断接收到的RGB数据在以下函数中进行处理
根据判断RGB值，输出颜色标志位，可以根据颜色的数量对以下函数的形参数量进行修改
**********************************************************/
void TCS34725_Colour_Uart2_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag) //形参的数量根据需要识别的颜色数量进行休整
{
	u8 sum=0,TCS34725_Colour_Receive_Num;
	char TCS34725_Colour_Receive_Data_Buffer[8]={0};
	
	if(TCS34725_Colour_Receive_Flag)  //串口接收完毕标志
	{
		Usart2_Receive_Data_Control(TCS34725_Colour_Receive_Data_Buffer);  //将串口1中断接收到的数据读取进行处理
		
		for(TCS34725_Colour_Receive_Num=0;TCS34725_Colour_Receive_Num<(TCS34725_Colour_Receive_Data_Buffer[3]+4);TCS34725_Colour_Receive_Num++)//rgb_data[3]=3
			sum+=TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num];
			if(sum==TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num])//校验和判断
			{
				TCS34725_Colour_rgb.Red=TCS34725_Colour_Receive_Data_Buffer[4];
				TCS34725_Colour_rgb.Green=TCS34725_Colour_Receive_Data_Buffer[5];
				TCS34725_Colour_rgb.Blue=TCS34725_Colour_Receive_Data_Buffer[6];
			}
			if(TCS34725_Colour_rgb.Blue>TCS34725_Colour_rgb.Green&&TCS34725_Colour_rgb.Green>TCS34725_Colour_rgb.Red&&TCS34725_Colour_rgb.Red>30&&TCS34725_Colour_rgb.Blue>90)
			{
				*Colour_Num0_Flag=1;  //颜色识别到“蓝色标志”
			}
		  if(TCS34725_Colour_rgb.Blue>250&&TCS34725_Colour_rgb.Green>250&&TCS34725_Colour_rgb.Red>250)
			{
				*Colour_Num1_Flag=1;  //颜色识别到“白色标志”
			}
			TCS34725_Colour_Receive_Flag=0;//处理数据完毕标志
	}
}

/**************************************************
使用串口3完成对TCS34725模块控制对应的函数初始化
*****************************************************/
//串口3发送多字节数据+校验和给颜色识别传感器
void TCS34725_Colour_Uart3_Send(uint8_t *Buffer, uint8_t Length)
{
	uint8_t i=0;
	while(i<Length)
	{
		if(i<(Length-1))
		Buffer[Length-1]+=Buffer[i];//累加Length-1前的数据
		UART3_SendByte(Buffer[i++]);
	}
}
//串口3发送指令给颜色识别传感器
void TCS34725_Colour_Uart3_Send_Com(u16 data)
{
		u8 bytes[3]={0};
	  bytes[0]=0xa5;
	  bytes[1]=data;//功能字节
	  TCS34725_Colour_Uart3_Send(bytes,3);//发送帧头、功能字节、校验和
}
//串口3控制TCS34725初始化
void TCS34725_Colour_Uart3_Init()
{
	Usart3_Init(9600);
	TCS34725_Colour_Uart3_Send_Com(0x01);//发送读RGB指令
}

//串口3中断接收到数据后 处理函数
/*******************************************************
当颜色识别完后读取对应的RGB数据
然后将串口3中断接收到的RGB数据在以下函数中进行处理
根据判断RGB值，输出颜色标志位，可以根据颜色的数量对以下函数的形参数量进行修改
**********************************************************/
void TCS34725_Colour_Uart3_Rgb_Handle(_Bool *Colour_Num0_Flag,_Bool *Colour_Num1_Flag) //形参的数量根据需要识别的颜色数量进行休整
{
	u8 sum=0,TCS34725_Colour_Receive_Num;
	char TCS34725_Colour_Receive_Data_Buffer[8]={0};
	
	if(TCS34725_Colour_Receive_Flag)  //串口接收完毕标志
	{
		Usart3_Receive_Data_Control(TCS34725_Colour_Receive_Data_Buffer);  //将串口1中断接收到的数据读取进行处理
		
		for(TCS34725_Colour_Receive_Num=0;TCS34725_Colour_Receive_Num<(TCS34725_Colour_Receive_Data_Buffer[3]+4);TCS34725_Colour_Receive_Num++)//rgb_data[3]=3
			sum+=TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num];
			if(sum==TCS34725_Colour_Receive_Data_Buffer[TCS34725_Colour_Receive_Num])//校验和判断
			{
				TCS34725_Colour_rgb.Red=TCS34725_Colour_Receive_Data_Buffer[4];
				TCS34725_Colour_rgb.Green=TCS34725_Colour_Receive_Data_Buffer[5];
				TCS34725_Colour_rgb.Blue=TCS34725_Colour_Receive_Data_Buffer[6];
			}
			if(TCS34725_Colour_rgb.Blue>TCS34725_Colour_rgb.Green&&TCS34725_Colour_rgb.Green>TCS34725_Colour_rgb.Red&&TCS34725_Colour_rgb.Red>30&&TCS34725_Colour_rgb.Blue>90)
			{
				*Colour_Num0_Flag=1;  //颜色识别到“蓝色标志”
			}
		  if(TCS34725_Colour_rgb.Blue>250&&TCS34725_Colour_rgb.Green>250&&TCS34725_Colour_rgb.Red>250)
			{
				*Colour_Num1_Flag=1;  //颜色识别到“白色标志”
			}
			TCS34725_Colour_Receive_Flag=0;//处理数据完毕标志
	}
}
