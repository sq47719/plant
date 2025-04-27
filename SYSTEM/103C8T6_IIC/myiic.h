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



//IO��������	 
#define IIC1_SCL        PBout(10)  //SCL
#define IIC1_SDA        PBout(11)  //SDA	 
#define IIC1_READ_SDA   PBin(11)   //����SDA 

//IIC���в�������
void IIC_GPIO_Init(void);                     //��ʼ��IIC��IO��				 
void IIC_Start(void);				                  //����IIC��ʼ�ź�
void IIC_Stop(void);	  			                //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			              //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);          //IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				                //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					                  //IIC����ACK�ź�
void IIC_NAck(void);				                  //IIC������ACK�ź�
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif




