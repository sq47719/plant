//////////////////////////////////////////////////////////////////////////////////	 
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA5（SCL）
//              D1   接PA6（SDA）
//              RES  接随开发板复位工作了  PA1
//              DC   接PA4
//              CS   接PA0               
//              ----------------------------------------------------------------
//All rights reserved
//******************************************************************************/

#ifndef __OLED_SPI_H
#define __OLED_SPI_H			  	 
#include "sys.h"
#include "stdlib.h"	 




//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------OLED端口定义----------------  	

#define RCC_APB2Periph_OLED7_GPIO_Port         RCC_APB2Periph_GPIOA
#define OLED7_GPIO_Pin_Scl                     GPIO_Pin_5
#define OLED7_GPIO_Pin_Sda                     GPIO_Pin_6
#define OLED7_GPIO_Pin_Res                     GPIO_Pin_1
#define OLED7_GPIO_Pin_Dc                      GPIO_Pin_4
#define OLED7_GPIO_Pin_Cs                      GPIO_Pin_0
#define OLED7_GPIO_Port                        GPIOA



#define  OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_0)      //CS
#define  OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define  OLED_DC_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)      //DC
#define  OLED_DC_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define  OLED_SDIN_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_6)    //MOSI
#define  OLED_SDIN_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_6)

#define  OLED_RST_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_1)     //RES
#define  OLED_RST_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_1)
 		     
#define OLED_SCLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_5)     //CLK
#define OLED_SCLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_5)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数

void OLED_Spi_Init(void);
void OLED_Clear_Spi(void);
void OLED_ShowCHinese_Spi(u8 x,u8 y,u8 no);

void OLED_WR_Byte_Spi(u8 dat,u8 cmd);	    
void OLED_Display_On_Spi(void);
void OLED_Display_Off_Spi(void);	   							   		    
void OLED_Set_Cursor_Spi(u8 x,u8 y);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar_Spi(u8 x,u8 y,char chr);
void OLED_P32x64Str_Spi(u8 x, u8 y,u8 dat);
void OLED_P8x16Str_Spi(u8 x, u8 y,u8 dat);
void OLED_ShowNum_Spi(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString_Spi(u8 x,u8 y, char *p);	 
void OLED_Set_Pos_Spi(unsigned char x, unsigned char y);
void OLED_ShowCHinese_Spi(u8 x,u8 y,u8 no);
void OLED_Spi_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
#endif  
	 



