/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLX90614_H
#define __MLX90614_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

 /************************************************
版权：小常硬件
公众号：微信搜索“小常硬件“在公众号免费下载相关资料
************************************************/		

#define ACK	 0 //应答
#define	NACK 1 //无应答
#define SA				0x00 //Slave address 单个MLX90614时地址为0x00,多个时地址默认为0x5a
#define RAM_ACCESS		0x00 //RAM access command RAM存取命令
#define EEPROM_ACCESS	0x20 //EEPROM access command EEPROM存取命令
#define RAM_TOBJ1		0x07 //To1 address in the eeprom 目标1温度,检测到的红外温度 -70.01 ~ 382.19度


/**************引脚相关参数定义***********
由于本模块程序的IIC协议是通过模拟时序的方式实现，
所以以下相关引脚定义可以进行随意更改，换普通IO口也可
******************************************/

#define RCC_APB2Periph_GP906_GPIO_Port		RCC_APB2Periph_GPIOB
#define GP906_GPIO_Pin_Num_Scl	          GPIO_Pin_10          //PB端口(端口和下面的两个针脚可自定义)
#define GP906_GPIO_Pin_Num_Sda            GPIO_Pin_11
#define GP906_GPIO_Port                   GPIOB






#define SMBUS_SCK_H()	    GP906_GPIO_Port->BSRR = GP906_GPIO_Pin_Num_Scl //置高电平
#define SMBUS_SCK_L()	    GP906_GPIO_Port->BRR = GP906_GPIO_Pin_Num_Scl  //置低电平
#define SMBUS_SDA_H()	    GP906_GPIO_Port->BSRR = GP906_GPIO_Pin_Num_Sda
#define SMBUS_SDA_L()	    GP906_GPIO_Port->BRR = GP906_GPIO_Pin_Num_Sda

#define SMBUS_SDA_PIN()	    GP906_GPIO_Port->IDR & GP906_GPIO_Pin_Num_Sda //读取引脚电平



void SMBus_StartBit(void);
void SMBus_StopBit(void);
void SMBus_SendBit(u8);
u8 SMBus_SendByte(u8);
u8 SMBus_ReceiveBit(void);
u8 SMBus_ReceiveByte(u8);
void SMBus_Delay(u16);
u16 SMBus_ReadMemory(u8, u8);
u8 PEC_Calculation(u8*);


void Gp_906_Init(void);      //引脚初始化
void Gp906_ReadTemp(float *Temp); //获取温度值

#endif

/*********************************END OF FILE*********************************/
