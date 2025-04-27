#ifndef __OLED_I2C_H
#define	__OLED_I2C_H


#include "stm32f10x.h"

#define OLED_ADDRESS	0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78
#define RCC_APB1Periph_OLED4_IIC_Num           RCC_APB1Periph_I2C1
#define RCC_APB2Periph_OLED4_GPIO_Port         RCC_APB2Periph_GPIOB
#define OLED4_GPIO_Pin_Scl                     GPIO_Pin_6
#define OLED4_GPIO_Pin_Sda                     GPIO_Pin_7
#define OLED4_GPIO_Port                        GPIOB
#define OLED4_IIC_Num                          I2C1

void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);   // OLED��ʾ�����ų�ʼ��������������
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y,  char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


/****************************
����OLED��ʾ����ʱ�����µ����ֱ�ӵ��ü���
*****************************/
//	OLED_Init();         //OLED��ʼ��
//	OLED_CLS();          //OLED����
//	OLED_ShowCN(32,2,0);			//С��Ӳ��
//	OLED_ShowCN(32+16,2,1);
//	OLED_ShowCN(32+32,2,2);
//	OLED_ShowCN(32+32+16,2,3);
//	delay_ms(100);
//	OLED_CLS();

//	 /*******��ʾ����**********/
//	OLED_ShowCN(0,0,4);  //����   ���ָ���ʵ����Ҫ�����޸�
//	OLED_ShowCN(0+16,0,5);	

#endif
