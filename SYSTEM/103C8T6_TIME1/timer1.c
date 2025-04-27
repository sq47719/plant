#include "timer1.h"
#include "delay.h"
/*-------------------------------------------------*/
/*定时器1     	                                   */
/*参  数：arr：自动重装值   0~65535                */
/*参  数：psc：时钟预分频数 0~65535                */
/*返回值：无                                       */
/*说  明：定时时间：arr*psc*1000/72000000  单位ms  */
/*-------------------------------------------------*/
void Timer1_Init(unsigned short int arr, unsigned short int psc)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;     //生成用于定时器设置的结构体   
    NVIC_InitTypeDef NVIC_InitStructure;                    //定义一个设置中断的变量	
	
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	        //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	
	  RCC_APB1PeriphClockCmd(RCC_APB2Periph_Timer_TIM1, ENABLE);                //使能TIM1时钟		
    TIM_DeInit(Timer_Tim1 );                                                  //定时器1寄存器恢复默认值
	
		TIM_TimeBaseInitStructure.TIM_Period = arr;                              //设置自动重装载值      //自动重装载值寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
		TIM_TimeBaseInitStructure.TIM_Prescaler = psc;                           //设置定时器预分频数
		TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;            		//时钟分频因子
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;           //计数器计数模式，设置向上计数
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0 ;                    	//重复计数器的值
    TIM_TimeBaseInit(Timer_Tim1, &TIM_TimeBaseInitStructure);                    //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位       
  
		TIM_ClearITPendingBit(Timer_Tim1, TIM_FLAG_Update); //清除更新中断，免得一打开中断立即产生中断
    TIM_ITConfig(Timer_Tim1,TIM_IT_Update,ENABLE);    //打开定时器更新中断
    TIM_Cmd(Timer_Tim1, ENABLE);  
	
	  NVIC_InitStructure.NVIC_IRQChannel	= Timer_Tim1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 1;  	//设置主优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority				= 1;    //设置次优先级
	  NVIC_Init(&NVIC_InitStructure);
}

//定时器1中断服务程序
void TIM1_UP_IRQHandler(void)   //TIM1中断TIM1_UP_IRQHandler
{
	if(TIM_GetITStatus(Timer_Tim1,TIM_IT_Update) != RESET)     //	/*判断中断手否真的产生*/
	{
		TIM_ClearITPendingBit(Timer_Tim1,TIM_IT_Update);	 	/*清除更新中断标志位*/
	}
}
