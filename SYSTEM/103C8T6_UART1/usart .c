#include "sys.h"
#include "usart.h"
#include "delay.h"
#include <string.h>	



u16  point1 = 0;
char USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
char Uart1_Zigee_Slave_Receive_Data_Buffer[USART_REC_LEN];
#if 1
#pragma import(__use_no_semihosting)             
            
struct __FILE    //标准库需要的支持函数   
{ 
	int handle; 

}; 

FILE __stdout;       
   
_sys_exit(int x)     //定义_sys_exit()以避免使用半主机模式 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)         //重定义fputc函数 
{      
	while((Usart_Num_3->SR&0X40)==0);    //循环发送,直到发送完毕      当使用一个串口的时候需要通过修改此处的串口号来进行对应   
	return ch;
}
#endif 

void UART1_SendByte(u16 Data)    //串口1发送单个字节 
{ 
   EXTI->IMR = 0x00000000;
   while (!(Usart_Num_1->SR & USART_FLAG_TXE));
   Usart_Num_1->DR = (Data & (uint16_t)0x01FF);	 
   EXTI->IMR = 0xfffff;
}


void UART1Write(char* data)      //串口1发送字符串 
{
	u16 i,len;
	len=strlen((char*)data);
	for (i=0; i<len; i++){
	UART1_SendByte(data[i]);
	}		
}


void UART1Write_Hex(char* data, int len)    //串口1发送HEX
{
	u16 i,len1;
	len1=len;
	for (i=0; i<len1; i++){
	UART1_SendByte(data[i]);
	}	
}

//通用串口发送字符串函数    通过选择串口选择哪个串口发送
void USART_SendString(USART_TypeDef* USARTx, char *DataString)
{
	int i = 0;
	USART_ClearFlag(USARTx,USART_FLAG_TC);								
	while(DataString[i] != '\0')										
	{
		USART_SendData(USARTx,DataString[i]);								
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);				
		USART_ClearFlag(USARTx,USART_FLAG_TC);									
		i++;
	}
}

void Uart_GPIO_Init()    //串口GPIO初始化
{
	 
    GPIO_InitTypeDef GPIO_InitStructure;      //GPIO端口设置
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart1_GPIO_Port,ENABLE);

    GPIO_InitStructure.GPIO_Pin = Uart1_GPIO_Pin_Num_TX;      	      //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(Uart1_GPIO_Port, &GPIO_InitStructure);   
	
	    
    GPIO_InitStructure.GPIO_Pin = Uart1_GPIO_Pin_Num_RX;             //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(Uart1_GPIO_Port, &GPIO_InitStructure);  
}

void Usart1_Usart_Init(u32 bound)   //串口1外设相关参数初始化
{
   
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart_USART1, ENABLE);
	  USART_DeInit(Usart_Num_1);  //复位串口1

   //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = Usart_Num_1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
	
   //USART 初始化设置
	  USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(Usart_Num_1, &USART_InitStructure);
    USART_ITConfig(Usart_Num_1, USART_IT_RXNE, ENABLE);//开启中断1	 
    USART_Cmd(Usart_Num_1, ENABLE);                    //使能串口 
}

void Usart1_Init(u32 bound)
{
	  Uart_GPIO_Init();
	  Usart1_Usart_Init(bound);
}

void  Usart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart1_Receive_Data_Buffer+i) = USART_RX_BUF[i];
	}  
}
//获取ZIgbee接收到的数据
void Zigbee_Uart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart1_Receive_Data_Buffer+i) = Uart1_Zigee_Slave_Receive_Data_Buffer[i];
	} 
}
/*************串口1通用中断处理函数*******

通用的串口1中断函数完成对数据的处理
后面定义的串口中断函数是专用模块的数据处理函数
***************************************/
//void USART1_IRQHandler()                	//串口1中断服务程序
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_1);         //(USART1->DR);	//读取接收到的数据
//	  USART_RX_BUF[point1++] = Res;
//		if(USART_RX_BUF[0]==0xC0)    //语音模块的唤醒指令
//		{
//			point1=0;
//		}
//	  if(point1 >= USART_REC_LEN)
//	  {
//		   point1 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntExit();  											 
//#endif
//}



/*************串口1用于接收GPS数据中断处理函数*******

通用的串口1中断函数完成对GPS数据的处理
调用该函数   当不接收GPS数据的时候需要屏蔽
***************************************/
//void USART1_IRQHandler()                	//串口1中断服务程序
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_1);         //(USART1->DR);	//读取接收到的数据
//		if(Res == '$')   //识别包头
//	  {
//		    point1 = 0;	
//	  }
//	  USART_RX_BUF[point1++] = Res;
//		
//		if(USART_RX_BUF[0] == '$' && USART_RX_BUF[4] == 'M' && USART_RX_BUF[5] == 'C')			//确定是否收到"GPRMC/GNRMC"这一帧数据
//		{
//			if(Res == '\n')									   
//			{
//				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
//				memcpy(Save_Data.GPS_Buffer, USART_RX_BUF, point1); 	//保存数据
//				Save_Data.isGetData = 1;
//				point1 = 0;
//				memset(USART_RX_BUF, 0, USART_REC_LEN);      //清空				
//			}	
//					
//		}
//	  if(point1 >= USART_REC_LEN)
//	  {
//		   point1 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntExit();  											 
//#endif
//}

