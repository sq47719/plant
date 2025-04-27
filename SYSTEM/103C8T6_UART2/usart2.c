#include "stm32f10x.h"  //包含需要的头文件
#include "usart2.h"     //包含需要的头文件



u16  point2 = 0;
char USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
char Uart2_Zigee_Slave_Receive_Data_Buffer[USART_REC_LEN];


//以下两个变量是ESP8266使用
unsigned char esp8266_buf[512];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0; 


//#if 1
//#pragma import(__use_no_semihosting)             
//            
//struct __FILE    //标准库需要的支持函数   
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
//   
//_sys_exit(int x)     //定义_sys_exit()以避免使用半主机模式 
//{ 
//	x = x; 
//} 

//int fputc(int ch, FILE *f)         //重定义fputc函数 
//{      
//	while((Usart_Num_1->SR&0X40)==0);    //循环发送,直到发送完毕      当使用一个串口的时候需要通过修改此处的串口号来进行对应     在(（uart.c）)文件中修改
//	return ch;
//}
//#endif 

void UART2_SendByte(u16 Data)    //串口2发送单个字节 
{ 
   EXTI->IMR = 0x00000000;
   while (!(Usart_Num_2->SR & USART_FLAG_TXE));
   Usart_Num_2->DR = (Data & (uint16_t)0x01FF);	 
   EXTI->IMR = 0xfffff;
}

void UART2Write(char* data)      //串口2发送字符串 
{
	u16 i,len;
	len=strlen((char*)data);
	for (i=0; i<len; i++){
	UART2_SendByte(data[i]);
	}		
}

void UART2Write_Hex(char* data, int len)    //串口1发送HEX
{
	u16 i,len1;
	len1=len;
	for (i=0; i<len1; i++){
	UART2_SendByte(data[i]);
	}	
}

/*-------------------------------------------------*/
/*函数名：初始化串口2GPIO                        */
/*返回值：无                                        */
/*-------------------------------------------------*/

void Uart2_GPIO_Init()    //串口GPIO初始化
{
	   GPIO_InitTypeDef GPIO_InitStructure;     //定义一个设置GPIO功能的变量
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart2_GPIO_Port, ENABLE);  //使能GPIOA时钟
	
	   GPIO_InitStructure.GPIO_Pin = Uart2_GPIO_Pin_Num_TX;              //准备设置PA2
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 //IO速率50M
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                //复用推挽输出，用于串口2的发送
     GPIO_Init(Uart2_GPIO_Port, &GPIO_InitStructure);                 //设置GPIO
   
     GPIO_InitStructure.GPIO_Pin = Uart2_GPIO_Pin_Num_RX;              //准备设置PA3
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             //浮空输入，用于串口2的接收
     GPIO_Init(Uart2_GPIO_Port, &GPIO_InitStructure);                  //设置GPIO
}



/*-------------------------------------------------*/
/*函数名：初始化串口2发送功能                        */
/*参  数：bound：波特率                             */
/*返回值：无                                        */
/*-------------------------------------------------*/
void Usart2_Usart_Init(unsigned int bound)
{  	 	
 
	USART_InitTypeDef USART_InitStructure;   //定义一个设置串口功能的变量
	NVIC_InitTypeDef NVIC_InitStructure;     //如果使能接收功能，定义一个设置中断的变量

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Usart_USART2, ENABLE); //使能串口2时钟
	USART_DeInit(Usart_Num_2);                                  //串口2寄存器重新设置为默认值
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3	
  
	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = Usart_Num_2_IRQn;         //设置串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		        //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			          //中断通道使能
	NVIC_Init(&NVIC_InitStructure);	                              //设置串口2中断     
	
  //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //8个数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //收发模式 
  USART_Init(Usart_Num_2, &USART_InitStructure);                                      //设置串口2	

	USART_ClearFlag(Usart_Num_2, USART_FLAG_RXNE);	              //清除接收标志位
	USART_ITConfig(Usart_Num_2, USART_IT_RXNE, ENABLE);            //开启接收中断
	USART_Cmd(Usart_Num_2, ENABLE);                                //使能串口2
}

void Usart2_Init(u32 bound)
{
	  Uart2_GPIO_Init();
	  Usart2_Usart_Init(bound);
}

