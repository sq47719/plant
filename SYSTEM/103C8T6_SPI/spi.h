#ifndef __SPI_H
#define __SPI_H
#include "sys.h"


//RFID_CLK       PB13     
//RFID_MOSI      PB15
//RFID_MISO      PB14
				    
#define SPI_Num                          SPI2
#define RCC_APB2Periph_SPI2_GPIO_Port    RCC_APB2Periph_GPIOB
#define RCC_APB1Periph_SPI_Num           RCC_APB1Periph_SPI2
#define SPI2_GPIO_Pin_Num_CLK            GPIO_Pin_13
#define SPI2_GPIO_Pin_Num_MISO           GPIO_Pin_14
#define SPI2_GPIO_Pin_Num_MOSI           GPIO_Pin_15	
#define SPI2_GPIO_Port                   GPIOB
	
void SPI2_Init(void);			                 //��ʼ��SPI2��
void SPI2_SetSpeed(u8 SpeedSet);           //����SPI2�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);          //SPI2���߶�дһ���ֽ�
void SPI1_Init(void);			                 //��ʼ��SPI1��
void SPI1_SetSpeed(u8 SpeedSet);           //����SPI1�ٶ�  		 
u8 SPI1_ReadWriteByte(u8 TxData);          //SPI1���߶�дһ���ֽ�
#endif

