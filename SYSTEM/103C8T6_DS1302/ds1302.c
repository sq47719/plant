#include "ds1302.h"
#include "delay.h"

//初始化时间定义
u8 time_buf[8] = {0x20,0x23,0x4,0x25,0x16,0x30,0x00,0x00}; //初始时间2023年4月25号16点30分00秒 
void DS1302_GPIO_Init_Write_Time(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_DS1302_GPIO_Port, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = DS1302_GPIO_Pin_CLK | DS1302_GPIO_Pin_DATA |DS1302_GPIO_Pin_RST;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS1302_GPIO_Port, &GPIO_InitStructure);
	
	GPIO_SetBits(DS1302_GPIO_Port, DS1302_GPIO_Pin_DATA);                        //数据端口拉高
	GPIO_ResetBits(DS1302_GPIO_Port, DS1302_GPIO_Pin_CLK | DS1302_GPIO_Pin_RST); //时钟和复位端口置低
	DS1302_Write_Time();
}

//向DS1302写入一个字节数据
void DS1302_Write_Byte(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr & 0xFE;  //最低位置零，写数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //写数据
	{
	  if(data & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //停止DS1302总线
}

//从DS1302读出一个字节数据
u8 DS1302_Read_Byte(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr | 0x01;  //最低位置高，读数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //读数据
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN)
			temp |= 0x80;
		else
			temp &= 0x7F;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //停止DS1302总线
	return temp;
}

//向DS1302写入时间数据
void DS1302_Write_Time(void)
{
  DS1302_Write_Byte(ds1302_control_add, 0x00);      //关闭写保护
  DS1302_Write_Byte(ds1302_sec_add, 0x80);          //暂停时钟
	//DS1302_Write_Byte(ds1302_charger_add, 0xA9);      //涓流充电
	DS1302_Write_Byte(ds1302_year_add,time_buf[1]);		//年 
	DS1302_Write_Byte(ds1302_month_add,time_buf[2]);	//月 
	DS1302_Write_Byte(ds1302_date_add,time_buf[3]);		//日 
	DS1302_Write_Byte(ds1302_hr_add,time_buf[4]);		  //时 
	DS1302_Write_Byte(ds1302_min_add,time_buf[5]);		//分
	DS1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//秒
	DS1302_Write_Byte(ds1302_day_add,1);		//周 
	DS1302_Write_Byte(ds1302_control_add,0x80);		    //打开写保护 
}

//从DS302读出时钟数据
void DS1302_Read_Time(void)  
{
	time_buf[1] = DS1302_Read_Byte(ds1302_year_add);		   //年 
	time_buf[2] = DS1302_Read_Byte(ds1302_month_add);		   //月 
	time_buf[3] = DS1302_Read_Byte(ds1302_date_add);		   //日 
	time_buf[4] = DS1302_Read_Byte(ds1302_hr_add);		     //时 
	time_buf[5] = DS1302_Read_Byte(ds1302_min_add);		     //分 
	time_buf[6] = (DS1302_Read_Byte(ds1302_sec_add))&0x7f; //秒，屏蔽秒的第7位，避免超出59
	time_buf[7] = DS1302_Read_Byte(ds1302_day_add);		     //周 	
}

//DS1302向上层返回时间数据
void DS1302_Get_Time(u8 *time1)
{
	time1[0]=(time_buf[1]>>4);   //年   
  time1[1]=(time_buf[1]&0x0f);   
	time1[2]='-';
  time1[3]=(time_buf[2]>>4);  //月   
  time1[4]=(time_buf[2]&0x0f);   
	time1[5]='-';
  time1[6]=(time_buf[3]>>4);  //日
  time1[7]=(time_buf[3]&0x0f);
	
  time1[8]=(time_buf[4]>>4);   //时   
  time1[9]=(time_buf[4]&0x0f);   
	time1[10]='-';
  time1[11]=(time_buf[5]>>4);  //分   
  time1[12]=(time_buf[5]&0x0f);   
	time1[13]='-';
  time1[14]=(time_buf[6]>>4);  //秒
  time1[15]=(time_buf[6]&0x0f);

}









