#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
	  
/****************************************

按键初始化函数

****************************************/

void KEY1_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_key1_GPIO_Port,ENABLE);//使能时钟

	GPIO_InitStructure.GPIO_Pin  = Key1_GPIO_Pin_num|Key1_GPIO_Pin_num1|Key1_GPIO_Pin_num2|Key1_GPIO_Pin_num3;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(Key1_GPIO_Port, &GPIO_InitStructure);//初始化GPIO
}


//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY3按下 
//注意此函数有响应优先级,KEY0>KEY1>KEY2!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志   static 为了执行该子函数的时候该变量不会每次都会被初始化
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// 无按键按下
}

/***************变量定义说明***************
整个系统的阈值设定变量按照这种方式进行命名
不用的变量要删除
需要用到的变量引用到以下函数的形参
***************变量定义说明***************/

//u16 *T_Ma;  //温度最大值   temperature
//u16 *T_Mi;   //温度最小值
//u16 *H_Ma;  //湿度最大值   Humidity
//u16 *H_Mi;  //湿度最小值
//float *B_Ma   //光照最大值   Beam
//float *B_Mi   //光照最小值 

/*************设定一个参数******/
void Limit_Value_Set_1(u16 *B_Ma) //光照最大值 
{
	u8 Key_Flag=0;
	static u8 Parameter_Select=0;
	Key_Flag=KEY_Scan(1);            //支持连续按
	if(Key_Flag==KEY0_PRES)          //完成需要设定的参数选择
	{
		Parameter_Select++;
		if(Parameter_Select==2)
		{
			Parameter_Select=0;
		}
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY1_PRES))  //选定参数后++
	{
		  *B_Ma +=1;
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY2_PRES))  //选定参数后--
	{
		  *B_Ma -=1;
	}
}
/***********设定两个参数************/
void Limit_Value_Set_2(u16 *T_Ma,u16 *H_Ma)
{
	u8 Key_Flag=0;
	static u8 Parameter_Select=0;
	Key_Flag=KEY_Scan(1);            //支持连续按
	if(Key_Flag==KEY0_PRES)          //完成需要设定的参数选择
	{
		Parameter_Select++;
		if(Parameter_Select==3)
		{
			Parameter_Select=0;
		}
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY1_PRES))  //选定参数后++
	{
		  *T_Ma +=1;
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY2_PRES))  //选定参数后--
	{
		  *T_Ma -=1;
	}
	if((Parameter_Select==2)&&(Key_Flag==KEY1_PRES))  //选定参数后++
	{
		  *H_Ma +=1;
	}
	if((Parameter_Select==2)&&(Key_Flag==KEY2_PRES))  //选定参数后--
	{
		  *H_Ma -=1;
	}
}

/**************************************
判断按键是否按下 完成控制标志位的设定
需要几个按键控制  可以根据设定需要对形参数量进行修改
*****************************************/
void Key_Control_Handle(_Bool *Key_0_Press_Fla,_Bool *Key_1_Press_Fla,u8 *Key_0_Num)
{
	u8 Key_Flag=0;
	static  u8 Key_0_Num_Count=0;
	Key_Flag=KEY_Scan(0);//不支持连续按
	
	if(Key_Flag==KEY0_PRES)
	{
		*Key_0_Press_Fla=1;
		Key_0_Num_Count++;
		*Key_0_Num=Key_0_Num_Count;
		if(Key_0_Num_Count==3)
		{
			Key_0_Num_Count=0;
		  *Key_0_Num=*Key_0_Num;
		}
	}
	if(Key_Flag==KEY1_PRES)
	{
		*Key_1_Press_Fla=1;
	}
}

/**************************************
一个按键进行控制
*****************************************/
void One_Key_Control_Handle(_Bool *Key_0_Press_Fla)
{
	u8 Key_Flag=0;
	Key_Flag=KEY_Scan(0);//不支持连续按
	
	if(Key_Flag==KEY0_PRES)
	{
		*Key_0_Press_Fla=1;
	}
}
