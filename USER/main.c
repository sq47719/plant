#include "sys.h"
#include "delay.h"
#include "adc.h"
#include "math.h"
#include "key.h"
#include "OLED_I2C.h"
#include "Beep_Led_Relay.h"
#include "Control_Report_To_Police.h"

int main(void)
 {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();         //��ʱ������ʼ��	
	OLED_Init();          //OLED��ʼ��
  KEY1_Init();          //������ʼ��
	Led1_init();					//PA11 LED�����
	Relay_init();					//PB8  �̵���
	Adc_Init2();       		//PB1  ������̼
	Adc_Init1(); 					//PB0  ����ʪ��
	Adc_Init();						//PA1  ����ǿ��
	while(DHT11_Init()){} //PC15 ��ʪ��
	OLED_CLS();	        	//OLED����
		
  TIM4_Init(300,7200);      //��ʱ��
	ALi_ESP8266_GPIO_Init();  //������  ESP8266  GPIO�Լ�ͨ�Žӿڵĳ�ʼ��
	MQTT_Buff_Init();         //MQTT��ʼ������
  AliIoT_Parameter_Init();  //������

	while(1)
	{
		  OLED_Display_Cotrol();//ϵͳ��ʾ���ƹ���ʵ��OLED��ʾ
	}
}
