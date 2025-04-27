#include "sys.h"
#include "usart.h"
#include "delay.h"
#include <string.h>	



u16  point1 = 0;
char USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
char Uart1_Zigee_Slave_Receive_Data_Buffer[USART_REC_LEN];
#if 1
#pragma import(__use_no_semihosting)             
            
struct __FILE    //��׼����Ҫ��֧�ֺ���   
{ 
	int handle; 

}; 

FILE __stdout;       
   
_sys_exit(int x)     //����_sys_exit()�Ա���ʹ�ð�����ģʽ 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)         //�ض���fputc���� 
{      
	while((Usart_Num_3->SR&0X40)==0);    //ѭ������,ֱ���������      ��ʹ��һ�����ڵ�ʱ����Ҫͨ���޸Ĵ˴��Ĵ��ں������ж�Ӧ   
	return ch;
}
#endif 

void UART1_SendByte(u16 Data)    //����1���͵����ֽ� 
{ 
   EXTI->IMR = 0x00000000;
   while (!(Usart_Num_1->SR & USART_FLAG_TXE));
   Usart_Num_1->DR = (Data & (uint16_t)0x01FF);	 
   EXTI->IMR = 0xfffff;
}


void UART1Write(char* data)      //����1�����ַ��� 
{
	u16 i,len;
	len=strlen((char*)data);
	for (i=0; i<len; i++){
	UART1_SendByte(data[i]);
	}		
}


void UART1Write_Hex(char* data, int len)    //����1����HEX
{
	u16 i,len1;
	len1=len;
	for (i=0; i<len1; i++){
	UART1_SendByte(data[i]);
	}	
}

//ͨ�ô��ڷ����ַ�������    ͨ��ѡ�񴮿�ѡ���ĸ����ڷ���
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

void Uart_GPIO_Init()    //����GPIO��ʼ��
{
	 
    GPIO_InitTypeDef GPIO_InitStructure;      //GPIO�˿�����
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart1_GPIO_Port,ENABLE);

    GPIO_InitStructure.GPIO_Pin = Uart1_GPIO_Pin_Num_TX;      	      //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(Uart1_GPIO_Port, &GPIO_InitStructure);   
	
	    
    GPIO_InitStructure.GPIO_Pin = Uart1_GPIO_Pin_Num_RX;             //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(Uart1_GPIO_Port, &GPIO_InitStructure);  
}

void Usart1_Usart_Init(u32 bound)   //����1������ز�����ʼ��
{
   
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart_USART1, ENABLE);
	  USART_DeInit(Usart_Num_1);  //��λ����1

   //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = Usart_Num_1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
	
   //USART ��ʼ������
	  USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(Usart_Num_1, &USART_InitStructure);
    USART_ITConfig(Usart_Num_1, USART_IT_RXNE, ENABLE);//�����ж�1	 
    USART_Cmd(Usart_Num_1, ENABLE);                    //ʹ�ܴ��� 
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
//��ȡZIgbee���յ�������
void Zigbee_Uart1_Receive_Data_Control(char *Uart1_Receive_Data_Buffer)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart1_Receive_Data_Buffer+i) = Uart1_Zigee_Slave_Receive_Data_Buffer[i];
	} 
}
/*************����1ͨ���жϴ�����*******

ͨ�õĴ���1�жϺ�����ɶ����ݵĴ���
���涨��Ĵ����жϺ�����ר��ģ������ݴ�����
***************************************/
//void USART1_IRQHandler()                	//����1�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_1);         //(USART1->DR);	//��ȡ���յ�������
//	  USART_RX_BUF[point1++] = Res;
//		if(USART_RX_BUF[0]==0xC0)    //����ģ��Ļ���ָ��
//		{
//			point1=0;
//		}
//	  if(point1 >= USART_REC_LEN)
//	  {
//		   point1 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}



/*************����1���ڽ���GPS�����жϴ�����*******

ͨ�õĴ���1�жϺ�����ɶ�GPS���ݵĴ���
���øú���   ��������GPS���ݵ�ʱ����Ҫ����
***************************************/
//void USART1_IRQHandler()                	//����1�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_1);         //(USART1->DR);	//��ȡ���յ�������
//		if(Res == '$')   //ʶ���ͷ
//	  {
//		    point1 = 0;	
//	  }
//	  USART_RX_BUF[point1++] = Res;
//		
//		if(USART_RX_BUF[0] == '$' && USART_RX_BUF[4] == 'M' && USART_RX_BUF[5] == 'C')			//ȷ���Ƿ��յ�"GPRMC/GNRMC"��һ֡����
//		{
//			if(Res == '\n')									   
//			{
//				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //���
//				memcpy(Save_Data.GPS_Buffer, USART_RX_BUF, point1); 	//��������
//				Save_Data.isGetData = 1;
//				point1 = 0;
//				memset(USART_RX_BUF, 0, USART_REC_LEN);      //���				
//			}	
//					
//		}
//	  if(point1 >= USART_REC_LEN)
//	  {
//		   point1 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}

/****************����1��ɫʶ�𴫸���TCS34725���ݽ��մ���*************
ͨ�õĴ���1�жϺ�����ɶ���ɫʶ��TCS34725���ݵĴ���
���øú���   ����������ɫʶ�����ݵ�ʱ����Ҫ����
********************************************************************/
//void USART1_IRQHandler(void)
//{
//	static uint8_t i=0,Reg_buf[20]={0};
//	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET)   //�жϽ��ձ�־
//	{
//		Reg_buf[i++]=USART_ReceiveData(Usart_Num_1);              //��ȡ�������ݣ�ͬʱ����ձ�־
//		if (Reg_buf[0]!=0x5a)                                //֡ͷ����
//			i=0;	
//		if ((i==2)&&(Reg_buf[1]!=0x5a))                      //֡ͷ����
//			i=0;
//	
//		if(i>3)                                             //i����4ʱ���Ѿ����յ��������ֽ�rebuf[3]
//		{
//			if(i!=(Reg_buf[3]+5))                            //�ж��Ƿ����һ֡�������
//				return;	
//			switch(Reg_buf[2])                               //������Ϻ���
//			{
//				case 0x45:
//					if(!TCS34725_Colour_Receive_Flag)            //�����ݴ�����ɺ�Ž����µ�����
//					{
//						memcpy(USART_RX_BUF,Reg_buf,8);            //�������յ�������
//						TCS34725_Colour_Receive_Flag=1;            //������ɱ�־
//					}
//					break;
//				case 0x15:break;                               //ԭʼ���ݽ��գ���ģ��0x45�ķ�ʽ
//				case 0x35:break;
//			}
//			i=0;                                             //������0
//		}
//	}
//		
//}

/****************����1ZIGBEE���ݽ��մ���*************
ͨ�õĴ���1�жϺ�����ɶ�Zigbee�������ݵĴ���
���øú���   ������ZIGBEE�������ݵ�ʱ����Ҫ����
********************************************************************/
void USART1_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(Usart_Num_1, USART_IT_RXNE) != RESET)   //�жϽ��ձ�־
	{
		  Res=USART_ReceiveData(Usart_Num_1);              //��ȡ�������ݣ�ͬʱ����ձ�־
		if(Res == '$')   //ʶ���ͷ
	  {
		    point1 = 0;	
	  }
	  USART_RX_BUF[point1++] = Res;
		
		if(USART_RX_BUF[0] == '$' )			//ȷ���Ƿ��յ�"$"
		{
			if(Res == '\n')									   
			{
				memset(Uart1_Zigee_Slave_Receive_Data_Buffer, 0, point1);             //���
				memcpy(Uart1_Zigee_Slave_Receive_Data_Buffer, USART_RX_BUF, point1); 	//��������
				point1 = 0;
				memset(USART_RX_BUF, 0, USART_REC_LEN);      //���				
			}	
					
		}
	  if(point1 >= USART_REC_LEN)
	  {
		   point1 = USART_REC_LEN;
	  }	                                         //������0
		
	}
		
}

/******************************************************* m 
����ʶ��Ĵ�����  
�βεı�־λ�������Ը���ʵ����Ŀ�������Ӻͼ���
ע�⽫��Ӧ.h�ļ��е���������һ������
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



u8 Hand(char *a)                   // ��������ʶ����
{ 
    if(strstr(USART_RX_BUF,a)!=NULL)
	       return 1;
	  else
		     return 0;
}

void CLR_Buf(void)                           // ���ڻ�������
{
	memset(USART_RX_BUF, 0, USART_REC_LEN);      //���
  point1 = 0;                    
}

/********************�������Ӧ�ô���2�����·��ͺ�����ʽ****
u2_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS)   ����  SSID��PASS�������ַ���
*********************************************************/

__align(8) char USART1_TX_BUF[USART1_MAX_SEND_LEN];  

void u1_printf(char* fmt,...)                   //��Ҫ������ڽ������ݷ�����Ҫ�����º���   ��һ���ڵ�ʱ�����ͨ���޸�uart.c�ļ��е�fputc�еĴ��ں�ʵ��
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART1_TX_BUF);		//�������鳤��
	for(j=0;j<i;j++)							//ѭ������
	{
	  while(USART_GetFlagStatus(Usart_Num_1,USART_FLAG_TC)==RESET); //ѭ������
		USART_SendData(Usart_Num_1,USART1_TX_BUF[j]); 
	} 
}


/*
************************************************************
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ   ��ESP8266��ʹ��
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}

