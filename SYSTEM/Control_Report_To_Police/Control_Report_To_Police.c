#include "Control_Report_To_Police.h"

u16 Servor_CPWM_Set_Buffer[9]={1500,1500,1500,1500,1500,1500,1500,1500,1500};

/************************************
OLED��ʾ��
************************************/
void OLED_Display_Cotrol(void)  //ϵͳ��ʾ���ƹ���ʵ��   OLED��ʾ
{
	
static unsigned short timeCount = 0;	//���ͼ������
static u8 temperature=28,humidity=29;
static char p1[16]=" "; 
static float cotwo,guan;
static int a=30,b=-1,c=80,d=40,m=1,n=0,g,coo,guang,led_on,moter_on,water_on,turan;
		char Test_Mqqt_Buffer[512]="";  //Ϊ�˽��հ�ť���º����ƴ����������Ϣ
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
		    if(g==KEY0_PRES){n++;OLED_CLS();}//���� 
				if(n==6)n=0;
				if(n==0)
				{
					//��ʾ����
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
      //�¶�
      OLED_ShowCN(0,0,0);
			OLED_ShowCN(16,0,2);
			DHT11_Read_Data(&temperature,&humidity);
			sprintf((char*)p1,":%d",temperature);	
      OLED_ShowStr(32,0,p1,2);
			//ʪ��
			OLED_ShowCN(64,0,1);
			OLED_ShowCN(80,0,2);
			sprintf((char*)p1,":%d ",humidity);
			OLED_ShowStr(96,0,p1,2);
			//����ʪ��
			OLED_ShowCN(0,2,3);
			OLED_ShowCN(16,2,4);
			OLED_ShowCN(32,2,1);
			OLED_ShowCN(48,2,2);
			Get_adc1(&turan);
			sprintf((char*)p1,":%dHL ",turan);
			OLED_ShowStr(64,2,p1,2);
		  //������̵
			OLED_ShowCN(0,4,5);
			OLED_ShowCN(16,4,6);
			OLED_ShowCN(32,4,7);
			OLED_ShowCN(48,4,8);
			Get_adc2(&cotwo);
			coo=(int)cotwo;
			sprintf((char*)p1,":%dMMP ",coo);
			OLED_ShowStr(64,4,p1,2);
			//����ǿ��
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
					//��ֵ����
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
			//�¶���ֵ

      OLED_ShowCN(0,0,0);
			OLED_ShowCN(16,0,2);
			OLED_ShowCN(32,0,13);
			OLED_ShowCN(48,0,14);
			sprintf((char*)p1,":%dC ",a);
			OLED_ShowStr(64,0,p1,2);
      //ʪ��
   
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
			//��
			OLED_ShowCN(0,6,10);
			OLED_ShowCN(16,6,11);		
			OLED_ShowCN(32,6,13);
			OLED_ShowCN(48,6,14);
			sprintf((char*)p1,":%dLM ",d);
			OLED_ShowStr(64,6,p1,2);
			
		}
				if(n==4)
				{
				//���ƽ���
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
				//����
				OLED_ShowCN(0,0,24);
				OLED_ShowCN(16,0,25);
				OLED_ShowStr(32,0,":",2);
				if(moter_on==1){OLED_ShowCN(48,0,21);}else{	OLED_ShowCN(48,0,22);}
				//ˮ��
				if(g==KEY2_PRES)water_on++;
				if(water_on==2)water_on=0;
				OLED_ShowCN(0,2,26);
				OLED_ShowCN(16,2,27);
				OLED_ShowStr(32,2,":",2);
				if(water_on==1){OLED_ShowCN(48,2,21);}else{	OLED_ShowCN(48,2,22);}
				
				//�ƹ�
				if(g==KEY3_PRES)led_on++;
				if(led_on==2)led_on=0;
				OLED_ShowCN(0,4,23);
				OLED_ShowCN(16,4,10);
				OLED_ShowStr(32,4,":",2);
				if(led_on==1){OLED_ShowCN(48,4,21);}else{	OLED_ShowCN(48,4,22);}
		
			
			}
			//���ƹ���
			if(moter_on==1||coo>c||temperature>a){Relay_0=1;}else{Relay_0=0;}
			
			if(water_on==1||turan<b){Relay_1=1;}else{Relay_1=0;}
			
			if(led_on==1||guang<d){Led1_0=0;}else{Led1_0=1;}
	
			
			timeCount++; 
			if(timeCount==20){timeCount=0;send_data(&temperature,&humidity,&turan,&coo,&guang,&a,&b,&c,&d,&n);}

			if(MQTT_TxDataOutPtr != MQTT_TxDataInPtr) //if�����Ļ���˵�����ͻ�������������
			{                
				if((MQTT_TxDataOutPtr[2] == 0x10)||((MQTT_TxDataOutPtr[2] == 0x82)&&(connectPackFlag == 1))||(subcribePackFlag == 1)) //10���ӱ���  82�ͻ��˶�������
				{    
					if (MQTT_TxDataOutPtr[2] == 0x30) 
					{	
					}
					else 
					{
					}
					
					MQTT_TxData(MQTT_TxDataOutPtr);							//��������
					MQTT_TxDataOutPtr += BUFF_UNIT;						//ָ������
					if(MQTT_TxDataOutPtr == MQTT_TxDataEndPtr)				//���ָ�뵽������β����
					{ 
						MQTT_TxDataOutPtr = MQTT_TxDataBuf[0];				//ָ���λ����������ͷ
					}	
					
				} 				
			}
			/*-------------------------------------------------------------*/
			/*                     ������ջ���������                      */
			/*-------------------------------------------------------------*/
			if(MQTT_RxDataOutPtr != MQTT_RxDataInPtr) //if�����Ļ���˵�����ջ�������������	
			{												
				/*-----------------------------------------------------*/
				/*                    ����CONNACK����                  */
				/*-----------------------------------------------------*/				
				//if�жϣ������һ���ֽ���0x20����ʾ�յ�����CONNACK����//�̶���ͷ     ����˵��ͻ���  ���ӱ���ȷ��
				//��������Ҫ�жϵ�4���ֽڣ�����CONNECT�����Ƿ�ɹ�      �ͻ��˵������	�ͻ����������ӷ����		
				if(MQTT_RxDataOutPtr[2] == 0x20)//����ȷ��
				{             			
					switch(MQTT_RxDataOutPtr[5])//MQTT-3.1.1-CN  38-39ҳ
					{					   
						case 0x00 : 
									connectPackFlag = 1;									//CONNECT���ĳɹ������ı��Ŀɷ�
									break;														//������֧case 0x00                                              
						case 0x01 :
									connectFlag = 0;											//connectFlag���㣬��������
									break;														//������֧case 0x01   
						case 0x02 : 
									connectFlag = 0;                                            //connectFlag���㣬��������
									break; 														//������֧case 0x02 
						case 0x03 : 
									connectFlag = 0;											//connectFlag���㣬��������
									break;														//������֧case 0x03
						case 0x04 : 
									connectFlag = 0;											//connectFlag���㣬��������						
									break;														//������֧case 0x04
						case 0x05 :
									connectFlag = 0;											//connectFlag���㣬��������						
									break;														//������֧case 0x05 		
						default   : 
									connectFlag = 0;											//connectFlag���㣬��������					
									break;														//������֧case default 								
					}				
			  }			
				//if�жϣ���һ���ֽ���0x90����ʾ�յ�����SUBACK����
				//��������Ҫ�ж϶��Ļظ��������ǲ��ǳɹ�
				else if(MQTT_RxDataOutPtr[2] == 0x90)//����˶���ȷ��
				{ 
					switch(MQTT_RxDataOutPtr[6])
					{					
						case 0x00 :
						case 0x01 : 
									subcribePackFlag = 1;				//subcribePackFlag��1����ʾ���ı��ĳɹ����������Ŀɷ���
									pingFlag = 0;						//pingFlag����
									TIM3_ENABLE_30S();					//����30s��PING��ʱ��	
									break;								//������֧                                             
						default: 
									connectFlag = 0;					//connectFlag���㣬��������
									break;								//������֧ 								
						}					
			    }
				//if�жϣ���һ���ֽ���0xD0����ʾ�յ�����PINGRESP����
				else if(MQTT_RxDataOutPtr[2] == 0xD0)
				{ 
					if(pingFlag == 1)
					{                   						        //���pingFlag=1����ʾ��һ�η���
						 pingFlag = 0;    				       			//Ҫ���pingFlag��־
					}
					else if(pingFlag > 1)	
					{ 				 									//���pingFlag>1����ʾ�Ƕ�η����ˣ�������2s����Ŀ��ٷ���
						pingFlag = 0;     				      			//Ҫ���pingFlag��־
						TIM3_ENABLE_30S(); 				      			//PING��ʱ���ػ�30s��ʱ��
					}				
				}	
				//if�жϣ������һ���ֽ���0x30����ʾ�յ����Ƿ�������������������
				//����Ҫ��ȡ��������
				else if((MQTT_RxDataOutPtr[2] == 0x30))
			    { 
					     MQTT_DealPushdata_Qs0(MQTT_RxDataOutPtr);   //����ȼ�0��������
								for(Test_Mqqt_Num=0;Test_Mqqt_Num<512;Test_Mqqt_Num++)
							{
								 Test_Mqqt_Buffer[Test_Mqqt_Num]=MQTT_RxDataOutPtr[Test_Mqqt_Num];
							}
							 Test_Mqqt_Num=strlen(Test_Mqqt_Buffer);
				}									
				MQTT_RxDataOutPtr += BUFF_UNIT;                //ָ������
				if(MQTT_RxDataOutPtr == MQTT_RxDataEndPtr)      //���ָ�뵽������β����
				{
					MQTT_RxDataOutPtr = MQTT_RxDataBuf[0];      //ָ���λ����������ͷ              
				}		          
			}//������ջ��������ݵ�else if��֧��β
						
			/*---------------------------------------------------------------------------------------------------------------------*/
			/*                    							                 ���������������                   		          			         */
			/*---------------------------------------------------------------------------------------------------------------------*/
			if(MQTT_CMDOutPtr != MQTT_CMDInPtr)							  //if�����Ļ���˵�����������������	
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
				MQTT_CMDOutPtr += BUFF_UNIT;				//ָ������
				if(MQTT_CMDOutPtr == MQTT_CMDEndPtr)	    //���ָ�뵽������β����
				MQTT_CMDOutPtr = MQTT_CMDBuf[0];			//ָ���λ����������ͷ	
							
			}	
		}
	/*--------------------------------------------------------------------*/
	/*      connectFlag=0ͬ�������Ͽ�������,����Ҫ�������ӷ�����            */
	/*--------------------------------------------------------------------*/
		else
		{ 
			TIM_Cmd(TIM4, DISABLE);                        //�ر�TIM4 
			TIM_Cmd(TIM3, DISABLE);                        //�ر�TIM3  
			WiFi_RxCounter = 0;                            //WiFi������������������                        
			memset(WiFi_RX_BUF, 0, WiFi_RXBUFF_SIZE);      //���WiFi���ջ����� 
			if(WiFi_Connect_IoTServer() == 0)			   //���WiFi�����Ʒ�������������0����ʾ��ȷ������if����ESP8266ģ��
			{   			     
				connectFlag = 1;                           //connectFlag��1����ʾ���ӳɹ�	
				WiFi_RxCounter = 0;                        //WiFi������������������                        
				memset(WiFi_RX_BUF, 0, WiFi_RXBUFF_SIZE);  //���WiFi���ջ����� 
 				MQTT_Buff_ReInit();                          //��ʼ�����ͻ�����  
			}				
		}

}


//�����ַ����Ƚ�   �ж�str �ַ������Ƿ����substr�ַ���

_Bool isSubstring(const char* str, const char* substr) {
    int i, j;
    int str_len =512;   //���ֵ������str�ַ����ĳ���   ������Ϊ�ڲ��������з�  ��Ĳ�׼����趨�ɹ̶���
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

//�����ַ�������ƴ�ӵĺ���

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
