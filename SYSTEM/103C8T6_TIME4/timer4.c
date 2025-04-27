
/*-------------------------------------------------*/
/*                                                 */
/*          		 ��ʱ��4                       */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "timer4.h"


/*-------------------------------------------------*/
/*����������ʱ��4��ʼ��                            */
/*��  ����arr���Զ���װֵ   0~65535                */
/*��  ����psc��ʱ��Ԥ��Ƶ�� 0~65535                */
/*����ֵ����                                       */
/*˵  ������ʱʱ�䣺arr*psc*1000/72000000  ��λms  */
/*-------------------------------------------------*/
void TIM4_Init(unsigned short int arr, unsigned short int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                            //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                 //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM4, ENABLE);            //ʹ��TIM4ʱ��	
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	                  //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //1��Ƶ
	TIM_TimeBaseInit(Timer_Tim4, &TIM_TimeBaseInitStructure);             //����TIM4
	
	TIM_ClearITPendingBit(Timer_Tim4, TIM_IT_Update);                     //�������жϱ�־λ
	TIM_ITConfig(Timer_Tim4, TIM_IT_Update, ENABLE);                      //ʹ��TIM4����ж�    
	TIM_Cmd(Timer_Tim4, DISABLE);                                         //�ȹر�TIM4                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim4_IRQn;                 //����TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //�����ж�
}


/*-------------------------------------------------*/
/*����������ʱ��4�жϷ�������        */
/*��  ������                                       */
/*����ֵ����                                       */
//ͨ�õĶ�ʱ��4�жϺ������������º����н��д���
/*-------------------------------------------------*/
//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(Timer_Tim4, TIM_IT_Update) != RESET)//���TIM_IT_Update��λ����ʾTIM4����жϣ�����if	
//	{ 
//		TIM_Cmd(Timer_Tim4, DISABLE);                        				 	//�ر�TIM4��ʱ��
//		TIM_SetCounter(Timer_Tim4, 0);                        			 	//���㶨ʱ��4������
//		TIM_ClearITPendingBit(Timer_Tim4, TIM_IT_Update);    			 	//���TIM4����жϱ�־ 	
//	}
//}


/**************************************************
������  ��������ͨ��ͨ����ʱ���жϺ���������ĺ���
������ǺͰ�����ͨ�Ž�������
****************************************************/
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//���TIM_IT_Update��λ����ʾTIM4����жϣ�����if	
	{                	
		memcpy(&MQTT_RxDataInPtr[2], USART2_RX_BUF, point2);  //�������ݵ����ջ�����
		MQTT_RxDataInPtr[0] = point2/256;                  	//��¼���ݳ��ȸ��ֽ�
		MQTT_RxDataInPtr[1] = point2%256;					 	        //��¼���ݳ��ȵ��ֽ�
		MQTT_RxDataInPtr += BUFF_UNIT;                                	//ָ������
		if(MQTT_RxDataInPtr == MQTT_RxDataEndPtr)                     	//���ָ�뵽������β����
			MQTT_RxDataInPtr = MQTT_RxDataBuf[0];                    	//ָ���λ����������ͷ
		point2 = 0;                                        	//����2������������������
		TIM_SetCounter(TIM3, 0);                                     	//���㶨ʱ��3�����������¼�ʱping������ʱ��
		TIM_Cmd(TIM4, DISABLE);                        				 	//�ر�TIM4��ʱ��
		TIM_SetCounter(TIM4, 0);                        			 	//���㶨ʱ��4������
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);     			 	//���TIM4����жϱ�־ 	
	}
}
