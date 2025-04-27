#include "servor.h"
#include "usart.h"
#include "delay.h"



u8 Servor_8_Num_count1;				 //每个变量用作8路舵机先后赋值控制

/*************************************
舵机线序：
暗灰：GND
红色：电源
橙色：脉冲输入


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
/************************GPIO电平反转函数1*****************************************/ 

void Flip_GPIO_One(void)
{

	switch(Servor_8_Num_count1)								 //将20ms的舵机控制周期分成8份，每2.5ms控制一个舵机运转
	{  											      //每个定时器控制8路舵机运转，3个定时器控制24路舵机运转
		case 1: 
			 Time2_ARR=Servor_CPWM_Set_Buffer[1];				 //将第一个舵机脉冲宽度值赋值给定时器2			
    	 Servor_Num_0_Set;  //同时拉高控制舵机1的引脚的电
				break;
		
		case 2:
   	    Time2_ARR=MAXPWM-Servor_CPWM_Set_Buffer[1]; 		 //将2.5ms减去PWM脉宽值的数据赋值定时器2
				Servor_Num_0_Cler;//同时拉低控制舵机1引脚的电平 
				break;							 //控制舵机1的引脚在剩下20ms-CPM[0]时间内将一直保持低电平，舵机1按照CPWM值转动

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

/************************舵机控制函数1*********************************************/
void Servo1(void)   //在定时器中断函数中调用
{		
	Servor_8_Num_count1++; 
	Flip_GPIO_One();						 //反转IO电平

}


