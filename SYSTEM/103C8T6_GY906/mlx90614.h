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
��Ȩ��С��Ӳ��
���ںţ�΢��������С��Ӳ�����ڹ��ں���������������
************************************************/		

#define ACK	 0 //Ӧ��
#define	NACK 1 //��Ӧ��
#define SA				0x00 //Slave address ����MLX90614ʱ��ַΪ0x00,���ʱ��ַĬ��Ϊ0x5a
#define RAM_ACCESS		0x00 //RAM access command RAM��ȡ����
#define EEPROM_ACCESS	0x20 //EEPROM access command EEPROM��ȡ����
#define RAM_TOBJ1		0x07 //To1 address in the eeprom Ŀ��1�¶�,��⵽�ĺ����¶� -70.01 ~ 382.19��


/**************������ز�������***********
���ڱ�ģ������IICЭ����ͨ��ģ��ʱ��ķ�ʽʵ�֣�
��������������Ŷ�����Խ���������ģ�����ͨIO��Ҳ��
******************************************/

#define RCC_APB2Periph_GP906_GPIO_Port		RCC_APB2Periph_GPIOB
#define GP906_GPIO_Pin_Num_Scl	          GPIO_Pin_10          //PB�˿�(�˿ں������������ſ��Զ���)
#define GP906_GPIO_Pin_Num_Sda            GPIO_Pin_11
#define GP906_GPIO_Port                   GPIOB






#define SMBUS_SCK_H()	    GP906_GPIO_Port->BSRR = GP906_GPIO_Pin_Num_Scl //�øߵ�ƽ
#define SMBUS_SCK_L()	    GP906_GPIO_Port->BRR = GP906_GPIO_Pin_Num_Scl  //�õ͵�ƽ
#define SMBUS_SDA_H()	    GP906_GPIO_Port->BSRR = GP906_GPIO_Pin_Num_Sda
#define SMBUS_SDA_L()	    GP906_GPIO_Port->BRR = GP906_GPIO_Pin_Num_Sda

#define SMBUS_SDA_PIN()	    GP906_GPIO_Port->IDR & GP906_GPIO_Pin_Num_Sda //��ȡ���ŵ�ƽ



void SMBus_StartBit(void);
void SMBus_StopBit(void);
void SMBus_SendBit(u8);
u8 SMBus_SendByte(u8);
u8 SMBus_ReceiveBit(void);
u8 SMBus_ReceiveByte(u8);
void SMBus_Delay(u16);
u16 SMBus_ReadMemory(u8, u8);
u8 PEC_Calculation(u8*);


void Gp_906_Init(void);      //���ų�ʼ��
void Gp906_ReadTemp(float *Temp); //��ȡ�¶�ֵ

#endif

/*********************************END OF FILE*********************************/
