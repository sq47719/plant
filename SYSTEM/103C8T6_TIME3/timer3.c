#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "timer3.h"
/*-------------------------------------------------*/
/*����������ʱ��3��ʼ��                            */
/*��  ����arr���Զ���װֵ   0~65535                */
/*��  ����psc��ʱ��Ԥ��Ƶ�� 0~65535                */
/*����ֵ����                                       */
/*˵  ������ʱʱ�䣺arr*psc*1000/72000000  ��λms  */
/*-------------------------------------------------*/
void TIM3_init(unsigned short int arr, unsigned short int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                           //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM3, ENABLE);           //ʹ��TIM3ʱ��	
	TIM_DeInit(Timer_Tim3);                                              //��ʱ��3�Ĵ����ָ�Ĭ��ֵ	
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	                //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1��Ƶ
	TIM_TimeBaseInit(Timer_Tim3, &TIM_TimeBaseInitStructure);            //����TIM3
	
	TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(Timer_Tim3, TIM_IT_Update, ENABLE);                     //ʹ��TIM3����ж�    
	TIM_Cmd(Timer_Tim3, DISABLE);                                         //�ȹ�TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim3_IRQn;                //����TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                                //�����ж�
}

/*-------------------------------------------------*/
/*����������ʱ��3�жϷ������� */
/*��  ������                                       */
/*����ֵ����                                       */
//��������Ƕ�ʱ����ͨ���жϺ�������ʱ���ж���Ҫ�����
//�����ڸú������޸�
/*-------------------------------------------------*/
//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(Timer_Tim3, TIM_IT_Update) != RESET)//���TIM_IT_Update��λ����ʾTIM3����жϣ�����if	
//	{ 
//		TIM_Cmd(Timer_Tim3, DISABLE);                        				 	//�ر�TIM3��ʱ��
//		TIM_SetCounter(Timer_Tim3, 0);                        			 	//���㶨ʱ��3������
//		TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);    			 	//���TIM3����жϱ�־ 	
//	}
//}

/**************************************************************
������  ����ͨ�Ŷ�ʱ��3��Ҫ�жϴ�����ʱ��
***************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//���TIM_IT_Update��λ����ʾTIM3����жϣ�����if	
		{  
		switch(pingFlag) 					//�ж�pingFlag��״̬
		{                               
			case 0:							//���pingFlag����0����ʾ����״̬������Ping����  
					MQTT_PingREQ(); 		//���Ping���ĵ����ͻ�����  
					break;
			case 1:							//���pingFlag����1��˵����һ�η��͵���ping���ģ�û���յ��������ظ�������1û�б����Ϊ0�������������쳣������Ҫ��������pingģʽ
					TIM3_ENABLE_2S(); 	    //���ǽ���ʱ��6����Ϊ2s��ʱ,���ٷ���Ping����
					MQTT_PingREQ();			//���Ping���ĵ����ͻ�����  
					break;
			case 2:							//���pingFlag����2��˵����û���յ��������ظ�
			case 3:				            //���pingFlag����3��˵����û���յ��������ظ�
			case 4:				            //���pingFlag����4��˵����û���յ��������ظ�	
					MQTT_PingREQ();  		//���Ping���ĵ����ͻ����� 
					break;
			case 5:							//���pingFlag����5��˵�����Ƿ����˶��ping�����޻ظ���Ӧ�������������⣬������������
					connectFlag = 0;        //����״̬��0����ʾ�Ͽ���û���Ϸ�����
					TIM_Cmd(TIM3, DISABLE); //��TIM3 				
					break;			
		}
		pingFlag++;           		   		//pingFlag����1����ʾ�ַ�����һ��ping���ڴ��������Ļظ�
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���TIM3����жϱ�־ 	
	}
}

/*-------------------------------------------------*/
/*����������ʱ��3ʹ��30s��ʱ                       */                                    
/*-------------------------------------------------*/
void TIM3_ENABLE_30S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                           //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM3, ENABLE);     //ʹ��TIM3ʱ��	
	TIM_DeInit(Timer_Tim3);                                              //��ʱ��3�Ĵ����ָ�Ĭ��ֵ	
	TIM_TimeBaseInitStructure.TIM_Period = 60000-1; 	           //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36000-1;             //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1��Ƶ
	TIM_TimeBaseInit(Timer_Tim3, &TIM_TimeBaseInitStructure);            //����TIM3
	
	TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(Timer_Tim3, TIM_IT_Update, ENABLE);                     //ʹ��TIM3����ж�    
	TIM_Cmd(Timer_Tim3, ENABLE);                                         //��TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim3_IRQn;                //����TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                                //�����ж�
}
/*-------------------------------------------------*/
/*����������ʱ��3ʹ��2s��ʱ                        */                                      
/*-------------------------------------------------*/
void TIM3_ENABLE_2S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                           //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM3, ENABLE);           //ʹ��TIM3ʱ��
	TIM_DeInit(Timer_Tim3);                                              //��ʱ��3�Ĵ����ָ�Ĭ��ֵ	
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1; 	           //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;              //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1��Ƶ
	TIM_TimeBaseInit(Timer_Tim3, &TIM_TimeBaseInitStructure);            //����TIM3
	
	TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(Timer_Tim3, TIM_IT_Update, ENABLE);                     //ʹ��TIM3����ж�    
	TIM_Cmd(Timer_Tim3, ENABLE);                                         //��TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim3_IRQn;                //����TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                                //�����ж�
}
