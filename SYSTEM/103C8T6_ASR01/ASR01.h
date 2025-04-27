#ifndef __ASR01_H  //if no define
#define __ASR01_H

#include "sys.h" 
#include "usart.h"
#include "usart2.h"     //包含需要的头文件
#include "usart3.h"



void ASR01_Uart1_init(u32 *boun);
void ASR01_Uart2_init(u32 *boun);
void ASR01_Uart3_init(u32 *boun);


#endif

