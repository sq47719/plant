#include "1602.h"
#include "delay.h"
#include "sys.h" 

 

void LCD1602_GPIO_Configuration()
{
	GPIO_InitTypeDef  GPIO_InitStrue;
	//初始化时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LCD1602_GPIO_Port,ENABLE);
	
	//初始化IO口
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStrue.GPIO_Pin=LCD1602_GPIO_Pin_Num_Rs|LCD1602_GPIO_Pin_Num_Rw|LCD1602_GPIO_Pin_Num_E;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LCD1602_GPIO_Port,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Pin=LCD1602_GPIO_Pin_Num0|LCD1602_GPIO_Pin_Num1|LCD1602_GPIO_Pin_Num2|LCD1602_GPIO_Pin_Num3|LCD1602_GPIO_Pin_Num4|LCD1602_GPIO_Pin_Num5|LCD1602_GPIO_Pin_Num6|LCD1602_GPIO_Pin_Num7;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LCD1602_GPIO_Port,&GPIO_InitStrue);
	
   	/* 初始化1602液晶 */
	LCD1602_Write_Cmd(0x38);//16*2显示，5*7点阵，8位数据口
	LCD1602_Write_Cmd(0x0C);//开显示，光标关闭
	LCD1602_Write_Cmd(0x06);//文字不动，地址自动+1
	LCD1602_Write_Cmd(0x01);//清屏

}

/* 向LCD1602液晶写入一字节命令，cmd-待写入命令值 */
void LCD1602_Write_Cmd(u8 cmd)
{
	u16 Temp;
	LCD_RS_Clr();
	LCD_RW_Clr();
	delay_us(800);
	Temp=GPIO_ReadOutputData(LCD1602_GPIO_Port);//读回GPIOA发送寄存器的数据。
  Temp&=0xFF00;//将GPIOA的高8位保留，低8位清0.

  Temp|=(u16)cmd;//将char型变量Send_Com强制转换成short(短整型)，其中高8位由0代替，低8位是Send_Com的值
  GPIO_Write(LCD1602_GPIO_Port,Temp);

	//GPIO_Write(GPIOA,cmd);
	delay_us(500);
	LCD_EN_Set();
	delay_us(3);
	LCD_EN_Clr();
}
/* 向LCD1602液晶写入一字节数据，dat-待写入数据值 */
void LCD1602_Write_Dat(u8 cmd)////////////////////
{
	u16 Temp;
	LCD_RS_Set();
	//LCD_RS_Clr();	
	LCD_RW_Clr();
	delay_us(800);
	Temp=GPIO_ReadOutputData(LCD1602_GPIO_Port);//读回GPIOA发送寄存器的数据。
  Temp&=0xFF00;//将GPIOA的高8位保留，低8位清0.

  //Temp|=(u16)dat;//将char型变量Send_Com强制转换成short(短整型)，其中高8位由0代替，低8位是Send_Com的值
	Temp|=(u16)cmd;
	GPIO_Write(LCD1602_GPIO_Port,Temp);		
	
 	delay_us(500); 
	LCD_EN_Set();
	delay_ms(3);
	LCD_EN_Clr();	
}
//***********************************************************************
//	显示屏字符串写入函数
//***********************************************************************
void write_str(unsigned char x,unsigned char y,unsigned char *s) 
{
    if (y == 0) 
    {
        LCD1602_Write_Cmd(0x80 + x);        //第一行显示
    }
    else 
    {
    	LCD1602_Write_Cmd(0xC0 + x);        //第二行显示
    }
    
    while (*s) 
    {
    	LCD1602_Write_Dat( *s);
    	s ++;
    }
}

//***********************************************************************
//	显示屏单字符写入函数
//***********************************************************************
void write_char(unsigned char x,unsigned char y,unsigned char z) 
{
	
    if (y == 0) 
    {
    	LCD1602_Write_Cmd(0x80 + x);        //第一行显示
    }
    else 
    {
    	LCD1602_Write_Cmd(0xC0 + x);        //第二行显示
    }
    
        LCD1602_Write_Dat(z);  
}
void write_ws(unsigned char x,unsigned char y,unsigned char date)
{ 
	 unsigned char shi,ge;
	 shi=date/10;
	 ge=date%10;
	 if(y==0){
		LCD1602_Write_Cmd(0x80+x);
	 }else{
		LCD1602_Write_Cmd(0x80+0x40+x);
	 }
	 LCD1602_Write_Dat(0x30+shi);
	 LCD1602_Write_Dat(0x30+ge);	
}

void write_num(unsigned char x,unsigned char y,unsigned int date)
{ 
	  unsigned int qian,bai,shi,ge;
	  qian=date/1000;
	  bai=date%1000/100;
	  shi=date%100/10;
	  ge=date%10;
 
	 if(y==0){
		LCD1602_Write_Cmd(0x80+x);
	 }else{
		LCD1602_Write_Cmd(0x80+0x40+x);
	 }
	 LCD1602_Write_Dat(0x30+qian);
	 LCD1602_Write_Dat(0x30+bai);
	 LCD1602_Write_Dat(0x30+shi);
	 LCD1602_Write_Dat(0x30+ge); 	 
}
void delay(u8 z)
{
	u8 x,y;
	for(x=z;x>0;x--)
		for(y=200;y>0;y--);
}




