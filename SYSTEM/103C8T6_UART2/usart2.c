#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "usart2.h"     //������Ҫ��ͷ�ļ�



u16  point2 = 0;
char USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
char Uart2_Zigee_Slave_Receive_Data_Buffer[USART_REC_LEN];


//��������������ESP8266ʹ��
unsigned char esp8266_buf[512];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0; 


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
//	while((Usart_Num_1->SR&0X40)==0);    //ѭ������,ֱ���������      ��ʹ��һ�����ڵ�ʱ����Ҫͨ���޸Ĵ˴��Ĵ��ں������ж�Ӧ     ��(��uart.c��)�ļ����޸�
//	return ch;
//}
//#endif 

void UART2_SendByte(u16 Data)    //����2���͵����ֽ� 
{ 
   EXTI->IMR = 0x00000000;
   while (!(Usart_Num_2->SR & USART_FLAG_TXE));
   Usart_Num_2->DR = (Data & (uint16_t)0x01FF);	 
   EXTI->IMR = 0xfffff;
}

void UART2Write(char* data)      //����2�����ַ��� 
{
	u16 i,len;
	len=strlen((char*)data);
	for (i=0; i<len; i++){
	UART2_SendByte(data[i]);
	}		
}

void UART2Write_Hex(char* data, int len)    //����1����HEX
{
	u16 i,len1;
	len1=len;
	for (i=0; i<len1; i++){
	UART2_SendByte(data[i]);
	}	
}

/*-------------------------------------------------*/
/*����������ʼ������2GPIO                        */
/*����ֵ����                                        */
/*-------------------------------------------------*/

void Uart2_GPIO_Init()    //����GPIO��ʼ��
{
	   GPIO_InitTypeDef GPIO_InitStructure;     //����һ������GPIO���ܵı���
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usart2_GPIO_Port, ENABLE);  //ʹ��GPIOAʱ��
	
	   GPIO_InitStructure.GPIO_Pin = Uart2_GPIO_Pin_Num_TX;              //׼������PA2
	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 //IO����50M
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                //����������������ڴ���2�ķ���
     GPIO_Init(Uart2_GPIO_Port, &GPIO_InitStructure);                 //����GPIO
   
     GPIO_InitStructure.GPIO_Pin = Uart2_GPIO_Pin_Num_RX;              //׼������PA3
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             //�������룬���ڴ���2�Ľ���
     GPIO_Init(Uart2_GPIO_Port, &GPIO_InitStructure);                  //����GPIO
}



/*-------------------------------------------------*/
/*����������ʼ������2���͹���                        */
/*��  ����bound��������                             */
/*����ֵ����                                        */
/*-------------------------------------------------*/
void Usart2_Usart_Init(unsigned int bound)
{  	 	
 
	USART_InitTypeDef USART_InitStructure;   //����һ�����ô��ڹ��ܵı���
	NVIC_InitTypeDef NVIC_InitStructure;     //���ʹ�ܽ��չ��ܣ�����һ�������жϵı���

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Usart_USART2, ENABLE); //ʹ�ܴ���2ʱ��
	USART_DeInit(Usart_Num_2);                                  //����2�Ĵ�����������ΪĬ��ֵ
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3	
  
	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = Usart_Num_2_IRQn;         //���ô���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		        //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			          //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                              //���ô���2�ж�     
	
  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;                                    //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //8������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //�շ�ģʽ 
  USART_Init(Usart_Num_2, &USART_InitStructure);                                      //���ô���2	

	USART_ClearFlag(Usart_Num_2, USART_FLAG_RXNE);	              //������ձ�־λ
	USART_ITConfig(Usart_Num_2, USART_IT_RXNE, ENABLE);            //���������ж�
	USART_Cmd(Usart_Num_2, ENABLE);                                //ʹ�ܴ���2
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
//��ȡZIgbee���յ�������
void Zigbee_Uart2_Receive_Data_Control(char *Uart2_Receive_Data_Buffer)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		*(Uart2_Receive_Data_Buffer+i) = Uart2_Zigee_Slave_Receive_Data_Buffer[i];
	} 
}
/*************����2ͨ���жϴ�����*******

ͨ�õĴ���2�жϺ�����ɶ����ݵĴ���
���涨��Ĵ����жϺ�����ר��ģ������ݴ�����
***************************************/
//void USART2_IRQHandler()                	//����2�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART1->DR);	//��ȡ���յ�������
//	  USART2_RX_BUF[point2++] = Res;

