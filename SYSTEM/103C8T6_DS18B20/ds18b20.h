#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   

 /************************************************
��Ȩ��С��Ӳ��
���ںţ�΢��������С��Ӳ�����ڹ��ں���������������
************************************************/	

/***************DS18B20���Ŷ���******************/

#define RCC_APB2Periph_DS18B20_GPIO_Port    RCC_APB2Periph_GPIOB
#define DS18B20_GPIO_Pin_Num                GPIO_Pin_8
#define DS18B20_GPIO_Port                   GPIOB


////IO��������											   
#define	DS18B20_DQ_OUT PBout(8) //���ݶ˿�	
#define	DS18B20_DQ_IN  PBin(8)  //���ݶ˿�	
   	
u8 DS18B20_Init(void);                   //��ʼ��DS18B20
short DS18B20_Get_Temp(void);            //��ȡ�¶�
void DS18B20_Start(void);                //��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);         //д��һ���ֽ�
u8 DS18B20_Read_Byte(void);              //����һ���ֽ�
u8 DS18B20_Read_Bit(void);               //����һ��λ
u8 DS18B20_Check(void);                  //����Ƿ����DS18B20
void DS18B20_Rst(void);                  //��λDS18B20   

#endif















