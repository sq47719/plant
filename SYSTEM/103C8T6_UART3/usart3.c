#include "delay.h"
#include "usart3.h"

	

u16  point3 = 0;
char USART3_RX_BUF[USART_REC_LEN];                     //���ջ���,���USART_REC_LEN���ֽ�.
char Uart3_Zigee_Slave_Receive_Data_Buffer[USART_REC_LEN];
//#if 1
//#pragma import(__use_no_semihosting)             
//            
//struct __FILE    //��׼����Ҫ��֧�ֺ���   
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
//   
//_sys_exit(int x)     //����_sys_exit()�Ա���ʹ�ð�����ģʽ 
//{ 
//	x = x; 
//} 

//int fputc(int ch, FILE *f)         //�ض���fputc���� 
//{      
//	while((Usart_Num_1->SR&0X40)==0);    //ѭ������,ֱ���������      ��ʹ��һ�����ڵ�ʱ����Ҫͨ���޸Ĵ˴��Ĵ��ں������ж�Ӧ     ��uart.c�ļ����޸�
//	return ch;
//}
//#endif 

void UART3_SendByte(u16 Data)    //����3���͵����ֽ� 
{ 
   EXTI->IMR = 0x00000000;
   while (!(Usart_Num_3->SR & USART_FLAG_TXE));
   Usart_Num_3->DR = (Data & (uint16_t)0x01FF);	 
   EXTI->IMR = 0xfffff;
}


void UART3Write(char* data)      //����3�����ַ��� 
{
	u16 i,len;
	len=strlen((char*)data);
	for (i=0; i<len; i++){
	UART3_SendByte(data[i]);
	}		
}

void UART3Write_Hex(char* data, int len)    //����1����HEX
{
	u16 i,len1;
	len1=len;
	for (i=0; i<len1; i++){
	UART3_SendByte(data[i]);
	}	
}

void Uart3_GPIO_Init()    //����GPIO��ʼ��
{
	 
    GPIO_InitTypeDef GPIO_InitStructure;      //GPIO�˿�����
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart3_GPIO_Port,ENABLE);

    GPIO_InitStructure.GPIO_Pin = Uart3_GPIO_Pin_Num_TX;      	    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(Uart3_GPIO_Port, &GPIO_InitStructure);   
	
	    
    GPIO_InitStructure.GPIO_Pin = Uart3_GPIO_Pin_Num_RX;            
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(Uart3_GPIO_Port, &GPIO_InitStructure);  
}

void Usart3_Usart_Init(u32 bound)   //����3������ز�����ʼ��
{
   
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef  NVIC_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_Usart_USART3,ENABLE); //����3ʱ��ʹ��
	  USART_DeInit(Usart_Num_3);                                  //��λ����3
	
		//Uart3  NVIC����
	  NVIC_InitStructure.NVIC_IRQChannel = Usart_Num_3_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;             //��ռ���ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		               //�����ȼ�3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			                 //IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	                                     //����ָ���Ĳ�����ʼ��VIC�Ĵ�
	
	  USART_InitStructure.USART_BaudRate = bound;                          //������һ������Ϊ9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;          //�ֳ�Ϊ8λ���ݸ�ʽ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;               //һ��ֹͣλ
	  USART_InitStructure.USART_Parity = USART_Parity_No;                  //����żУ��λ
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	    //�շ�ģʽ
  
	  USART_Init(Usart_Num_3, &USART_InitStructure);                      //��ʼ������	3
	  USART_ITConfig(Usart_Num_3, USART_IT_RXNE, ENABLE);                 //�����ж�   
		USART_Cmd(Usart_Num_3, ENABLE);                                     //ʹ�ܴ��� 
}

void Usart3_Init(u32 bound)
{
	  Uart3_GPIO_Init();
	  Usart3_Usart_Init(bound);
}

void  Usart3_Receive_Data_Control(char *Uart3_Receive_Data_Buffer)
{
		u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart3_Receive_Data_Buffer+i) = USART3_RX_BUF[i];
	}  
}
//��ȡZIgbee���յ�������
void Zigbee_Uart3_Receive_Data_Control(char *Uart3_Receive_Data_Buffer)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart3_Receive_Data_Buffer+i) = Uart3_Zigee_Slave_Receive_Data_Buffer[i];
	} 
}
/*************����3ͨ���жϴ�����*******

ͨ�õĴ���3�жϺ�����ɶ����ݵĴ���
���涨��Ĵ����жϺ�����ר��ģ������ݴ�����

�Զ���Ĺ������������Ĺ���
***************************************/
//void USART3_IRQHandler()                	//����1�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_3, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_3);         //(USART1->DR);	//��ȡ���յ�������
//	  USART3_RX_BUF[point3++] = Res;
//		if(USART3_RX_BUF[0]==0xC0)  //����ģ��Ļ���ָ��
//		{
//			point3=0;
//		}
//	  if(point3 >= USART_REC_LEN)
//	  {
//		   point3 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}