//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}

/*************����2���������жϴ�����*******

����2�жϺ�����ɶ������������ݵĴ���
�ô����жϺ�������������ģ������ݴ�����   ����Ҫ�������Ƶ�ʱ������
***************************************/
//void USART2_IRQHandler()                	//����2�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART1->DR);	//��ȡ���յ�������
//	  USART2_RX_BUF[point2++] = Res;
//		if(USART2_RX_BUF[0]==0xC0)  //����ģ��Ļ���ָ��
//		{
//			point2=0;
//		}
//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}
/*************����2���ڽ���GPS�����жϴ�����*******

ͨ�õĴ���2�жϺ�����ɶ�GPS���ݵĴ���
���øú���   ��������GPS���ݵ�ʱ����Ҫ����
***************************************/
//void USART2_IRQHandler()                	//����2�жϷ������
//{
//	u8 Res;
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART2->DR);	//��ȡ���յ�������
//		if(Res == '$')   //ʶ���ͷ
//	  {
//		    point2 = 0;	
//	  }
//	  USART2_RX_BUF[point2++] = Res;
//		
//		if(USART2_RX_BUF[0] == '$' && USART2_RX_BUF[4] == 'M' && USART2_RX_BUF[5] == 'C')			
//		{
//			if(Res == '\n')									   
//			{
//				memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //���
//				memcpy(Save_Data.GPS_Buffer, USART2_RX_BUF, point2); 	//��������
//				Save_Data.isGetData = 1;
//				point2 = 0;
//				memset(USART2_RX_BUF, 0, USART_REC_LEN);      //���				
//			}	
//					
//		}
//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }			 
//  } 
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();  											 
//#endif
//}

/****************����2��ɫʶ�𴫸���TCS34725���ݽ��մ���*************
ͨ�õĴ���2�жϺ�����ɶ���ɫʶ��TCS34725���ݵĴ���
���øú���   ����������ɫʶ�����ݵ�ʱ����Ҫ����
********************************************************************/
//void USART2_IRQHandler(void)
//{
//	static uint8_t i=0,Reg_buf[20]={0};
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET)   //�жϽ��ձ�־
//	{
//		Reg_buf[i++]=USART_ReceiveData(Usart_Num_2);              //��ȡ�������ݣ�ͬʱ����ձ�־
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
//						memcpy(USART2_RX_BUF,Reg_buf,8);            //�������յ�������
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

/****************����2ZIGBEE���ݽ��մ���*************
ͨ�õĴ���2�жϺ�����ɶ�Zigbee�������ݵĴ���
���øú���   ������ZIGBEE�������ݵ�ʱ����Ҫ����
********************************************************************/
//void USART2_IRQHandler(void)
//{
//	u8 Res;
//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET)   //�жϽ��ձ�־
//	{
//		  Res=USART_ReceiveData(Usart_Num_2);              //��ȡ�������ݣ�ͬʱ����ձ�־
//		if(Res == '$')   //ʶ���ͷ
//	  {
//		    point2 = 0;	
//	  }
//	  USART2_RX_BUF[point2++] = Res;
//		
//		if(USART2_RX_BUF[0] == '$' )			//ȷ���Ƿ��յ�"$"
//		{
//			if(Res == '\n')									   
//			{
//				memset(Uart2_Zigee_Slave_Receive_Data_Buffer, 0, point2);             //���
//				memcpy(Uart2_Zigee_Slave_Receive_Data_Buffer, USART2_RX_BUF, point2); 	//��������
//				point2 = 0;
//				memset(USART2_RX_BUF, 0, USART_REC_LEN);      //���				
//			}	
//					
//		}
//	  if(point2 >= USART_REC_LEN)
//	  {
//		   point2 = USART_REC_LEN;
//	  }	                                         //������0
//		
//	}
//		
//}

