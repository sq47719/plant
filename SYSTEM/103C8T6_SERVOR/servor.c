#include "servor.h"
#include "usart.h"
#include "delay.h"



u8 Servor_8_Num_count1;				 //ÿ����������8·����Ⱥ�ֵ����

/*************************************
�������
���ң�GND
��ɫ����Դ
��ɫ����������


****************************************/

void Servor_GPIO_Config_Time2_Init(void)	
{
	GPIO_InitTypeDef GPIO_InitStructure;	

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_Servor_GPIO_Port, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);
  GPIO_InitStructure.GPIO_Pin =  Servor_GPIO_Pin_Num_0|Servor_GPIO_Pin_Num_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(Servor_GPIO_Port, &GPIO_InitStructure);
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_Servor1_GPIO_Port,ENABLE);
	GPIO_InitStructure.GPIO_Pin =  Servor1_GPIO_Pin_Num_0|Servor1_GPIO_Pin_Num_1|Servor1_GPIO_Pin_Num_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(Servor1_GPIO_Port, &GPIO_InitStructure);
	
	TIM2_init(2505,71);
	
}
/************************GPIO��ƽ��ת����1*****************************************/ 

void Flip_GPIO_One(void)
{

	switch(Servor_8_Num_count1)								 //��20ms�Ķ���������ڷֳ�8�ݣ�ÿ2.5ms����һ�������ת
	{  											      //ÿ����ʱ������8·�����ת��3����ʱ������24·�����ת
		case 1: 
			 Time2_ARR=Servor_CPWM_Set_Buffer[1];				 //����һ�����������ֵ��ֵ����ʱ��2			
    	 Servor_Num_0_Set;  //ͬʱ���߿��ƶ��1�����ŵĵ�
				break;
		
		case 2:
   	    Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[1]; 		 //��2.5ms��ȥPWM����ֵ�����ݸ�ֵ��ʱ��2
				Servor_Num_0_Cler;//ͬʱ���Ϳ��ƶ��1���ŵĵ�ƽ 
				break;							 //���ƶ��1��������ʣ��20ms-CPM[0]ʱ���ڽ�һֱ���ֵ͵�ƽ�����1����CPWMֵת��

		case 3:	
			  Time2_ARR=Servor_CPWM_Set_Buffer[2]; 
				Servor_Num_1_Set;
				break;
		
		case 4:	
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[2];  
				Servor_Num_1_Cler; 
				break;

		case 5:	
			  Time2_ARR=Servor_CPWM_Set_Buffer[3];  
				Servor1_Num_0_Set; 
				break;
		
		case 6:	
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[3];  
				Servor1_Num_0_Cler;	
				break;

		case 7:	
			  Time2_ARR=Servor_CPWM_Set_Buffer[4];  
			  Servor1_Num_1_Set; 
				break;
		
		case 8:	
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[4];  
				Servor1_Num_1_Cler;
				break;

		case 9:	
			  Time2_ARR=Servor_CPWM_Set_Buffer[5];  
				Servor1_Num_2_Set; 
				break;
		
		case 10:
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[5];  
				Servor1_Num_2_Cler;
				break;

		case 11:
			  Time2_ARR=Servor_CPWM_Set_Buffer[6];  
 
				break;
		
		case 12:
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[6];  

				break;

		case 13:
			  Time2_ARR=Servor_CPWM_Set_Buffer[7];  

				break;
		
		case 14:
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[7];  

				break;

		case 15:
			  Time2_ARR=Servor_CPWM_Set_Buffer[8];  

				break;
		
		case 16:
			  Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[8]; 
	
				Servor_8_Num_count1=0; 
				break;
		default:break;
	}	
}

/************************������ƺ���1*********************************************/
void Servo1(void)   //�ڶ�ʱ���жϺ����е���
{		
	Servor_8_Num_count1++; 
	Flip_GPIO_One();						 //��תIO��ƽ

}


