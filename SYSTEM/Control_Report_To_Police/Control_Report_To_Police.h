#ifndef __CONTROL_REPORT_TO_POLICE_H  //if no define
#define __CONTROL_REPORT_TO_POLICE_H
#include "stm32f10x.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include <string.h>
#include "delay.h"
#include "adc.h"
#include "Beep_Led_Relay.h"
#include "adc2.h"
#include "key.h" 
#include "OLED_I2C.h"
#include "Beep_Led_Relay.h"
#include "dht11.h"
#include "1602.h"
#include "HX711.h"
#include "ultrasonsic.h"
#include "mlx90614.h"
#include "gps.h"
#include "adxl345.h"
#include "ds1302.h"
#include "rc522.h"
#include "rc5222.h"
#include "ASR01.h"
#include "E18_D80.h"
#include "JR6001.h"
#include "oled_Spi.h"
#include "ULN2003.h"
#include "24l01.h"
#include "servor.h"  //舵机
#include "TCS34725_Colour.h"
#include "SIM900A.h"
#include "Zigbee.h"	
#include "esp8266.h"
#include "onenet.h"
#include "rtc.h" 
#include "L298N.h"
#include "mqtt.h"
#include "wifi.h"
#include "timer2.h"
#include "timer3.h"
#include "timer4.h"
 /************************************************
版权：小常硬件
公众号：微信搜索“小常硬件“在公众号免费下载相关资料
************************************************/		

void OLED_Display_Cotrol(void); //显示控制函数
void LCD_Display_Cotrol(void);            //LCD显示
void Parameter_1_Compare(u8 parameter1,u16 parameter1_Limit_Value,u8 *Parameter1_Compare_Result) ;// 1个参数比较
void Parameter_2_Compare(u8 parameter1,u16 parameter1_Limit_Value,u8 parameter2,u16 parameter2_Limit_Value,u8 *Parameter1_Compare_Result,u8 *Parameter2_Compare_Result);//2个参数比较
void Parameter_3_Compare(u8 parameter1,u8 parameter1_Limit_Value,float parameter2,float parameter2_Limit_Value,float parameter3,float parameter3_Limit_Value,_Bool *Parameter1_Compare_Result,_Bool *Parameter2_Compare_Result,_Bool *Parameter3_Compare_Result); 

void Control_Port_Low_Effetive(u8 Parameter_Compare_Result,volatile unsigned long *Port);//低电平有效
void Control_Port_High_Effetive(u8 Parameter_Compare_Result,volatile unsigned long *Port);//高电平有效


void Noise_Control_Port_Adjust(u8 Parameter_Compare_Result);
void Water_Control_Port_Low_Effetive(u8 Parameter_Compare_Result,volatile unsigned long *Port);

_Bool isSubstring(const char* str, const char* substr);  //两个字符串  判断是否是子字符串
#endif
