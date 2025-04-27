
/*-------------------------------------------------*/
/*                                                 */
/*          		定时器2                       */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h" 			 //包含需要的头文件
#include "timer2.h"



unsigned  char Ms_HcSR_Count=0;


/*-------------------------------------------------*/
/*函数名：定时器2初始化                            */
/*参  数：arr：自动重装值   0~65535                */
/*参  数：psc：时钟预分频数 0~65535                */
/*返回值：无                                       */
/*说  明：定时时间：arr*psc*1000/72000000  单位ms  */
/*-------------------------------------------------*/
void TIM2_init(unsigned short int arr, unsigned short int psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;             //定义一个设置定时器的变量
	NVIC_InitTypeDef NVIC_InitStructure;                           //定义一个设置中断的变量	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_Timer_TIM2, ENABLE);            //使能TIM2时钟	
	TIM_DeInit(Timer_Tim2);                                              //定时器2寄存器恢复默认值	
	 TIM_TimeBaseInitStructure.TIM_Period = arr; 	                //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                  //设置定时器预分频数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //1分频
	TIM_TimeBaseInit(Timer_Tim2, &TIM_TimeBaseInitStructure);            //设置TIM2
	
	TIM_ClearITPendingBit(Timer_Tim2, TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(Timer_Tim2, TIM_IT_Update, ENABLE);                     //使能TIM2溢出中断    
	TIM_Cmd(Timer_Tim2, ENABLE);                                         //开TIM2                          
	
	NVIC_InitStructure.NVIC_IRQChannel = Timer_Tim2_IRQn;                //设置TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             //子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //中断通道使能
	NVIC_Init(&NVIC_InitStructure);                                //设置中断
}

/*-------------------------------------------------*/
/*函数名：定时器2中断服务函数。         */
/*参  数：无                                       */
/*返回值：无  
此中断函数是通用的中断函数，如果要用定时器2的
中断处理函数，则在以下函数进行修改
-------------------------------------------------*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(Timer_Tim2, TIM_IT_Update) != RESET)//如果TIM_IT_Update置位，表示TIM2溢出中断，进入if	
	{ 
//		TIM_Cmd(Timer_Tim2, DISABLE);                        				 	//关闭TIM2定时器
//		TIM_SetCounter(Timer_Tim2, 0);                        			 	//清零定时器2计数器
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);			
		Servo1();
		TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
		TIM_ClearITPendingBit(Timer_Tim2, TIM_IT_Update);    			 	//清除TIM2溢出中断标志 	
	}
}

/*-------------------------------------------------*/
/*函数名：定时器2中断服务函数。         */
/*参  数：无                                       */
/*返回值：无  
此中断函数是完成对超声波测距的计时的中断函数，
如果不是超声波测距用则屏蔽以下函数
-------------------------------------------------*/
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(Timer_Tim2, TIM_IT_Update) != RESET)//如果TIM_IT_Update置位，表示TIM2溢出中断，进入if	
//	{ 
//		TIM_ClearITPendingBit(Timer_Tim2, TIM_IT_Update);    			 	//清除TIM2溢出中断标志 
//    Ms_HcSR_Count++;		
//	}
//}

/*************************************************
打开定时器2
***************************************************/
void Open_Timer_Num_2()        //打开定时器
{
        //	/*清除计数器*/
	TIM_SetCounter(Timer_Tim2,0);
	Ms_HcSR_Count = 0;
	TIM_Cmd(Timer_Tim2,ENABLE);//使能定时器
}

/***********************************************
关闭定时器2
************************************************/
void Close_Timer_Num_2()        //关闭定时器
{
       //	/*关闭计数器使能*/
	TIM_Cmd(Timer_Tim2,DISABLE);
}
