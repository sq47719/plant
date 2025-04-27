#include "oled_Spi.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"


//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;

//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte_Spi(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

	void OLED_Set_Pos_Spi(u8 x, u8 y) 
{ 
	OLED_WR_Byte_Spi(0xb0+y,OLED_CMD);
	OLED_WR_Byte_Spi((((x)&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte_Spi(((x)&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On_Spi(void)
{
	OLED_WR_Byte_Spi(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte_Spi(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte_Spi(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off_Spi(void)
{
	OLED_WR_Byte_Spi(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte_Spi(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte_Spi(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear_Spi(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte_Spi (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte_Spi (0x02,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte_Spi (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte_Spi(0,OLED_DATA); 
	} //更新显示
}


void OLED_Set_Cursor_Spi(u8 x,u8 y)
{

//   unsigned char  pos;
//   if (y==0)
//     {
//			 x=8;
//		 
//		 }
//   else if (y==16)
//     {x=8;}
//   else if (y==32)
//     {x=8;}
//   else if (y==48)
//     {x=8;}
  // pos = x+y ;  
     //显示地址
    OLED_Set_Pos_Spi( x,  y);
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar_Spi(u8 x,u8 y,char chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos_Spi(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte_Spi(F8X16A_Spi[c*16+i],OLED_DATA);
			OLED_Set_Pos_Spi(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte_Spi(F8X16A_Spi[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos_Spi(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte_Spi(F6x8_Spi[c][i],OLED_DATA);
				
			}
}

void OLED_P32x64Str_Spi(u8 x, u8 y,u8 dat)
{
	unsigned char i=0;
	unsigned int adder=64*dat;
		
		if(x>128){x=0;y++;}
		OLED_Set_Pos_Spi(x,y);
		for(i=0;i<16;i++)
		{
		OLED_WR_Byte_Spi(F32X64[adder],OLED_DATA);	
  		adder += 1;
		}
		
		OLED_Set_Pos_Spi(x,y+1);
		for(i=0;i<16;i++)
		{
		OLED_WR_Byte_Spi(F32X64[adder],OLED_DATA);		
  		adder += 1;
		}

		OLED_Set_Pos_Spi(x,y+2);
		for(i=0;i<16;i++)
		{
		OLED_WR_Byte_Spi(F32X64[adder],OLED_DATA);		
  		adder += 1;
		}
		
		OLED_Set_Pos_Spi(x,y+3);
		for(i=0;i<16;i++)
		{
		OLED_WR_Byte_Spi(F32X64[adder],OLED_DATA);		
  		adder += 1;
		}
		//x+=1;
}

void OLED_P8x16Str_Spi(u8 x, u8 y,u8 dat)
{
	unsigned char i=0;
	
		
		if(x>120){x=0;y++;}
		OLED_Set_Pos_Spi(x,y);
		for(i=0;i<8;i++)
		OLED_WR_Byte_Spi(F8X16_Spi[dat*16+i],OLED_DATA);
		OLED_Set_Pos_Spi(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte_Spi(F8X16_Spi[dat*16+i+8],OLED_DATA);
		x+=8;
	
	
}



//m^n函数
u32 oled_pow_Spi(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum_Spi(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow_Spi(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar_Spi(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar_Spi(x+(size/2)*t,y,temp+'0'); 
	}
} 
//显示一个字符号串
void OLED_ShowString_Spi(u8 x,u8 y,char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar_Spi(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese_Spi(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos_Spi(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte_Spi(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos_Spi(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte_Spi(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}





/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_Spi_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos_Spi(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte_Spi(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//初始化SSD1306					    
void OLED_Spi_Init(void)
{ 	 		 
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_OLED7_GPIO_Port, ENABLE);//使能时钟
  	
	//GPIO初始化设置
  GPIO_InitStructure.GPIO_Pin = OLED7_GPIO_Pin_Scl|OLED7_GPIO_Pin_Sda|OLED7_GPIO_Pin_Res|OLED7_GPIO_Pin_Dc | OLED7_GPIO_Pin_Cs ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //浮空输入	GPIO_Mode_IN_FLOATING 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
	GPIO_Init(OLED7_GPIO_Port, &GPIO_InitStructure);   //初始化GPIOA端口
	
  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(200);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte_Spi(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte_Spi(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte_Spi(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte_Spi(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte_Spi(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte_Spi(0xff,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte_Spi(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte_Spi(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte_Spi(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte_Spi(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte_Spi(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte_Spi(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte_Spi(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte_Spi(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte_Spi(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte_Spi(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte_Spi(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte_Spi(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte_Spi(0x12,OLED_CMD);
	OLED_WR_Byte_Spi(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte_Spi(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte_Spi(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte_Spi(0x02,OLED_CMD);//
	OLED_WR_Byte_Spi(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte_Spi(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte_Spi(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte_Spi(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte_Spi(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte_Spi(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear_Spi();
	OLED_Set_Pos_Spi(0,0); 	
}  






























