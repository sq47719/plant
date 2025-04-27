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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();         //延时函数初始化	
	OLED_Init();          //OLED初始化
  KEY1_Init();          //按键初始化
	Led1_init();					//PA11 LED补光灯
	Relay_init();					//PB8  继电器
	Adc_Init2();       		//PB1  二氧化碳
	Adc_Init1(); 					//PB0  土壤湿度
	Adc_Init();						//PA1  光照强度
	while(DHT11_Init()){} //PC15 温湿度
	OLED_CLS();	        	//OLED清屏
		
  TIM4_Init(300,7200);      //定时器
	ALi_ESP8266_GPIO_Init();  //阿里云  ESP8266  GPIO以及通信接口的初始化
	MQTT_Buff_Init();         //MQTT初始化接收
  AliIoT_Parameter_Init();  //阿里云

	while(1)
	{
		  OLED_Display_Cotrol();//系统显示控制功能实现OLED显示
	}
}