/****************串口1颜色识别传感器TCS34725数据接收处理*************
通用的串口1中断函数完成对颜色识别TCS34725数据的处理
调用该函数   当不接收颜色识别数据的时候需要屏蔽
********************************************************************/
//void USART1_IRQHandler(void)
//{
//	static uint8_t i=0,Reg_buf[20]={0};
//	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET)   //判断接收标志
//	{
//		Reg_buf[i++]=USART_ReceiveData(Usart_Num_1);              //读取串口数据，同时清接收标志
//		if (Reg_buf[0]!=0x5a)                                //帧头不对
//			i=0;	
//		if ((i==2)&&(Reg_buf[1]!=0x5a))                      //帧头不对
//			i=0;
//	
//		if(i>3)                                             //i等于4时，已经接收到数据量字节rebuf[3]
//		{
//			if(i!=(Reg_buf[3]+5))                            //判断是否接收一帧数据完毕
//				return;	
//			switch(Reg_buf[2])                               //接收完毕后处理
//			{
//				case 0x45:
//					if(!TCS34725_Colour_Receive_Flag)            //当数据处理完成后才接收新的数据
//					{
//						memcpy(USART_RX_BUF,Reg_buf,8);            //拷贝接收到的数据
//						TCS34725_Colour_Receive_Flag=1;            //接收完成标志
//					}
//					break;
//				case 0x15:break;                               //原始数据接收，可模仿0x45的方式
//				case 0x35:break;
//			}
//			i=0;                                             //缓存清0
//		}
//	}
//		
//}

/****************串口1ZIGBEE数据接收处理*************
通用的串口1中断函数完成对Zigbee接收数据的处理
调用该函数   当不用ZIGBEE接收数据的时候需要屏蔽
********************************************************************/
void USART1_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET)   //判断接收标志
	{
		  Res=USART_ReceiveData(Usart_Num_1);              //读取串口数据，同时清接收标志
		if(Res == '$')   //识别包头
	  {
		    point1 = 0;	
	  }
	  USART_RX_BUF[point1++] = Res;
		
		if(USART_RX_BUF[0] == '$' )			//确定是否收到"$"
		{
			if(Res == '\n')									   
			{
				memset(Uart1_Zigee_Slave_Receive_Data_Buffer, 0, point1);             //清空
				memcpy(Uart1_Zigee_Slave_Receive_Data_Buffer, USART_RX_BUF, point1); 	//保存数据
				point1 = 0;
				memset(USART_RX_BUF, 0, USART_REC_LEN);      //清空				
			}	
					
		}
	  if(point1 >= USART_REC_LEN)
	  {
		   point1 = USART_REC_LEN;
	  }	                                         //缓存清0
		
	}
		
}

/******************************************************* m 
语音识别的处理函数  
形参的标志位个数可以根据实际项目进行增加和减少
注意将对应.h文件中的声明函数一并改了
********************************************************/
void  ASR01_Uart1_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
{
	  if(USART_RX_BUF[0] == 0xCC&&USART_RX_BUF[1] == 0x31)
		{
			*ASR01_Control_Led_On_Flag=1;
			*ASR01_Control_Led_Off_Flag=1;
			point1=0;
		}
		if(USART_RX_BUF[0] == 0xCC&&USART_RX_BUF[1] == 0x32)
		{
			*ASR01_Control_Led_Off_Flag=0;
			*ASR01_Control_Led_On_Flag=0;
			point1=0;
		}
		
}



u8 Hand(char *a)                   // 串口命令识别函数
{ 
    if(strstr(USART_RX_BUF,a)!=NULL)
	       return 1;
	  else
		     return 0;
}

void CLR_Buf(void)                           // 串口缓存清理
{
	memset(USART_RX_BUF, 0, USART_REC_LEN);      //清空
  point1 = 0;                    
}

/********************多个串口应用串口2用以下发送函数形式****
u2_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS)   其中  SSID和PASS是两个字符串
*********************************************************/

__align(8) char USART1_TX_BUF[USART1_MAX_SEND_LEN];  

void u1_printf(char* fmt,...)                   //需要多个串口进行数据发送需要用以下函数   单一串口的时候可以通过修改uart.c文件中的fputc中的串口号实现
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART1_TX_BUF);		//计算数组长度
	for(j=0;j<i;j++)							//循环发送
	{
	  while(USART_GetFlagStatus(Usart_Num_1,USART_FLAG_TC)==RESET); //循环发送
		USART_SendData(Usart_Num_1,USART1_TX_BUF[j]); 
	} 
}


/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印   在ESP8266中使用
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}