void  Usart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer)
{
		u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart2_Receive_Data_Buffer+i) = USART2_RX_BUF[i];
	}   
}
//获取ZIgbee接收到的数据
void Zigbee_Uart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart2_Receive_Data_Buffer+i) = Uart2_Zigee_Slave_Receive_Data_Buffer[i];
	} 
}
/*************串口2通用中断处理函数*******

通用的串口2中断函数完成对数据的处理
后面定义的串口中断函数是专用模块的数据处理函数
***************************************/
//void USART2_IRQHandler()                	//串口2中断服务程序
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART1->DR);	//读取接收到的数据
//	  USART2_RX_BUF[point2++] = Res;

//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntExit();  											 
//#endif
//}

/*************串口2语音控制中断处理函数*******

串口2中断函数完成对语音控制数据的处理
该串口中断函数是语音控制模块的数据处理函数   不需要语音控制的时候屏蔽
***************************************/
//void USART2_IRQHandler()                	//串口2中断服务程序
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART1->DR);	//读取接收到的数据
//	  USART2_RX_BUF[point2++] = Res;
//		if(USART2_RX_BUF[0]==0xC0)  //语音模块的唤醒指令
//		{
//			point2=0;
//		}
//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntExit();  											 
//#endif
//}
/*************串口2用于接收GPS数据中断处理函数*******

通用的串口2中断函数完成对GPS数据的处理
调用该函数   当不接收GPS数据的时候需要屏蔽
***************************************/
//void USART2_IRQHandler()                	//串口2中断服务程序
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART2->DR);	//读取接收到的数据
//		if(Res == '$')   //识别包头
//	  {
//		    point2 = 0;	
//	  }
//	  USART2_RX_BUF[point2++] = Res;
//		
//		if(USART2_RX_BUF[0] == '$' && USART2_RX_BUF[4] == 'M' && USART2_RX_BUF[5] == 'C')			
//		{
//			if(Res == '\n')									   
//			{
//				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
//				memcpy(Save_Data.GPS_Buffer, USART2_RX_BUF, point2); 	//保存数据
//				Save_Data.isGetData = 1;
//				point2 = 0;
//				memset(USART2_RX_BUF, 0, USART_REC_LEN);      //清空				
//			}	
//					
//		}
//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
//	OSIntExit();  											 
//#endif
//}

/****************串口2颜色识别传感器TCS34725数据接收处理*************
通用的串口2中断函数完成对颜色识别TCS34725数据的处理
调用该函数   当不接收颜色识别数据的时候需要屏蔽
********************************************************************/
//void USART2_IRQHandler(void)
//{
//	static uint8_t i=0,Reg_buf[20]={0};
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET)   //判断接收标志
//	{
//		Reg_buf[i++]=USART_ReceiveData(Usart_Num_2);              //读取串口数据，同时清接收标志
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
//						memcpy(USART2_RX_BUF,Reg_buf,8);            //拷贝接收到的数据
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

/****************串口2ZIGBEE数据接收处理*************
通用的串口2中断函数完成对Zigbee接收数据的处理
调用该函数   当不用ZIGBEE接收数据的时候需要屏蔽
********************************************************************/
//void USART2_IRQHandler(void)
//{
//	u8 Res;
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET)   //判断接收标志
//	{
//		  Res=USART_ReceiveData(Usart_Num_2);              //读取串口数据，同时清接收标志
//		if(Res == '$')   //识别包头
//	  {
//		    point2 = 0;	
//	  }
//	  USART2_RX_BUF[point2++] = Res;
//		
//		if(USART2_RX_BUF[0] == '$' )			//确定是否收到"$"
//		{
//			if(Res == '\n')									   
//			{
//				memset(Uart2_Zigee_Slave_Receive_Data_Buffer, 0, point2);             //清空
//				memcpy(Uart2_Zigee_Slave_Receive_Data_Buffer, USART2_RX_BUF, point2); 	//保存数据
//				point2 = 0;
//				memset(USART2_RX_BUF, 0, USART_REC_LEN);      //清空				
//			}	
//					
//		}
//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }	                                         //缓存清0
//		
//	}
//		
//}

/****************串口2ESP8266  onenet数据接收处理*************
通用的串口2中断函数完成对ESP8266数据的处理
调用该函数   当不接收ESP8266数据的时候需要屏蔽
********************************************************************/

//void USART2_IRQHandler(void)
//{
//		u8 Res;

