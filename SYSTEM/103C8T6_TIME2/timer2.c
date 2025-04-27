
/*-------------------------------------------------*/
/*                                                 */
/*          		��ʱ��2                       */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h" 			 //������Ҫ��ͷ�ļ�
#include "timer2.h"



unsigned  char Ms_HcSR_Count=0;


/*-------------------------------------------------*/
/*����������ʱ��2��ʼ��                            */
/*��  ����arr���Զ���װֵ   0~65535                */
/*��  ����psc��ʱ��Ԥ��Ƶ�� 0~65535                */
/*����ֵ����                                       */
/*˵  ������ʱʱ�䣺arr*psc*1000/72000000  ��λms  */
/*-------------------------------------------------*/
void TIM2_init(unsigned short int arr, unsigned short int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                           //����һ�������жϵı���	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM2, ENABLE);            //ʹ��TIM2ʱ��	
	TIM_DeInit(Timer_Tim2);                                              //��ʱ��2�Ĵ����ָ�Ĭ��ֵ	
	 TIM_TimeBaseInitStructure.TIM_Period = arr; 	                //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1��Ƶ
	TIM_TimeBaseInit(Timer_Tim2, &TIM_TimeBaseInitStructure);            //����TIM2
	
	TIM_ClearITPendingBit(Timer_Tim2, TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(Timer_Tim2, TIM_IT_Update, ENABLE);                     //ʹ��TIM2����ж�    
	TIM_Cmd(Timer_Tim2, ENABLE);                                         //��TIM2                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim2_IRQn;                //����TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                                //�����ж�
}

/*-------------------------------------------------*/
/*����������ʱ��2�жϷ�������         */
/*��  ������                                       */
/*����ֵ����  
���жϺ�����ͨ�õ��жϺ��������Ҫ�ö�ʱ��2��
�жϴ��������������º��������޸�
-------------------------------------------------*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(Timer_Tim2, TIM_IT_Update) != RESET)//���TIM_IT_Update��λ����ʾTIM2����жϣ�����if	
	{ 
//		TIM_Cmd(Timer_Tim2, DISABLE);                        				 	//�ر�TIM2��ʱ��
//		TIM_SetCounter(Timer_Tim2, 0);                        			 	//���㶨ʱ��2������
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);			
		Servo1();
		TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
		TIM_ClearITPendingBit(Timer_Tim2, TIM_IT_Update);    			 	//���TIM2����жϱ�־ 	
	}
}

/*-------------------------------------------------*/
/*����������ʱ��2�жϷ�������         */
/*��  ������                                       */
/*����ֵ����  
���жϺ�������ɶԳ��������ļ�ʱ���жϺ�����
������ǳ�������������������º���
-------------------------------------------------*/
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(Timer_Tim2, TIM_IT_Update) != RESET)//���TIM_IT_Update��λ����ʾTIM2����жϣ�����if	
//	{ 
//		TIM_ClearITPendingBit(Timer_Tim2, TIM_IT_Update);    			 	//���TIM2����жϱ�־ 
//    Ms_HcSR_Count++;		
//	}
//}

/*************************************************
�򿪶�ʱ��2
***************************************************/
void Open_Timer_Num_2()        //�򿪶�ʱ��
{
        //	/*���������*/
	TIM_SetCounter(Timer_Tim2,0);
	Ms_HcSR_Count = 0;
	TIM_Cmd(Timer_Tim2,ENABLE);//ʹ�ܶ�ʱ��
}

/***********************************************
�رն�ʱ��2
************************************************/
void Close_Timer_Num_2()        //�رն�ʱ��
{
       //	/*�رռ�����ʹ��*/
	TIM_Cmd(Timer_Tim2,DISABLE);
}
