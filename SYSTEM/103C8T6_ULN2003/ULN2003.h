#ifndef __ULN2003_H
#define __ULN2003_H			


#include "delay.h"
#include "sys.h"

#define RCC_APB2Periph_ULN2003_GPIOB_Port       RCC_APB2Periph_GPIOB
#define ULN2003_GPIOB_Pin_Num_0                 GPIO_Pin_5
#define ULN2003_GPIOB_Pin_Num_1                 GPIO_Pin_6
#define ULN2003_GPIOB_Pin_Num_2                 GPIO_Pin_7
#define ULN2003_GPIOB_Pin_Num_3                 GPIO_Pin_8
#define ULN2003_GPIOB_Port                       GPIOB

#define ULN2003_GPIOB_Num_0_Control_Set      GPIO_SetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_0)
#define ULN2003_GPIOB_Num_0_Control_cler     GPIO_ResetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_0)

#define ULN2003_GPIOB_Num_1_Control_Set      GPIO_SetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_1)
#define ULN2003_GPIOB_Num_1_Control_cler     GPIO_ResetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_1)

#define ULN2003_GPIOB_Num_2_Control_Set      GPIO_SetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_2)
#define ULN2003_GPIOB_Num_2_Control_cler     GPIO_ResetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_2)

#define ULN2003_GPIOB_Num_3_Control_Set      GPIO_SetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_3)
#define ULN2003_GPIOB_Num_3_Control_cler     GPIO_ResetBits(ULN2003_GPIOB_Port,ULN2003_GPIOB_Pin_Num_3)


#define RCC_APB2Periph_ULN2003_GPIOA_Port       RCC_APB2Periph_GPIOA
#define ULN2003_GPIOA_Pin_Num_0                 GPIO_Pin_0
#define ULN2003_GPIOA_Pin_Num_1                 GPIO_Pin_1
#define ULN2003_GPIOA_Pin_Num_2                 GPIO_Pin_2
#define ULN2003_GPIOA_Pin_Num_3                 GPIO_Pin_3
#define ULN2003_GPIOA_Port                      GPIOA

#define ULN2003_GPIOA_Num_0_Control_Set      GPIO_SetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_0)
#define ULN2003_GPIOA_Num_0_Control_cler     GPIO_ResetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_0)

#define ULN2003_GPIOA_Num_1_Control_Set      GPIO_SetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_1)
#define ULN2003_GPIOA_Num_1_Control_cler     GPIO_ResetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_1)

#define ULN2003_GPIOA_Num_2_Control_Set      GPIO_SetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_2)
#define ULN2003_GPIOA_Num_2_Control_cler     GPIO_ResetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_2)

#define ULN2003_GPIOA_Num_3_Control_Set      GPIO_SetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_3)
#define ULN2003_GPIOA_Num_3_Control_cler     GPIO_ResetBits(ULN2003_GPIOA_Port,ULN2003_GPIOA_Pin_Num_3)


void ULN2003_GPIOB_Init(void);
void ULN2003_GPIOA_Init(void);
void ULN2003_GPIOB_Contol_Moto_Foreward(u16 moto_ms);
void ULN2003_GPIOB_Contol_Moto_Reversal(u16 moto_ms);
void ULN2003_GPIOB_Contol_Moto_Stop(void);

void ULN2003_GPIOA_Contol_Moto_Foreward(u16 moto_ms);
void ULN2003_GPIOA_Contol_Moto_Reversal(u16 moto_ms);
void ULN2003_GPIOA_Contol_Moto_Stop(void);  



#endif  

	 
