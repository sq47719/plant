#include "ULN2003.h"


//控制引脚接GPIOB
void ULN2003_GPIOB_Init()
{
	      GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ULN2003_GPIOB_Port,ENABLE);
        GPIO_InitStructure.GPIO_Pin = ULN2003_GPIOB_Pin_Num_0|ULN2003_GPIOB_Pin_Num_1|ULN2003_GPIOB_Pin_Num_2|ULN2003_GPIOB_Pin_Num_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(ULN2003_GPIOB_Port, &GPIO_InitStructure);

        ULN2003_GPIOB_Num_0_Control_cler;
        ULN2003_GPIOB_Num_1_Control_cler;
        ULN2003_GPIOB_Num_2_Control_cler;
        ULN2003_GPIOB_Num_3_Control_cler;
}

//控制引脚接GPIOA
void ULN2003_GPIOA_Init()
{
	      GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ULN2003_GPIOA_Port,ENABLE);
        GPIO_InitStructure.GPIO_Pin = ULN2003_GPIOA_Pin_Num_0|ULN2003_GPIOA_Pin_Num_1|ULN2003_GPIOA_Pin_Num_2|ULN2003_GPIOA_Pin_Num_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(ULN2003_GPIOA_Port, &GPIO_InitStructure);

        ULN2003_GPIOA_Num_0_Control_cler;
        ULN2003_GPIOA_Num_1_Control_cler;
        ULN2003_GPIOA_Num_2_Control_cler;
        ULN2003_GPIOA_Num_3_Control_cler;
}

//电机正转
void ULN2003_GPIOB_Contol_Moto_Foreward(u16 moto_ms)   
{
	     ULN2003_GPIOB_Num_0_Control_Set;
	     ULN2003_GPIOB_Num_1_Control_cler;
	     ULN2003_GPIOB_Num_2_Control_cler;
	     ULN2003_GPIOB_Num_3_Control_cler;
	     delay_ms(moto_ms);
	
	     ULN2003_GPIOB_Num_0_Control_cler;
	     ULN2003_GPIOB_Num_1_Control_Set;
	     ULN2003_GPIOB_Num_2_Control_cler;
	     ULN2003_GPIOB_Num_3_Control_cler;
	     delay_ms(moto_ms);
	
		   ULN2003_GPIOB_Num_0_Control_cler;
	     ULN2003_GPIOB_Num_1_Control_cler;
			 ULN2003_GPIOB_Num_2_Control_Set;
	     ULN2003_GPIOB_Num_3_Control_cler;
	     delay_ms(moto_ms);
			 
			 ULN2003_GPIOB_Num_0_Control_cler;
	     ULN2003_GPIOB_Num_1_Control_cler;
	     ULN2003_GPIOB_Num_2_Control_cler;
			 ULN2003_GPIOB_Num_3_Control_Set;
	     delay_ms(moto_ms);
}


//电机反转
void ULN2003_GPIOB_Contol_Moto_Reversal(u16 moto_ms)  
{
	     ULN2003_GPIOB_Num_0_Control_cler;	    
	     ULN2003_GPIOB_Num_1_Control_cler;
	     ULN2003_GPIOB_Num_2_Control_cler;
	     ULN2003_GPIOB_Num_3_Control_Set;
	     delay_ms(moto_ms);
	
	     ULN2003_GPIOB_Num_0_Control_cler;
	     ULN2003_GPIOB_Num_1_Control_cler;
		   ULN2003_GPIOB_Num_2_Control_Set;
	     ULN2003_GPIOB_Num_3_Control_cler;
	     delay_ms(moto_ms);
	
		   ULN2003_GPIOB_Num_0_Control_cler;
	     ULN2003_GPIOB_Num_1_Control_Set;
	     ULN2003_GPIOB_Num_2_Control_cler;
	     ULN2003_GPIOB_Num_3_Control_cler;
	     delay_ms(moto_ms);

			 ULN2003_GPIOB_Num_0_Control_Set;	
	     ULN2003_GPIOB_Num_1_Control_cler;
	     ULN2003_GPIOB_Num_2_Control_cler;
			 ULN2003_GPIOB_Num_3_Control_cler;
	     delay_ms(moto_ms);
}

void ULN2003_GPIOB_Contol_Moto_Stop()  
{
	     ULN2003_GPIOB_Num_0_Control_cler;	    
	     ULN2003_GPIOB_Num_1_Control_cler;
	     ULN2003_GPIOB_Num_2_Control_cler;
	     ULN2003_GPIOB_Num_3_Control_cler;
}

//电机正转
void ULN2003_GPIOA_Contol_Moto_Foreward(u16 moto_ms)   
{
	     ULN2003_GPIOA_Num_0_Control_Set;
	     ULN2003_GPIOA_Num_1_Control_cler;
	     ULN2003_GPIOA_Num_2_Control_cler;
	     ULN2003_GPIOA_Num_3_Control_cler;
	     delay_ms(moto_ms);
	
	     ULN2003_GPIOA_Num_0_Control_cler;
	     ULN2003_GPIOA_Num_1_Control_Set;
	     ULN2003_GPIOA_Num_2_Control_cler;
	     ULN2003_GPIOA_Num_3_Control_cler;
	     delay_ms(moto_ms);
	
		   ULN2003_GPIOA_Num_0_Control_cler;
	     ULN2003_GPIOA_Num_1_Control_cler;
			 ULN2003_GPIOA_Num_2_Control_Set;
	     ULN2003_GPIOA_Num_3_Control_cler;
	     delay_ms(moto_ms);
			 
			 ULN2003_GPIOA_Num_0_Control_cler;
	     ULN2003_GPIOA_Num_1_Control_cler;
	     ULN2003_GPIOA_Num_2_Control_cler;
			 ULN2003_GPIOA_Num_3_Control_Set;
	     delay_ms(moto_ms);
}


//电机反转
void ULN2003_GPIOA_Contol_Moto_Reversal(u16 moto_ms)  
{
	     ULN2003_GPIOA_Num_0_Control_cler;	    
	     ULN2003_GPIOA_Num_1_Control_cler;
	     ULN2003_GPIOA_Num_2_Control_cler;
	     ULN2003_GPIOA_Num_3_Control_Set;
	     delay_ms(moto_ms);
	
	     ULN2003_GPIOA_Num_0_Control_cler;
	     ULN2003_GPIOA_Num_1_Control_cler;
		   ULN2003_GPIOA_Num_2_Control_Set;
	     ULN2003_GPIOA_Num_3_Control_cler;
	     delay_ms(moto_ms);
	
		   ULN2003_GPIOA_Num_0_Control_cler;
	     ULN2003_GPIOA_Num_1_Control_Set;
	     ULN2003_GPIOA_Num_2_Control_cler;
	     ULN2003_GPIOA_Num_3_Control_cler;
	     delay_ms(moto_ms);

			 ULN2003_GPIOA_Num_0_Control_Set;	
	     ULN2003_GPIOA_Num_1_Control_cler;
	     ULN2003_GPIOA_Num_2_Control_cler;
			 ULN2003_GPIOA_Num_3_Control_cler;
	     delay_ms(moto_ms);
}	


void ULN2003_GPIOA_Contol_Moto_Stop()  
{
        ULN2003_GPIOA_Num_0_Control_cler;
        ULN2003_GPIOA_Num_1_Control_cler;
        ULN2003_GPIOA_Num_2_Control_cler;
        ULN2003_GPIOA_Num_3_Control_cler;
}

