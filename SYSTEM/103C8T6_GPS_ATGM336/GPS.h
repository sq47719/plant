
#ifndef __GPS_H
#define __GPS_H

#include "stdio.h"      
#include "stdarg.h"		 
#include "string.h"
#include  <stdlib.h>
#include  <math.h>
#include "usart.h"
#include "usart2.h"
#include "usart3.h"
		


//定义数组长度
#define GPS_Buffer_Length         80
#define UTCTime_Length            11
#define latitude_Length           11
#define N_S_Length                2
#define longitude_Length          12
#define E_W_Length                2 

#define PI                      3.1415926
#define EARTH_RADIUS            6378137    //根据坐标系定义的

#define false                     0
#define true                      1

typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//是否获取到GPS数据
	char isParseData;	//是否解析完成
	char UTCTime[UTCTime_Length];		//UTC时间
	char latitude[latitude_Length];		//纬度
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//经度
	char E_W[E_W_Length];		//E/W
	char isUsefull;		//定位信息是否有效
} _SaveData;

extern _SaveData Save_Data;   //在串口中断中完成对GPS数据的读取存储




void GPS_Uart1_Init(void);  //GPS串口1接收IO初始化   根据接收GPS数据选择的串口来定调用哪个初始化函数
void GPS_Uart2_Init(void);  //GPS串口2接收IO初始化   根据接收GPS数据选择的串口来定调用哪个初始化函数
void GPS_Uart3_Init(void);  //GPS串口3接收IO初始化   根据接收GPS数据选择的串口来定调用哪个初始化函数



void printGpsBuffer(char *Gps_Data_buffer);
void parseGpsBuffer(void);

/*********************************
用以下函数将经纬度采集存储在数组之后，
需要进行字符串的转换
*********************************/
void Get_GPS_Data(char *GPS_Data_All_Buffer,char *GPS_Dimen_Data_Buffer,char *GPS_Longtiu_Data_Buffer);                         //采集处理GPS数据   要知道经纬度信息调用该函数
double get_distance(double lat1, double lng1, double lat2, double lng2);  //计算距离  

void clrStruct(void);     



#endif


