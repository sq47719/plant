#ifndef __JR6001_H
#define __JR6001_H	 


#include "sys.h" 
#include "usart.h"
#include "usart2.h"     //包含需要的头文件
#include "usart3.h"
#include "delay.h"

void JR6001_Uart1_init(u32 *boun);
void JR6001_Uart2_init(u32 *boun);
void JR6001_Uart3_init(u32 *boun);

void JR6001_Uart1_Handle(char *Instruct,_Bool Voice_Sppch_flag);
void JR6001_Uart2_Handle(char *Instruct,_Bool Voice_Sppch_flag);
void JR6001_Uart3_Handle(char *Instruct,_Bool Voice_Sppch_flag);

void JR6001_Uart1_Voice_Add(void);
void JR6001_Uart2_Voice_Add(void);
void JR6001_Uart3_Voice_Add(void);
	

#endif
