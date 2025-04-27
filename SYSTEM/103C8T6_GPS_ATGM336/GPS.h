
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
		


//�������鳤��
#define GPS_Buffer_Length         80
#define UTCTime_Length            11
#define latitude_Length           11
#define N_S_Length                2
#define longitude_Length          12
#define E_W_Length                2 

#define PI                      3.1415926
#define EARTH_RADIUS            6378137    //��������ϵ�����

#define false                     0
#define true                      1

typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//�Ƿ��ȡ��GPS����
	char isParseData;	//�Ƿ�������
	char UTCTime[UTCTime_Length];		//UTCʱ��
	char latitude[latitude_Length];		//γ��
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//����
	char E_W[E_W_Length];		//E/W
	char isUsefull;		//��λ��Ϣ�Ƿ���Ч
} _SaveData;

extern _SaveData Save_Data;   //�ڴ����ж�����ɶ�GPS���ݵĶ�ȡ�洢




void GPS_Uart1_Init(void);  //GPS����1����IO��ʼ��   ���ݽ���GPS����ѡ��Ĵ������������ĸ���ʼ������
void GPS_Uart2_Init(void);  //GPS����2����IO��ʼ��   ���ݽ���GPS����ѡ��Ĵ������������ĸ���ʼ������
void GPS_Uart3_Init(void);  //GPS����3����IO��ʼ��   ���ݽ���GPS����ѡ��Ĵ������������ĸ���ʼ������



void printGpsBuffer(char *Gps_Data_buffer);
void parseGpsBuffer(void);

/*********************************
�����º�������γ�Ȳɼ��洢������֮��
��Ҫ�����ַ�����ת��
*********************************/
void Get_GPS_Data(char *GPS_Data_All_Buffer,char *GPS_Dimen_Data_Buffer,char *GPS_Longtiu_Data_Buffer);                         //�ɼ�����GPS����   Ҫ֪����γ����Ϣ���øú���
double get_distance(double lat1, double lng1, double lat2, double lng2);  //�������  

void clrStruct(void);     



#endif