/*************����3���ڽ���GPS�����жϴ�����*******

ͨ�õĴ���3�жϺ�����ɶ�GPS���ݵĴ���
���øú���   ��������GPS���ݵ�ʱ����Ҫ����
***************************************/
//void USART3_IRQHandler()                	//����3�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_3, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_3);         //(USART1->DR);	//��ȡ���յ�������
//		if(Res == '$')   //ʶ���ͷ
//	  {
//		    point3 = 0;	
//	  }
//	  USART3_RX_BUF[point3++] = Res;
//		
//		if(USART3_RX_BUF[0] == '$' && USART3_RX_BUF[4] == 'M' && USART3_RX_BUF[5] == 'C')			
//		{
//			if(Res == '\n')									   
//			{
//				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //���
//				memcpy(Save_Data.GPS_Buffer, USART3_RX_BUF, point3); 	//��������
//				Save_Data.isGetData = 1;
//				point3 = 0;
//				memset(USART3_RX_BUF, 0, USART_REC_LEN);      //���				
//			}	
//					
//		}
//	  if(point3 >= USART_REC_LEN)
//	  {
//		   point3 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}

/****************����3��ɫʶ�𴫸���TCS34725���ݽ��մ���*************
ͨ�õĴ���3�жϺ�����ɶ���ɫʶ��TCS34725���ݵĴ���
���øú���   ����������ɫʶ�����ݵ�ʱ����Ҫ����
********************************************************************/
//void USART3_IRQHandler(void)
//{
//	static uint8_t i=0,Reg_buf[20]={0};
//	if(USART_GetITStatus(Usart_Num_3, USART_IT_RXNE) != RESET)   //�жϽ��ձ�־
//	{
//		Reg_buf[i++]=USART_ReceiveData(Usart_Num_3);              //��ȡ�������ݣ�ͬʱ����ձ�־
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
//						memcpy(USART3_RX_BUF,Reg_buf,8);            //�������յ�������
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

/****************����3ZIGBEE���ݽ��մ���*************
ͨ�õĴ���3�жϺ�����ɶ�Zigbee�������ݵĴ���
���øú���   ������ZIGBEE�������ݵ�ʱ����Ҫ����
********************************************************************/
void USART3_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(Usart_Num_3, USART_IT_RXNE) != RESET)   //�жϽ��ձ�־
	{
		  Res=USART_ReceiveData(Usart_Num_3);              //��ȡ�������ݣ�ͬʱ����ձ�־
		if(Res == '$')   //ʶ���ͷ
	  {
		    point3 = 0;	
	  }
	  USART3_RX_BUF[point3++] = Res;
		
		if(USART3_RX_BUF[0] == '$' )			//ȷ���Ƿ��յ�"$"
		{
			if(Res == '\n')									   
			{
				memset(Uart3_Zigee_Slave_Receive_Data_Buffer, 0, point3);             //���
				memcpy(Uart3_Zigee_Slave_Receive_Data_Buffer, USART3_RX_BUF, point3); 	//��������
				point3 = 0;
				memset(USART3_RX_BUF, 0, USART_REC_LEN);      //���				
			}	
					
		}
	  if(point3 >= USART_REC_LEN)
	  {
		   point3 = USART_REC_LEN;
	  }	                                         //������0
		
	}
		
}
/******************************************************* m 
����ʶ��Ĵ�����  
�βεı�־λ�������Ը���ʵ����Ŀ�������Ӻͼ���
ע�⽫��Ӧ.h�ļ��е���������һ������
********************************************************/
void  ASR01_Uart3_Handle(_Bool *ASR01_Control_Led_On_Flag,_Bool *ASR01_Control_Led_Off_Flag)
{
	  if(USART3_RX_BUF[0] == 0xCC&&USART3_RX_BUF[1] == 0x31)
		{
			*ASR01_Control_Led_On_Flag=1;
			*ASR01_Control_Led_Off_Flag=1;
			point3=0;
		}
		if(USART3_RX_BUF[0] == 0xCC&&USART3_RX_BUF[1] == 0x32)
		{
			*ASR01_Control_Led_On_Flag=0;
			*ASR01_Control_Led_Off_Flag=0;
			point3=0;
		}
		
}
u8 Hand_Uart3(char *a)                   // ��������ʶ����
{ 
    if(strstr(USART3_RX_BUF,a)!=NULL)
	       return 1;
	  else
		     return 0;
}

void CLR_Uart3_Buf(void)                           // ���ڻ�������
{
	memset(USART3_RX_BUF, 0, USART_REC_LEN);      //���
  point3 = 0;                    
}

/********************�������Ӧ�ô���3�����·��ͺ�����ʽ****
u3_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS)   ����  SSID��PASS�������ַ���
*********************************************************/

__align(8) char USART3_TX_BUF[USART3_MAX_SEND_LEN];  
void u3_printf(char* fmt,...)                   //��Ҫ������ڽ������ݷ�����Ҫ�����º���   ��һ���ڵ�ʱ�����ͨ���޸�uart.c�ļ��е�fputc�еĴ��ں�ʵ��
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�������鳤��
	for(j=0;j<i;j++)							//ѭ������
	{
	  while(USART_GetFlagStatus(Usart_Num_3,USART_FLAG_TC)==RESET); //ѭ������
		USART_SendData(Usart_Num_3,USART3_TX_BUF[j]); 
	} 
}



 



