//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//		if(esp8266_cnt >= sizeof(esp8266_buf))	
//			esp8266_cnt = 0; //防止串口被刷爆
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART1->DR);	//读取接收到的数据
//	  esp8266_buf[esp8266_cnt++] = Res;	
//    USART_ClearFlag(USART2, USART_FLAG_RXNE);		
//  } 
//}

/****************串口2ESP8266 阿里云 数据接收处理*************
通用的串口2中断函数完成对ESP8266数据的处理
调用该函数   当不接收ESP8266数据的时候需要屏蔽
********************************************************************/
void USART2_IRQHandler(void)   
{                      
	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET)    //如果USART_IT_RXNE标志置位，表示有数据到了，进入if分支
	{  
		if(connectFlag == 0) 							     //如果connectFlag等于0，当前还没有连接服务器，处于指令配置状态
		{                                     
			if(Usart_Num_2->DR)
			{                                     			 //处于指令配置状态时，非零值才保存到缓冲区	
				USART2_RX_BUF[point2] = Usart_Num_2->DR;//保存到缓冲区	
				point2++; 						 //每接收1个字节的数据，Usart2_RxCounter加1，表示接收的数据总量+1 
			}					
		}
		else
		{		                                           	 //反之connectFlag等于1，连接上服务器了	
			USART2_RX_BUF[point2] = Usart_Num_2->DR;    //把接收到的数据保存到Usart2_RxBuff中				
			if(point2 == 0)
			{    									    											 //如果Usart2_RxCounter等于0，表示是接收的第1个数据，进入if分支				
				TIM_Cmd(Timer_Tim4, ENABLE); 
			}
			else																						 //else分支，表示果Usart2_RxCounter不等于0，不是接收的第一个数据
			{                        									    
				TIM_SetCounter(Timer_Tim4, 0);  
			}	
			point2++;         				     //每接收1个字节的数据，Usart2_RxCounter加1，表示接收的数据总量+1 
		}
	}
} 



/******************************************************* m 
语音识别的处理函数  
形参的标志位个数可以根据实际项目进行增加和减少
注意将对应.h文件中的声明函数一并改了
********************************************************/
void  ASR01_Uart2_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
{
	  if(USART2_RX_BUF[0] == 0xCC&&USART2_RX_BUF[1] == 0x31)
		{
			*ASR01_Control_Led_On_Flag=1;
			*ASR01_Control_Led_Off_Flag=1;
			point2=0;
		}
		if(USART2_RX_BUF[0] == 0xCC&&USART2_RX_BUF[1] == 0x32)
		{
			*ASR01_Control_Led_On_Flag=0;
			*ASR01_Control_Led_Off_Flag=0;
			point2=0;
		}
		
}

u8 Hand_Uart2(char *a)                   // 串口命令识别函数
{ 
    if(strstr(USART2_RX_BUF,a)!=NULL)
	       return 1;
	  else
		     return 0;
}

void CLR_Uart2_Buf(void)                           // 串口缓存清理
{
	memset(USART2_RX_BUF, 0, USART_REC_LEN);      //清空
  point2 = 0;                    
}


/********************多个串口应用串口2用以下发送函数形式****
u2_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS)   其中  SSID和PASS是两个字符串
*********************************************************/

__align(8) char USART2_TX_BUF[USART2_MAX_SEND_LEN];  
void u2_printf(char* fmt,...)                   //需要多个串口进行数据发送需要用以下函数   单一串口的时候可以通过修改uart.c文件中的fputc中的串口号实现
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//计算数组长度
	for(j=0;j<i;j++)							//循环发送
	{
	  while(USART_GetFlagStatus(Usart_Num_2,USART_FLAG_TC)==RESET); //循环发送
		USART_SendData(Usart_Num_2,USART2_TX_BUF[j]); 
	} 
}

/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送   在ESP8266无线模块控制中使用
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}


/*-------------------------------------------------*/
/*函数名：串口2发送缓冲区中的数据                    */
/*参  数：data：数据                                */
/*返回值：无
该函数是在阿里云   数据发送时候用
-------------------------------------------------*/
void u2_TxData(unsigned char *data)
{
	int	i;	
	while((Usart_Num_2->SR&0X40) == 0);
	for(i = 1; i <= (data[0] * 256 + data[1]); i++)
	{			
		Usart_Num_2->DR = data[i+1];
		while((Usart_Num_2->SR&0X40) == 0);	
	}
}


