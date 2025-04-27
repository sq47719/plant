#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
	  
/****************************************

������ʼ������

****************************************/

void KEY1_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_key1_GPIO_Port,ENABLE);//ʹ��ʱ��

	GPIO_InitStructure.GPIO_Pin  = Key1_GPIO_Pin_num|Key1_GPIO_Pin_num1|Key1_GPIO_Pin_num2|Key1_GPIO_Pin_num3;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(Key1_GPIO_Port, &GPIO_InitStructure);//��ʼ��GPIO
}


//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY3���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־   static Ϊ��ִ�и��Ӻ�����ʱ��ñ�������ÿ�ζ��ᱻ��ʼ��
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// �ް�������
}

/***************��������˵��***************
����ϵͳ����ֵ�趨�����������ַ�ʽ��������
���õı���Ҫɾ��
��Ҫ�õ��ı������õ����º������β�
***************��������˵��***************/

//u16 *T_Ma;  //�¶����ֵ   temperature
//u16 *T_Mi;   //�¶���Сֵ
//u16 *H_Ma;  //ʪ�����ֵ   Humidity
//u16 *H_Mi;  //ʪ����Сֵ
//float *B_Ma   //�������ֵ   Beam
//float *B_Mi   //������Сֵ 

/*************�趨һ������******/
void Limit_Value_Set_1(u16 *B_Ma) //�������ֵ 
{
	u8 Key_Flag=0;
	static u8 Parameter_Select=0;
	Key_Flag=KEY_Scan(1);            //֧��������
	if(Key_Flag==KEY0_PRES)          //�����Ҫ�趨�Ĳ���ѡ��
	{
		Parameter_Select++;
		if(Parameter_Select==2)
		{
			Parameter_Select=0;
		}
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY1_PRES))  //ѡ��������++
	{
		  *B_Ma +=1;
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY2_PRES))  //ѡ��������--
	{
		  *B_Ma -=1;
	}
}
/***********�趨��������************/
void Limit_Value_Set_2(u16 *T_Ma,u16 *H_Ma)
{
	u8 Key_Flag=0;
	static u8 Parameter_Select=0;
	Key_Flag=KEY_Scan(1);            //֧��������
	if(Key_Flag==KEY0_PRES)          //�����Ҫ�趨�Ĳ���ѡ��
	{
		Parameter_Select++;
		if(Parameter_Select==3)
		{
			Parameter_Select=0;
		}
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY1_PRES))  //ѡ��������++
	{
		  *T_Ma +=1;
	}
	if((Parameter_Select==1)&&(Key_Flag==KEY2_PRES))  //ѡ��������--
	{
		  *T_Ma -=1;
	}
	if((Parameter_Select==2)&&(Key_Flag==KEY1_PRES))  //ѡ��������++
	{
		  *H_Ma +=1;
	}
	if((Parameter_Select==2)&&(Key_Flag==KEY2_PRES))  //ѡ��������--
	{
		  *H_Ma -=1;
	}
}

/**************************************
�жϰ����Ƿ��� ��ɿ��Ʊ�־λ���趨
��Ҫ������������  ���Ը����趨��Ҫ���β����������޸�
*****************************************/
void Key_Control_Handle(_Bool *Key_0_Press_Fla,_Bool *Key_1_Press_Fla,u8 *Key_0_Num)
{
	u8 Key_Flag=0;
	static  u8 Key_0_Num_Count=0;
	Key_Flag=KEY_Scan(0);//��֧��������
	
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
һ���������п���
*****************************************/
void One_Key_Control_Handle(_Bool *Key_0_Press_Fla)
{
	u8 Key_Flag=0;
	Key_Flag=KEY_Scan(0);//��֧��������
	
	if(Key_Flag==KEY0_PRES)
	{
		*Key_0_Press_Fla=1;
	}
}
