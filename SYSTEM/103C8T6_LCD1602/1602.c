#include "1602.h"
#include "delay.h"
#include "sys.h" 

 

void LCD1602_GPIO_Configuration()
{
	GPIO_InitTypeDef  GPIO_InitStrue;
	//��ʼ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LCD1602_GPIO_Port,ENABLE);
	
	//��ʼ��IO��
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;  //�������
	GPIO_InitStrue.GPIO_Pin=LCD1602_GPIO_Pin_Num_Rs|LCD1602_GPIO_Pin_Num_Rw|LCD1602_GPIO_Pin_Num_E;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LCD1602_GPIO_Port,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Pin=LCD1602_GPIO_Pin_Num0|LCD1602_GPIO_Pin_Num1|LCD1602_GPIO_Pin_Num2|LCD1602_GPIO_Pin_Num3|LCD1602_GPIO_Pin_Num4|LCD1602_GPIO_Pin_Num5|LCD1602_GPIO_Pin_Num6|LCD1602_GPIO_Pin_Num7;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LCD1602_GPIO_Port,&GPIO_InitStrue);
	
   	/* ��ʼ��1602Һ�� */
	LCD1602_Write_Cmd(0x38);//16*2��ʾ��5*7����8λ���ݿ�
	LCD1602_Write_Cmd(0x0C);//����ʾ�����ر�
	LCD1602_Write_Cmd(0x06);//���ֲ�������ַ�Զ�+1
	LCD1602_Write_Cmd(0x01);//����

}

/* ��LCD1602Һ��д��һ�ֽ����cmd-��д������ֵ */
void LCD1602_Write_Cmd(u8 cmd)
{
	u16 Temp;
	LCD_RS_Clr();
	LCD_RW_Clr();
	delay_us(800);
	Temp=GPIO_ReadOutputData(LCD1602_GPIO_Port);//����GPIOA���ͼĴ��������ݡ�
  Temp&=0xFF00;//��GPIOA�ĸ�8λ��������8λ��0.

  Temp|=(u16)cmd;//��char�ͱ���Send_Comǿ��ת����short(������)�����и�8λ��0���棬��8λ��Send_Com��ֵ
  GPIO_Write(LCD1602_GPIO_Port,Temp);

	//GPIO_Write(GPIOA,cmd);
	delay_us(500);
	LCD_EN_Set();
	delay_us(3);
	LCD_EN_Clr();
}
/* ��LCD1602Һ��д��һ�ֽ����ݣ�dat-��д������ֵ */
void LCD1602_Write_Dat(u8 cmd)////////////////////
{
	u16 Temp;
	LCD_RS_Set();
	//LCD_RS_Clr();	
	LCD_RW_Clr();
	delay_us(800);
	Temp=GPIO_ReadOutputData(LCD1602_GPIO_Port);//����GPIOA���ͼĴ��������ݡ�
  Temp&=0xFF00;//��GPIOA�ĸ�8λ��������8λ��0.

  //Temp|=(u16)dat;//��char�ͱ���Send_Comǿ��ת����short(������)�����и�8λ��0���棬��8λ��Send_Com��ֵ
	Temp|=(u16)cmd;
	GPIO_Write(LCD1602_GPIO_Port,Temp);		
	
 	delay_us(500); 
	LCD_EN_Set();
	delay_ms(3);
	LCD_EN_Clr();	
}
//***********************************************************************
//	��ʾ���ַ���д�뺯��
//***********************************************************************
void write_str(unsigned char x,unsigned char y,unsigned char *s) 
{
    if (y == 0) 
    {
        LCD1602_Write_Cmd(0x80 + x);        //��һ����ʾ
    }
    else 
    {
    	LCD1602_Write_Cmd(0xC0 + x);        //�ڶ�����ʾ
    }
    
    while (*s) 
    {
    	LCD1602_Write_Dat( *s);
    	s ++;
    }
}

//***********************************************************************
//	��ʾ�����ַ�д�뺯��
//***********************************************************************
void write_char(unsigned char x,unsigned char y,unsigned char z) 
{
	
    if (y == 0) 
    {
    	LCD1602_Write_Cmd(0x80 + x);        //��һ����ʾ
    }
    else 
    {
    	LCD1602_Write_Cmd(0xC0 + x);        //�ڶ�����ʾ
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




