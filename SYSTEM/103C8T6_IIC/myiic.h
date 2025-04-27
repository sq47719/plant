#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"



#define RCC_APB2Periph_IIC1_GPIO_Port      RCC_APB2Periph_GPIOB
#define IIC1_GPIO_Port                     GPIOB
#define IIC1_GPIO_Pin_Num_SCL              (GPIO_Pin_10)
#define IIC1_GPIO_Pin_Num_SDA              (GPIO_Pin_11)


//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}       //PB7
//#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=(u32)8<<12;}     //PB11
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=(u32)3<<12;}



//IO操作函数	 
#define IIC1_SCL        PBout(10)  //SCL
#define IIC1_SDA        PBout(11)  //SDA	 
#define IIC1_READ_SDA   PBin(11)   //输入SDA 

//IIC所有操作函数
void IIC_GPIO_Init(void);                     //初始化IIC的IO口				 
void IIC_Start(void);				                  //发送IIC开始信号
void IIC_Stop(void);	  			                //发送IIC停止信号
void IIC_Send_Byte(u8 txd);			              //IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);          //IIC读取一个字节
u8 IIC_Wait_Ack(void); 				                //IIC等待ACK信号
void IIC_Ack(void);					                  //IIC发送ACK信号
void IIC_NAck(void);				                  //IIC不发送ACK信号
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif




