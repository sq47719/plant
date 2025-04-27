#ifndef __DS1302_H
#define __DS1302_H
#include "sys.h"

extern u8 time_buf[8];

#define RCC_APB2Periph_DS1302_GPIO_Port        RCC_APB2Periph_GPIOA
#define DS1302_GPIO_Pin_CLK                    GPIO_Pin_0
#define DS1302_GPIO_Pin_RST                    GPIO_Pin_2
#define DS1302_GPIO_Pin_DATA                   GPIO_Pin_1
#define DS1302_GPIO_Port                       GPIOA

//IO方向设置
#define DS1302_IO_IN()  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=8<<4;}
#define DS1302_IO_OUT() {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=3<<4;}

//IO操作函数									   
#define	DS1302_DATA_OUT PAout(1) //数据端口	
#define	DS1302_DATA_IN  PAin(1)  //数据端口	

#define	DS1302_SCK  PAout(0)
#define	DS1302_RST  PAout(2)


//DS1302地址定义
#define ds1302_sec_add			  0x80		//秒数据地址
#define ds1302_min_add			  0x82		//分数据地址
#define ds1302_hr_add			    0x84		//时数据地址
#define ds1302_date_add			  0x86		//日数据地址
#define ds1302_month_add		  0x88		//月数据地址
#define ds1302_day_add			  0x8a		//星期数据地址
#define ds1302_year_add			  0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

void DS1302_GPIO_Init_Write_Time(void);
void DS1302_Write_Byte(u8 addr, u8 data);
u8 DS1302_Read_Byte(u8 addr);
void DS1302_Write_Time(void);
void DS1302_Read_Time(void);
void DS1302_Get_Time(u8 *time1);

#endif
