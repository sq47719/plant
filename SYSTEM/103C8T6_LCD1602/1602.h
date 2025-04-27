#ifndef   __1602_H
#define   __1602_H
#include "sys.h" 



#define RCC_APB2Periph_LCD1602_GPIO_Port     RCC_APB2Periph_GPIOA
#define LCD1602_GPIO_Pin_Num_Rs              GPIO_Pin_8
#define LCD1602_GPIO_Pin_Num_Rw              GPIO_Pin_11
#define LCD1602_GPIO_Pin_Num_E               GPIO_Pin_12
#define LCD1602_GPIO_Pin_Num0                GPIO_Pin_0
#define LCD1602_GPIO_Pin_Num1                GPIO_Pin_1
#define LCD1602_GPIO_Pin_Num2                GPIO_Pin_2
#define LCD1602_GPIO_Pin_Num3                GPIO_Pin_3
#define LCD1602_GPIO_Pin_Num4                GPIO_Pin_4
#define LCD1602_GPIO_Pin_Num5                GPIO_Pin_5
#define LCD1602_GPIO_Pin_Num6                GPIO_Pin_6
#define LCD1602_GPIO_Pin_Num7                GPIO_Pin_7
#define LCD1602_GPIO_Port                    GPIOA

//1602液晶指令/数据选择引脚
#define	LCD_RS_Set()	GPIO_SetBits(LCD1602_GPIO_Port, LCD1602_GPIO_Pin_Num_Rs)
#define	LCD_RS_Clr()	GPIO_ResetBits(LCD1602_GPIO_Port, LCD1602_GPIO_Pin_Num_Rs)

//1602液晶读写引脚
#define	LCD_RW_Set()	GPIO_SetBits(LCD1602_GPIO_Port, LCD1602_GPIO_Pin_Num_Rw)
#define	LCD_RW_Clr()	GPIO_ResetBits(LCD1602_GPIO_Port, LCD1602_GPIO_Pin_Num_Rw)

//1602液晶使能引脚
#define	LCD_EN_Set()	GPIO_SetBits(LCD1602_GPIO_Port, LCD1602_GPIO_Pin_Num_E)
#define	LCD_EN_Clr()	GPIO_ResetBits(LCD1602_GPIO_Port, LCD1602_GPIO_Pin_Num_E)





void LCD1602_GPIO_Configuration(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void write_str(unsigned char x,unsigned char y,unsigned char *s);
void write_char(unsigned char x,unsigned char y,unsigned char z);
void write_ws(unsigned char x,unsigned char y,unsigned char date);
void write_num(unsigned char x,unsigned char y,unsigned int date);
void delay(u8 z);



#endif