/****************����2ESP8266  onenet���ݽ��մ���*************
ͨ�õĴ���2�жϺ�����ɶ�ESP8266���ݵĴ���
���øú���   ��������ESP8266���ݵ�ʱ����Ҫ����
********************************************************************/

//void USART2_IRQHandler(void)
//{
//		u8 Res;

//	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET) 
//	{
//		if(esp8266_cnt >= sizeof(esp8266_buf))	
//			esp8266_cnt = 0; //��ֹ���ڱ�ˢ��
//	  Res =USART_ReceiveData(Usart_Num_2);         //(USART1->DR);	//��ȡ���յ�������
//	  esp8266_buf[esp8266_cnt++] = Res;	
//    USART_ClearFlag(USART2, USART_FLAG_RXNE);		
//  } 
//}

/****************����2ESP8266 ������ ���ݽ��մ���*************
ͨ�õĴ���2�жϺ�����ɶ�ESP8266���ݵĴ���
���øú���   ��������ESP8266���ݵ�ʱ����Ҫ����
********************************************************************/
void USART2_IRQHandler(void)   
{                      
	if(USART_GetITStatus(Usart_Num_2, USART_IT_RXNE) != RESET)    //���USART_IT_RXNE��־��λ����ʾ�����ݵ��ˣ�����if��֧
	{  
		if(connectFlag == 0) 							     //���connectFlag����0����ǰ��û�����ӷ�����������ָ������״̬
		{                                     
			if(Usart_Num_2->DR)
			{                                     			 //����ָ������״̬ʱ������ֵ�ű��浽������	
				USART2_RX_BUF[point2] = Usart_Num_2->DR;//���浽������	
				point2++; 						 //ÿ����1���ֽڵ����ݣ�Usart2_RxCounter��1����ʾ���յ���������+1 
			}					
		}
		else
		{		                                           	 //��֮connectFlag����1�������Ϸ�������	
			USART2_RX_BUF[point2] = Usart_Num_2->DR;    //�ѽ��յ������ݱ��浽Usart2_RxBuff��				
			if(point2 == 0)
			{    									    											 //���Usart2_RxCounter����0����ʾ�ǽ��յĵ�1�����ݣ�����if��֧				
				TIM_Cmd(Timer_Tim4, ENABLE); 
			}
			else																						 //else��֧����ʾ��Usart2_RxCounter������0�����ǽ��յĵ�һ������
			{                        									    
				TIM_SetCounter(Timer_Tim4, 0);  
			}	
			point2++;         				     //ÿ����1���ֽڵ����ݣ�Usart2_RxCounter��1����ʾ���յ���������+1 
		}
	}
} 



/******************************************************* m 
����ʶ��Ĵ�����  
�βεı�־λ�������Ը���ʵ����Ŀ�������Ӻͼ���
ע�⽫��Ӧ.h�ļ��е���������һ������
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

u8 Hand_Uart2(char *a)                   // ��������ʶ����
{ 
    if(strstr(USART2_RX_BUF,a)!=NULL)
	       return 1;
	  else
		     return 0;
}

void CLR_Uart2_Buf(void)                           // ���ڻ�������
{
	memset(USART2_RX_BUF, 0, USART_REC_LEN);      //���
  point2 = 0;                    
}


/********************�������Ӧ�ô���2�����·��ͺ�����ʽ****
u2_printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS)   ����  SSID��PASS�������ַ���
*********************************************************/

__align(8) char USART2_TX_BUF[USART2_MAX_SEND_LEN];  
void u2_printf(char* fmt,...)                   //��Ҫ������ڽ������ݷ�����Ҫ�����º���   ��һ���ڵ�ʱ�����ͨ���޸�uart.c�ļ��е�fputc�еĴ��ں�ʵ��
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�������鳤��
	for(j=0;j<i;j++)							//ѭ������
	{
	  while(USART_GetFlagStatus(Usart_Num_2,USART_FLAG_TC)==RESET); //ѭ������
		USART_SendData(Usart_Num_2,USART2_TX_BUF[j]); 
	} 
}

/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���   ��ESP8266����ģ�������ʹ��
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}


/*-------------------------------------------------*/
/*������������2���ͻ������е�����                    */
/*��  ����data������                                */
/*����ֵ����
�ú������ڰ�����   ���ݷ���ʱ����
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


