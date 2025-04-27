#include "stm32f10x.h"  //包含需要的头文件
#include "timer3.h"
/*-------------------------------------------------*/
/*函数名：定时器3初始化                            */
/*参  数：arr：自动重装值   0~65535                */
/*参  数：psc：时钟预分频数 0~65535                */
/*返回值：无                                       */
/*说  明：定时时间：arr*psc*1000/72000000  单位ms  */
/*-------------------------------------------------*/
void TIM3_init(unsigned short int arr, unsigned short int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //定义一个设置定时器的变量
	NVIC_InitTypeDef NVIC_InitStructure;                           //定义一个设置中断的变量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM3, ENABLE);           //使能TIM3时钟	
	TIM_DeInit(Timer_Tim3);                                              //定时器3寄存器恢复默认值	
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	                //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //设置定时器预分频数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1分频
	TIM_TimeBaseInit(Timer_Tim3, &TIM_TimeBaseInitStructure);            //设置TIM3
	
	TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(Timer_Tim3, TIM_IT_Update, ENABLE);                     //使能TIM3溢出中断    
	TIM_Cmd(Timer_Tim3, DISABLE);                                         //先关TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim3_IRQn;                //设置TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //中断通道使能
	NVIC_Init(&NVIC_InitStructure);                                //设置中断
}

/*-------------------------------------------------*/
/*函数名：定时器3中断服务函数。 */
/*参  数：无                                       */
/*返回值：无                                       */
//这个函数是定时器的通用中断函数，定时器中断需要处理的
//数据在该函数中修改
/*-------------------------------------------------*/
//void TIM3_IRQHandler(void)
//{
//	if(TIM_GetITStatus(Timer_Tim3, TIM_IT_Update) != RESET)//如果TIM_IT_Update置位，表示TIM3溢出中断，进入if	
//	{ 
//		TIM_Cmd(Timer_Tim3, DISABLE);                        				 	//关闭TIM3定时器
//		TIM_SetCounter(Timer_Tim3, 0);                        			 	//清零定时器3计数器
//		TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);    			 	//清除TIM3溢出中断标志 	
//	}
//}

/**************************************************************
阿里云  数据通信定时器3需要中断处理函数时用
***************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//如果TIM_IT_Update置位，表示TIM3溢出中断，进入if	
		{  
		switch(pingFlag) 					//判断pingFlag的状态
		{                               
			case 0:							//如果pingFlag等于0，表示正常状态，发送Ping报文  
					MQTT_PingREQ(); 		//添加Ping报文到发送缓冲区  
					break;
			case 1:							//如果pingFlag等于1，说明上一次发送到的ping报文，没有收到服务器回复，所以1没有被清除为0，可能是连接异常，我们要启动快速ping模式
					TIM3_ENABLE_2S(); 	    //我们将定时器6设置为2s定时,快速发送Ping报文
					MQTT_PingREQ();			//添加Ping报文到发送缓冲区  
					break;
			case 2:							//如果pingFlag等于2，说明还没有收到服务器回复
			case 3:				            //如果pingFlag等于3，说明还没有收到服务器回复
			case 4:				            //如果pingFlag等于4，说明还没有收到服务器回复	
					MQTT_PingREQ();  		//添加Ping报文到发送缓冲区 
					break;
			case 5:							//如果pingFlag等于5，说明我们发送了多次ping，均无回复，应该是连接有问题，我们重启连接
					connectFlag = 0;        //连接状态置0，表示断开，没连上服务器
					TIM_Cmd(TIM3, DISABLE); //关TIM3 				
					break;			
		}
		pingFlag++;           		   		//pingFlag自增1，表示又发送了一次ping，期待服务器的回复
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIM3溢出中断标志 	
	}
}

/*-------------------------------------------------*/
/*函数名：定时器3使能30s定时                       */                                    
/*-------------------------------------------------*/
void TIM3_ENABLE_30S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //定义一个设置定时器的变量
	NVIC_InitTypeDef NVIC_InitStructure;                           //定义一个设置中断的变量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM3, ENABLE);     //使能TIM3时钟	
	TIM_DeInit(Timer_Tim3);                                              //定时器3寄存器恢复默认值	
	TIM_TimeBaseInitStructure.TIM_Period = 60000-1; 	           //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36000-1;             //设置定时器预分频数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1分频
	TIM_TimeBaseInit(Timer_Tim3, &TIM_TimeBaseInitStructure);            //设置TIM3
	
	TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(Timer_Tim3, TIM_IT_Update, ENABLE);                     //使能TIM3溢出中断    
	TIM_Cmd(Timer_Tim3, ENABLE);                                         //开TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim3_IRQn;                //设置TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //中断通道使能
	NVIC_Init(&NVIC_InitStructure);                                //设置中断
}
/*-------------------------------------------------*/
/*函数名：定时器3使能2s定时                        */                                      
/*-------------------------------------------------*/
void TIM3_ENABLE_2S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //定义一个设置定时器的变量
	NVIC_InitTypeDef NVIC_InitStructure;                           //定义一个设置中断的变量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM3, ENABLE);           //使能TIM3时钟
	TIM_DeInit(Timer_Tim3);                                              //定时器3寄存器恢复默认值	
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1; 	           //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;              //设置定时器预分频数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1分频
	TIM_TimeBaseInit(Timer_Tim3, &TIM_TimeBaseInitStructure);            //设置TIM3
	
	TIM_ClearITPendingBit(Timer_Tim3, TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(Timer_Tim3, TIM_IT_Update, ENABLE);                     //使能TIM3溢出中断    
	TIM_Cmd(Timer_Tim3, ENABLE);                                         //开TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim3_IRQn;                //设置TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //中断通道使能
	NVIC_Init(&NVIC_InitStructure);                                //设置中断
}
