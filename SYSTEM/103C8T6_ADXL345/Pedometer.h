#ifndef _Pedometer_H
#define _Pedometer_H




extern _Bool ADXL345_FLAG;  				//读取标志位 利用定时器取200ms读取一次数据 人的步数大概是1S一步
//extern unsigned char START_FLAG;		//开始计步标志位
//extern unsigned char number;

extern unsigned int  STEPS;
//extern unsigned int  time;
										
//float  speed=0;
//float  dist=0;
//float  kalul=0;

void step_counter(void);

#endif
