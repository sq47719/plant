#include "timer1.h"
#include "delay.h"
/*-------------------------------------------------*/
/*��ʱ��1     	                                   */
/*��  ����arr���Զ���װֵ   0~65535                */
/*��  ����psc��ʱ��Ԥ��Ƶ�� 0~65535                */
/*����ֵ����                                       */
/*˵  ������ʱʱ�䣺arr*psc*1000/72000000  ��λms  */
/*-------------------------------------------------*/
void Timer1_Init(unsigned short int arr, unsigned short int psc)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;     //�������ڶ�ʱ�����õĽṹ��   
    NVIC_InitTypeDef NVIC_InitStructure;                    //����һ�������жϵı���	
	
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	        //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	
	  RCC_APB1PeriphClockCmd(RCC_APB2Periph_Timer_TIM1, ENABLE);                //ʹ��TIM1ʱ��		
    TIM_DeInit(Timer_Tim1 );                                                  //��ʱ��1�Ĵ����ָ�Ĭ��ֵ
	
		TIM_TimeBaseInitStructure.TIM_Period = arr;                              //�����Զ���װ��ֵ      //�Զ���װ��ֵ�Ĵ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
		TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                           //���ö�ʱ��Ԥ��Ƶ��
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;            		//ʱ�ӷ�Ƶ����
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;           //����������ģʽ���������ϼ���
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0 ;                    	//�ظ���������ֵ
    TIM_TimeBaseInit(Timer_Tim1, &TIM_TimeBaseInitStructure);                    //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ       
  
		TIM_ClearITPendingBit(Timer_Tim1, TIM_FLAG_Update); //��������жϣ����һ���ж����������ж�
    TIM_ITConfig(Timer_Tim1,TIM_IT_Update,ENABLE);    //�򿪶�ʱ�������ж�
    TIM_Cmd(Timer_Tim1, ENABLE);  
	
	  NVIC_InitStructure.NVIC_IRQChannel	= Timer_Tim1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 1;  	//���������ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority				= 1;    //���ô����ȼ�
	  NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��1�жϷ������
void TIM1_UP_IRQHandler(void)   //TIM1�ж�TIM1_UP_IRQHandler
{
	if(TIM_GetITStatus(Timer_Tim1,TIM_IT_Update) != RESET)     //	/*�ж��ж��ַ���Ĳ���*/
	{
		TIM_ClearITPendingBit(Timer_Tim1,TIM_IT_Update);	 	/*��������жϱ�־λ*/
	}
}
