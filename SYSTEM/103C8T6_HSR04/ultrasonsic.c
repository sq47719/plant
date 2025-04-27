#include "ultrasonsic.h"
#include "delay.h" 




void Hcsr04Init()
{  
    GPIO_InitTypeDef GPIO_InitStructure;
	/*����GPIOBʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_Usr04_GPIO_Port,ENABLE);
     
        //IO��ʼ��
    GPIO_InitStructure.GPIO_Pin =Usr04_GPIO_Pin_Num_Tx;   //���͵�ƽ����TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�����������
    GPIO_Init(Usr04_GPIO_Port, &GPIO_InitStructure);
    GPIO_ResetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Tx);//һ��ʼ�͵�ƽ
     
    GPIO_InitStructure.GPIO_Pin =   Usr04_GPIO_Pin_Num_Rx;     //���ص�ƽ����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(Usr04_GPIO_Port, &GPIO_InitStructure);  
    GPIO_ResetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Rx); //Ĭ�ϵ͵�ƽ   
         
}

void Hcsr04_Timer2_Init()
{
	 Hcsr04Init();
	 TIM2_init((1000-1),(72-1));
}


//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
   u32 time = 0;
	/*//�������źźܳ��ǣ�����ֵ������ظ�������overCount���ж��������������*/
	time = Ms_HcSR_Count*1000;//overCountÿ++һ�Σ�����overCount���룬time΢��
	time += TIM_GetCounter(Timer_Tim2);//��ȡ��TIM2���Ĵ����еļ���ֵ��һ�߼�������ź�ʱ��
	Timer_Tim2->CNT = 0;  //��TIM2�����Ĵ����ļ���ֵ����
	delay_ms(50);
	return time;
 
}
void Hcsr04GetLength(float *Leng )
{
	/*��5�����ݼ���һ��ƽ��ֵ*/

	float t = 0;
	float sum = 0;
	u16  	i = 0;
	while(i != 5){
		GPIO_SetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Tx);//trig�����źţ������ߵ�ƽ
		delay_us(20);//����ʱ�䳬��10us
		GPIO_ResetBits(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Tx);
		/*Echo�����ź� �ȴ������ź�*/
		/*���뷽����ģ����Զ�����8��40KHz�����������ͬʱ�ز����ţ�echo���˵ĵ�ƽ����0��Ϊ1��
		����ʱӦ��������ʱ����ʱ���������������ر�ģ����յ�ʱ���ز��� �Ŷ˵ĵ�ƽ����1��Ϊ0��
		����ʱӦ��ֹͣ��ʱ������������ʱ�����µ����ʱ�伴Ϊ
			�������ɷ��䵽���ص���ʱ����*/
		while(GPIO_ReadInputDataBit(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Rx) == 0);//echo�ȴ�����
		/*������ʱ��*/
		Open_Timer_Num_2();
		i = i+1; //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
		while(GPIO_ReadInputDataBit(Usr04_GPIO_Port,Usr04_GPIO_Pin_Num_Rx) == 1);
		/*�رն�ʱ��*/
		Close_Timer_Num_2();
		/*��ȡEcho�ߵ�ƽʱ��ʱ��*/
		t = GetEchoTimer();
		*Leng = (float)t/58;//��λʱcm
		sum += *Leng;		
	}
	*Leng = sum/5;//���ƽ��ֵ

}
