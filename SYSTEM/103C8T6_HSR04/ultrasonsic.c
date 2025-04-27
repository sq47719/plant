#include "ultrasonsic.h"
#include "delay.h" 




void Hcsr04Init()
{  
    GPIO_InitTypeDef GPIO_InitStructure;
	/*开启GPIOB时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usr04_GPIO_Port,ENABLE);
     
        //IO初始化
    GPIO_InitStructure.GPIO_Pin =Usr04_GPIO_Pin_Num_Tx;   //发送电平引脚TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置推挽输出
    GPIO_Init(Usr04_GPIO_Port, &GPIO_InitStructure);
    GPIO_ResetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Tx);//一开始低电平
     
    GPIO_InitStructure.GPIO_Pin =   Usr04_GPIO_Pin_Num_Rx;     //返回电平引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(Usr04_GPIO_Port, &GPIO_InitStructure);  
    GPIO_ResetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Rx); //默认低电平   
         
}

void Hcsr04_Timer2_Init()
{
	 Hcsr04Init();
	 TIM2_init((1000-1),(72-1));
}


//获取定时器时间
u32 GetEchoTimer(void)
{
   u32 time = 0;
	/*//当回响信号很长是，计数值溢出后重复计数，overCount用中断来保存溢出次数*/
	time = Ms_HcSR_Count*1000;//overCount每++一次，代表overCount毫秒，time微妙
	time += TIM_GetCounter(Timer_Tim2);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间
	Timer_Tim2->CNT = 0;  //将TIM2计数寄存器的计数值清零
	delay_ms(50);
	return time;
 
}
void Hcsr04GetLength(float *Leng )
{
	/*测5次数据计算一次平均值*/

	float t = 0;
	float sum = 0;
	u16  	i = 0;
	while(i != 5){
		GPIO_SetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Tx);//trig拉高信号，发出高电平
		delay_us(20);//持续时间超过10us
		GPIO_ResetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Tx);
		/*Echo发出信号 等待回响信号*/
		/*输入方波后，模块会自动发射8个40KHz的声波，与此同时回波引脚（echo）端的电平会由0变为1；
		（此时应该启动定时器计时）；当超声波返回被模块接收到时，回波引 脚端的电平会由1变为0；
		（此时应该停止定时器计数），定时器记下的这个时间即为
			超声波由发射到返回的总时长；*/
		while(GPIO_ReadInputDataBit(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Rx) == 0);//echo等待回响
		/*开启定时器*/
		Open_Timer_Num_2();
		i = i+1; //每收到一次回响信号+1，收到5次就计算均值
		while(GPIO_ReadInputDataBit(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Rx) == 1);
		/*关闭定时器*/
		Close_Timer_Num_2();
		/*获取Echo高电平时间时间*/
		t = GetEchoTimer();
		*Leng = (float)t/58;//单位时cm
		sum += *Leng;		
	}
	*Leng = sum/5;//五次平均值

}
