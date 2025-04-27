#include "Control_Report_To_Police.h"

u16 Servor_CPWM_Set_Buffer[9]={1500,1500,1500,1500,1500,1500,1500,1500,1500};

/************************************
OLED显示屏
************************************/
void OLED_Display_Cotrol(void)  //系统显示控制功能实现   OLED显示
{
	
static unsigned short timeCount = 0;	//发送间隔变量
static u8 temperature=28,humidity=29;
static char p1[16]=" "; 
static float cotwo,guan;
static int a=30,b=-1,c=80,d=40,m=1,n=0,g,coo,guang,led_on,moter_on,water_on,turan;
		char Test_Mqqt_Buffer[512]="";  //为了接收按钮按下后阿里云传输的数据信息
	  char Test_Them_WATER_ON_Buffer[4]="999";
	  char Test_Them_WATER_OFF_Buffer[4]="888";
	  char Test_Them_WATER_OF_Buffer[4]="777";
		char Test_Them_WATER_OA_Buffer[4]="666";
		char Test_Them_WATER_OB_Buffer[4]="555";
		char Test_Them_WATER_OC_Buffer[4]="444";
		char Test_Them_WATER_OD_Buffer[4]="333";
		char Test_Them_WATER_OE_Buffer[4]="222";
		char Test_Them_WATER_OK_Buffer[4]="111";
		char Test_Them_WATER_OG_Buffer[4]="112";
	  char Test_Them_WATER_OH_Buffer[4]="113";
	  char Test_Them_WATER_OI_Buffer[4]="114";
//  char Test_Them_WATER_OJ_Buffer[4]="115";
		u16 Test_Mqqt_Num=0;	

			
  if(connectFlag == 1) 
	{ 
			 g=KEY_Scan(0);
		    if(g==KEY0_PRES){n++;OLED_CLS();}//清屏 
				if(n==6)n=0;
				if(n==0)
				{
					//显示界面
					OLED_ShowCN(32,2,17);
					OLED_ShowCN(48,2,18);
					OLED_ShowCN(64,2,15);
					OLED_ShowCN(80,2,16);
					delay_ms(1000);
					delay_ms(1000);
					OLED_CLS();
					n=1;
				}
		    if(n==1)
			{
      //温度
      OLED_ShowCN(0,0,0);
			OLED_ShowCN(16,0,2);
			DHT11_Read_Data(&temperature,&humidity);
			sprintf((char*)p1,":%d",temperature);	
      OLED_ShowStr(32,0,p1,2);
			//湿度
			OLED_ShowCN(64,0,1);
			OLED_ShowCN(80,0,2);
			sprintf((char*)p1,":%d ",humidity);
			OLED_ShowStr(96,0,p1,2);
			//土壤湿度
			OLED_ShowCN(0,2,3);
			OLED_ShowCN(16,2,4);
			OLED_ShowCN(32,2,1);
			OLED_ShowCN(48,2,2);
			Get_adc1(&turan);
			sprintf((char*)p1,":%dHL ",turan);
			OLED_ShowStr(64,2,p1,2);
		  //二样化痰
			OLED_ShowCN(0,4,5);
			OLED_ShowCN(16,4,6);
			OLED_ShowCN(32,4,7);
			OLED_ShowCN(48,4,8);
			Get_adc2(&cotwo);
			coo=(int)cotwo;
			sprintf((char*)p1,":%dMMP ",coo);
			OLED_ShowStr(64,4,p1,2);
			//光照强度
			OLED_ShowCN(0,6,10);
			OLED_ShowCN(16,6,11);
			OLED_ShowCN(32,6,12);
			OLED_ShowCN(48,6,2);
		  Get_adc(&guan);
			guang=99-(int)guan;
			sprintf((char*)p1,":%dLM ",guang);
			OLED_ShowStr(64,6,p1,2);
		}
			if(n==2)
				{
					//阈值界面
				OLED_ShowCN(32,2,13);
				OLED_ShowCN(48,2,14);
				OLED_ShowCN(64,2,15);
				OLED_ShowCN(80,2,16);
					delay_ms(1000);
					delay_ms(1000);
					OLED_CLS();
					n=3;
				}	
		
			if(n==3)
			{
				sprintf((char*)p1,"%d",m);
			  OLED_ShowStr(112,0,p1,2);
				if(g==KEY1_PRES){m++;}
				if(m==5)m=1;
				switch(m)
				{
						case 1:
										if(g==KEY2_PRES)a++;
						        if(g==KEY3_PRES)a--;
										break;
						case 2:
										if(g==KEY2_PRES)b++;
						        if(g==KEY3_PRES)b--;
										break;
						case 3:
										if(g==KEY2_PRES)c++;
						        if(g==KEY3_PRES)c--;
										break;
						case 4:
										if(g==KEY2_PRES)d++;
						        if(g==KEY3_PRES)d--;
										break;
						default:break;
				}
			//温度阈值

      OLED_ShowCN(0,0,0);
			OLED_ShowCN(16,0,2);
			OLED_ShowCN(32,0,13);
			OLED_ShowCN(48,0,14);
			sprintf((char*)p1,":%dC ",a);
			OLED_ShowStr(64,0,p1,2);
      //湿度
   
      OLED_ShowCN(0,2,3);
			OLED_ShowCN(16,2,4);
			OLED_ShowCN(32,2,1);
			OLED_ShowCN(48,2,2);
			sprintf((char*)p1,":%dHL ",b);
			OLED_ShowStr(64,2,p1,2);
			//coo

      OLED_ShowStr(0,4,"CO2",2);
			OLED_ShowCN(32,4,13);
			OLED_ShowCN(48,4,14);
			sprintf((char*)p1,":%dPMM ",c);
			OLED_ShowStr(64,4,p1,2);
			//光
			OLED_ShowCN(0,6,10);
			OLED_ShowCN(16,6,11);		
			OLED_ShowCN(32,6,13);
			OLED_ShowCN(48,6,14);
			sprintf((char*)p1,":%dLM ",d);
			OLED_ShowStr(64,6,p1,2);
			
		}
				if(n==4)
				{
				//控制界面
				OLED_ShowCN(32,2,19);
				OLED_ShowCN(48,2,20);
				OLED_ShowCN(64,2,15);
				OLED_ShowCN(80,2,16);
					delay_ms(1000);
					delay_ms(1000);
					OLED_CLS();
					n=5;
				}	
      if(n==5)
			{
				if(g==KEY1_PRES)moter_on++;
				if(moter_on==2)moter_on=0;
				//风扇
				OLED_ShowCN(0,0,24);
				OLED_ShowCN(16,0,25);
				OLED_ShowStr(32,0,":",2);
				if(moter_on==1){OLED_ShowCN(48,0,21);}else{	OLED_ShowCN(48,0,22);}
				//水泵
				if(g==KEY2_PRES)water_on++;
				if(water_on==2)water_on=0;
				OLED_ShowCN(0,2,26);
				OLED_ShowCN(16,2,27);
				OLED_ShowStr(32,2,":",2);
				if(water_on==1){OLED_ShowCN(48,2,21);}else{	OLED_ShowCN(48,2,22);}
				
				//灯光
				if(g==KEY3_PRES)led_on++;
				if(led_on==2)led_on=0;
				OLED_ShowCN(0,4,23);
				OLED_ShowCN(16,4,10);
				OLED_ShowStr(32,4,":",2);
				if(led_on==1){OLED_ShowCN(48,4,21);}else{	OLED_ShowCN(48,4,22);}
		
			
			}
			//控制功能
			if(moter_on==1||coo>c||temperature>a){Relay_0=1;}else{Relay_0=0;}
			
			if(water_on==1||turan<b){Relay_1=1;}else{Relay_1=0;}
			
			if(led_on==1||guang<d){Led1_0=0;}else{Led1_0=1;}
	
			
			timeCount++; 
			if(timeCount==20){timeCount=0;send_data(&temperature,&humidity,&turan,&coo,&guang,&a,&b,&c,&d,&n);}

			if(MQTT_TxDataOutPtr != MQTT_TxDataInPtr) //if成立的话，说明发送缓冲区有数据了
			{                
				if((MQTT_TxDataOutPtr[2] == 0x10)||((MQTT_TxDataOutPtr[2] == 0x82)&&(connectPackFlag == 1))||(subcribePackFlag == 1)) //10连接报文  82客户端订阅请求
				{    
					if (MQTT_TxDataOutPtr[2] == 0x30) 
					{	
					}
					else 
					{
					}
					
					MQTT_TxData(MQTT_TxDataOutPtr);							//发送数据
					MQTT_TxDataOutPtr += BUFF_UNIT;						//指针下移
					if(MQTT_TxDataOutPtr == MQTT_TxDataEndPtr)				//如果指针到缓冲区尾部了
					{ 
						MQTT_TxDataOutPtr = MQTT_TxDataBuf[0];				//指针归位到缓冲区开头
					}	
					
				} 				
			}
			/*-------------------------------------------------------------*/
			/*                     处理接收缓冲区数据                      */
			/*-------------------------------------------------------------*/
			if(MQTT_RxDataOutPtr != MQTT_RxDataInPtr) //if成立的话，说明接收缓冲区有数据了	
			{												
				/*-----------------------------------------------------*/
				/*                    处理CONNACK报文                  */
				/*-----------------------------------------------------*/				
				//if判断，如果第一个字节是0x20，表示收到的是CONNACK报文//固定报头     服务端到客户端  连接报文确认
				//接着我们要判断第4个字节，看看CONNECT报文是否成功      客户端到服务端	客户端请求连接服务端		
				if(MQTT_RxDataOutPtr[2] == 0x20)//连接确认
				{             			
					switch(MQTT_RxDataOutPtr[5])//MQTT-3.1.1-CN  38-39页
					{					   
						case 0x00 : 
									connectPackFlag = 1;									//CONNECT报文成功，订阅报文可发
									break;														//跳出分支case 0x00                                              
						case 0x01 :
									connectFlag = 0;											//connectFlag置零，重启连接
									break;														//跳出分支case 0x01   
						case 0x02 : 
									connectFlag = 0;                                            //connectFlag置零，重启连接
									break; 														//跳出分支case 0x02 
						case 0x03 : 
									connectFlag = 0;											//connectFlag置零，重启连接
									break;														//跳出分支case 0x03
						case 0x04 : 
									connectFlag = 0;											//connectFlag置零，重启连接						
									break;														//跳出分支case 0x04
						case 0x05 :
									connectFlag = 0;											//connectFlag置零，重启连接						
									break;														//跳出分支case 0x05 		
						default   : 
									connectFlag = 0;											//connectFlag置零，重启连接					
									break;														//跳出分支case default 								
					}				
			  }			
				//if判断，第一个字节是0x90，表示收到的是SUBACK报文
				//接着我们要判断订阅回复，看看是不是成功
				else if(MQTT_RxDataOutPtr[2] == 0x90)//服务端订阅确认
				{ 
					switch(MQTT_RxDataOutPtr[6])
					{					
						case 0x00 :
						case 0x01 : 
									subcribePackFlag = 1;				//subcribePackFlag置1，表示订阅报文成功，其他报文可发送
									pingFlag = 0;						//pingFlag清零
									TIM3_ENABLE_30S();					//启动30s的PING定时器	
									break;								//跳出分支                                             
						default: 
									connectFlag = 0;					//connectFlag置零，重启连接
									break;								//跳出分支 								
						}					
			    }
				//if判断，第一个字节是0xD0，表示收到的是PINGRESP报文
				else if(MQTT_RxDataOutPtr[2] == 0xD0)
				{ 
					if(pingFlag == 1)
					{                   						        //如果pingFlag=1，表示第一次发送
						 pingFlag = 0;    				       			//要清除pingFlag标志
					}
					else if(pingFlag > 1)	
					{ 				 									//如果pingFlag>1，表示是多次发送了，而且是2s间隔的快速发送
						pingFlag = 0;     				      			//要清除pingFlag标志
						TIM3_ENABLE_30S(); 				      			//PING定时器重回30s的时间
					}				
				}	
				//if判断，如果第一个字节是0x30，表示收到的是服务器发来的推送数据
				//我们要提取控制命令
				else if((MQTT_RxDataOutPtr[2] == 0x30))
			    { 
					     MQTT_DealPushdata_Qs0(MQTT_RxDataOutPtr);   //处理等级0推送数据
								for(Test_Mqqt_Num=0;Test_Mqqt_Num<512;Test_Mqqt_Num++)
							{
								 Test_Mqqt_Buffer[Test_Mqqt_Num]=MQTT_RxDataOutPtr[Test_Mqqt_Num];
							}
							 Test_Mqqt_Num=strlen(Test_Mqqt_Buffer);
				}									
				MQTT_RxDataOutPtr += BUFF_UNIT;                //指针下移
				if(MQTT_RxDataOutPtr == MQTT_RxDataEndPtr)      //如果指针到缓冲区尾部了
				{
					MQTT_RxDataOutPtr = MQTT_RxDataBuf[0];      //指针归位到缓冲区开头              
				}		          
			}//处理接收缓冲区数据的else if分支结尾
						
			/*---------------------------------------------------------------------------------------------------------------------*/
			/*                    							                 处理命令缓冲区数据                   		          			         */
			/*---------------------------------------------------------------------------------------------------------------------*/
			if(MQTT_CMDOutPtr != MQTT_CMDInPtr)							  //if成立的话，说明命令缓冲区有数据了	
			{    
				
					if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_ON_Buffer))
				{
					a++;

				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OFF_Buffer))
				{
					a--;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OF_Buffer))
				{
					b++;
				}
					if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OA_Buffer))
				{
					b--;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OB_Buffer))
				{
					c++;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OC_Buffer))
				{
					c--;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OD_Buffer))
				{
					d++;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OE_Buffer))
				{
					d--;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OK_Buffer))
				{
					moter_on++;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OG_Buffer))
				{
					water_on++;
				}
				
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OH_Buffer))
				{
		      led_on++;
				}
				if(isSubstring(Test_Mqqt_Buffer,Test_Them_WATER_OI_Buffer))
				{
					n++;
					OLED_CLS();
				}
				
				
				MQTT_CMDOutPtr[238]=0;
				MQTT_CMDOutPtr += BUFF_UNIT;				//指针下移
				if(MQTT_CMDOutPtr == MQTT_CMDEndPtr)	    //如果指针到缓冲区尾部了
				MQTT_CMDOutPtr = MQTT_CMDBuf[0];			//指针归位到缓冲区开头	
							
			}	
		}
	/*--------------------------------------------------------------------*/
	/*      connectFlag=0同服务器断开了连接,我们要重启连接服务器            */
	/*--------------------------------------------------------------------*/
		else
		{ 
			TIM_Cmd(TIM4, DISABLE);                        //关闭TIM4 
			TIM_Cmd(TIM3, DISABLE);                        //关闭TIM3  
			WiFi_RxCounter = 0;                            //WiFi接收数据量变量清零                        
			memset(WiFi_RX_BUF, 0, WiFi_RXBUFF_SIZE);      //清空WiFi接收缓冲区 
			if(WiFi_Connect_IoTServer() == 0)			   //如果WiFi连接云服务器函数返回0，表示正确，进入if，配ESP8266模块
			{   			     
				connectFlag = 1;                           //connectFlag置1，表示连接成功	
				WiFi_RxCounter = 0;                        //WiFi接收数据量变量清零                        
				memset(WiFi_RX_BUF, 0, WiFi_RXBUFF_SIZE);  //清空WiFi接收缓冲区 
 				MQTT_Buff_ReInit();                          //初始化发送缓冲区  
			}				
		}

}


//两个字符串比较   判断str 字符串中是否包含substr字符串

_Bool isSubstring(const char* str, const char* substr) {
    int i, j;
    int str_len =512;   //这个值正常是str字符串的长度   但是因为内部包含换行符  算的不准因此设定成固定的
    int substr_len = strlen(substr);

    for (i = 0; i <= str_len - substr_len; i++) {
        for (j = 0; j < substr_len; j++) {
            if (str[i + j] != substr[j])
                break;
        }
        if (j == substr_len)
            return true;
    }

    return false;
}

//两个字符串进行拼接的函数

void concatenateStrings(const char* str1, const char* str2, char* result) {
    int i = 0;
    int j = 0;

    while (str1[i] != '\0') {
        result[j] = str1[i];
        i++;
        j++;
    }

    i = 0;
    while (str2[i] != '\0') {
        result[j] = str2[i];
        i++;
        j++;
    }
    result[j] = '\0';
}
