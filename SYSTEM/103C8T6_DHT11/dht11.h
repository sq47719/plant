#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   


		

/******************IO口方向设置****************
对于PA0到PA15  IO口方向设置整理如下，其他的GPIOB、GPIOC同理即可

//PA0
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=8<<0;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=3<<0;}
//PA1
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=8<<4;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=3<<4;}
//PA2
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=8<<8;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFF0FF;GPIOA->CRL|=3<<8;}
//PA3
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFF0FFF;GPIOA->CRL|=8<<12;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFF0FFF;GPIOA->CRL|=3<<12;}
//PA4
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=8<<16;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=3<<16;}
//PA5
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=8<<20;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=3<<20;}
//PA6
#define DHT11_IO_IN()  {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=8<<24;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XF0FFFFFF;GPIOA->CRL|=3<<24;}
//PA7
#define DHT11_IO_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=8<<28;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=3<<28;}



//PA8
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=8<<0;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=3<<0;}
//PA9
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=8<<4;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=3<<4;}
//PA10
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFFF0FF;GPIOA->CRH|=8<<8;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFFF0FF;GPIOA->CRH|=3<<8;}
//PA11
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=3<<12;}
//PA12
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=8<<16;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=3<<16;}
//PA13
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFF0FFFFF;GPIOA->CRH|=3<<20;}
//PA14
#define DHT11_IO_IN()  {GPIOA->CRH&=0XF0FFFFFF;GPIOA->CRH|=8<<24;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XF0FFFFFF;GPIOA->CRH|=3<<24;}
//PA15
#define DHT11_IO_IN()  {GPIOA->CRH&=0X0FFFFFFF;GPIOA->CRH|=8<<28;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0X0FFFFFFF;GPIOA->CRH|=3<<28;}
**********************************************/

/***************DHT11端口相关参数配置定义**********/
#define RCC_APB2Periph_DHT11_GPIO_Port    RCC_APB2Periph_GPIOC
#define DHT11_GPIO_Pin_Num                GPIO_Pin_15
#define DHT11_GPIO_Port                   GPIOC

//IO方向设置
//PA12
#define DHT11_IO_IN()  {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=8<<28;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=3<<28;}

////IO操作函数											   
#define	DHT11_DQ_OUT PCout(15) //数据端口	
#define	DHT11_DQ_IN  PCin(15)  //数据端口	


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif















