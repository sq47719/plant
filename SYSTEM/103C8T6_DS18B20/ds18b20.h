#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   

 /************************************************
版权：小常硬件
公众号：微信搜索“小常硬件“在公众号免费下载相关资料
************************************************/	

/***************DS18B20引脚定义******************/

#define RCC_APB2Periph_DS18B20_GPIO_Port    RCC_APB2Periph_GPIOB
#define DS18B20_GPIO_Pin_Num                GPIO_Pin_8
#define DS18B20_GPIO_Port                   GPIOB


////IO操作函数											   
#define	DS18B20_DQ_OUT PBout(8) //数据端口	
#define	DS18B20_DQ_IN  PBin(8)  //数据端口	
   	
u8 DS18B20_Init(void);                   //初始化DS18B20
short DS18B20_Get_Temp(void);            //获取温度
void DS18B20_Start(void);                //开始温度转换
void DS18B20_Write_Byte(u8 dat);         //写入一个字节
u8 DS18B20_Read_Byte(void);              //读出一个字节
u8 DS18B20_Read_Bit(void);               //读出一个位
u8 DS18B20_Check(void);                  //检测是否存在DS18B20
void DS18B20_Rst(void);                  //复位DS18B20   

#endif















