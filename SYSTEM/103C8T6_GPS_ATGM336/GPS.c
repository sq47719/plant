#include "stm32f10x.h"  //包含需要的头文件
#include "gps.h"     //包含需要的头文件



_SaveData Save_Data;

/******************************************
GPS的IO口初始化   根据连接的那个IO口选择对应的串口调用程序

串口1完成GPS数据的接收
********************************************/

void GPS_Uart1_Init()
{
	Usart1_Init(9600);
	clrStruct();
}


/******************************************
GPS的IO口初始化   根据连接的那个IO口选择对应的串口调用程序

串口2完成GPS数据的接收
********************************************/

void GPS_Uart2_Init()
{
	Usart2_Init(9600);
  clrStruct();
}


/******************************************
GPS的IO口初始化   根据连接的那个IO口选择对应的串口调用程序

串口3完成GPS数据的接收
********************************************/

void GPS_Uart3_Init()
{
	Usart3_Init(9600);
  clrStruct();
}


void clrStruct()
{
	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
	memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
	memset(Save_Data.UTCTime, 0, UTCTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
	memset(Save_Data.N_S, 0, N_S_Length);
	memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.E_W, 0, E_W_Length);
}

void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//解析错误
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//解析错误
				}
			}


		}
	}
}
void printGpsBuffer(char *Gps_Data_buffer)
{
	u8 fen,fen1;
		if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			printf("纬度 = ");
			printf("%f",atof(Save_Data.latitude));
      printf("\r\n");
      printf("%d",(int)((atof(Save_Data.latitude)-(int)atof(Save_Data.latitude))*100));
			printf("\r\n");
      fen=(int)((atof(Save_Data.latitude)-(int)atof(Save_Data.latitude))*100);
      *Gps_Data_buffer=(int)atof(Save_Data.latitude)/10000;
      *(Gps_Data_buffer+1)=(int)atof(Save_Data.latitude)%10000/1000;
			*(Gps_Data_buffer+2)=(int)atof(Save_Data.latitude)%1000/100;
			*(Gps_Data_buffer+3)=(int)atof(Save_Data.latitude)%100/10;
	  	*(Gps_Data_buffer+4)=(int)atof(Save_Data.latitude)%10;
      *(Gps_Data_buffer+5)=fen/10;
	 		*(Gps_Data_buffer+6)=fen%10;

			printf("经度 = ");
			printf("%f",atof(Save_Data.longitude));
      printf("\r\n");
      printf("%d",(int)((atof(Save_Data.longitude)-(int)atof(Save_Data.longitude))*100));
			printf("\r\n");
      fen=(int)((atof(Save_Data.longitude)-(int)atof(Save_Data.longitude))*100);
      *(Gps_Data_buffer+7)=(int)atof(Save_Data.longitude)/10000;
      *(Gps_Data_buffer+8)=(int)atof(Save_Data.longitude)%10000/1000;
			*(Gps_Data_buffer+9)=(int)atof(Save_Data.longitude)%1000/100;
			*(Gps_Data_buffer+10)=(int)atof(Save_Data.longitude)%100/10;
	 		*(Gps_Data_buffer+11)=(int)atof(Save_Data.longitude)%10;
      *(Gps_Data_buffer+12)=fen1/10;
	 		*(Gps_Data_buffer+13)=fen1%10;

		}
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}

static double radian(double d)
{
    return d * PI / 180.0;  
}

double get_distance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = radian(lat1);
    double radLat2 = radian(lat2);
    double a = radLat1 - radLat2;
    double b = radian(lng1) - radian(lng2);
    
    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));
    
    dst = dst * EARTH_RADIUS;
	  if(dst<0)
		 {
		   dst=-dst;
		 }
    return dst;
}

void Get_GPS_Data(char *GPS_Data_All_Buffer,char *GPS_Dimen_Data_Buffer,char *GPS_Longtiu_Data_Buffer)
{

   unsigned char i;
	 parseGpsBuffer();
	 printGpsBuffer(GPS_Data_All_Buffer);
	 
	 for(i=0;i<8;i++)
	 {
		 	*(GPS_Dimen_Data_Buffer+i)=*(GPS_Data_All_Buffer+i);
	    *(GPS_Longtiu_Data_Buffer+i)=*(GPS_Data_All_Buffer+7+i);
	 }

	
}





