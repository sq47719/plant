
#ifndef __MQTT_H
#define __MQTT_H

#include "stm32f10x.h"    //������Ҫ��ͷ�ļ�
#include "string.h"       //������Ҫ��ͷ�ļ�
#include "stdio.h"        //������Ҫ��ͷ�ļ�
#include "wifi.h"         //������Ҫ��ͷ�ļ�
#include "utils_hmac.h"




#define  R_NUM               8     //���ջ���������
#define  BUFF_UNIT          512   //���ջ���������

#define  T_NUM               8     //���ͻ���������  

#define  C_NUM               8     //�����������

#define  MQTT_TxData(x)       u2_TxData(x)                                  //����2�������ݷ���

//#define  PRODUCTKEY           "k00daKpPBSb"                                 //��ƷID
//#define  PRODUCTKEY_LEN       strlen(PRODUCTKEY)                            //��ƷID����
//#define  DEVICENAME           "mqtt-web"                                     //�豸��  
//#define  DEVICENAME_LEN       strlen(DEVICENAME)                            //�豸������
//#define  DEVICESECRE          "2aba4abf34cdbfdb7724a13ba4ce0847"            //�豸��Կ   
//#define  DEVICESECRE_LEN      strlen(DEVICESECRE)                           //�豸��Կ����
//#define  S_TOPIC_NAME         "/sys/k00daKpPBSb/mqtt-web/thing/service/property/set"   //��Ҫ���ĵ�����  
//#define  P_TOPIC_NAME         "/sys/k00daKpPBSb/mqtt-web/thing/event/property/post"    //��Ҫ����������   
#define  PRODUCTKEY           "k0qdlJYPoyz"                                 //��ƷID
#define  PRODUCTKEY_LEN       strlen(PRODUCTKEY)                            //��ƷID����
#define  DEVICENAME           "device-vz"                                        //�豸��  
#define  DEVICENAME_LEN       strlen(DEVICENAME)                            //�豸������
#define  DEVICESECRE          "79487b307b3797c25fb76e2436f04068"            //�豸��Կ   
#define  DEVICESECRE_LEN      strlen(DEVICESECRE)                           //�豸��Կ����
#define  S_TOPIC_NAME         "/sys/k0qdlJYPoyz/device-vz/thing/service/property/set"   //��Ҫ���ĵ�����  
#define  P_TOPIC_NAME         "/sys/k0qdlJYPoyz/device-vz/thing/event/property/post"    //��Ҫ����������   


extern unsigned char  MQTT_RxDataBuf[R_NUM][BUFF_UNIT];       //�ⲿ�������������ݵĽ��ջ�����,���з��������������ݣ�����ڸû�����,��������һ���ֽڴ�����ݳ���
extern unsigned char *MQTT_RxDataInPtr;                        //�ⲿ����������ָ�򻺳���������ݵ�λ��
extern unsigned char *MQTT_RxDataOutPtr;                       //�ⲿ����������ָ�򻺳�����ȡ���ݵ�λ��
extern unsigned char *MQTT_RxDataEndPtr;                       //�ⲿ����������ָ�򻺳���������λ��
extern unsigned char  MQTT_TxDataBuf[T_NUM][BUFF_UNIT];       //�ⲿ�������������ݵķ��ͻ�����,���з��������������ݣ�����ڸû�����,��������һ���ֽڴ�����ݳ���
extern unsigned char *MQTT_TxDataInPtr;                        //�ⲿ����������ָ�򻺳���������ݵ�λ��
extern unsigned char *MQTT_TxDataOutPtr;                       //�ⲿ����������ָ�򻺳�����ȡ���ݵ�λ��
extern unsigned char *MQTT_TxDataEndPtr;                       //�ⲿ����������ָ�򻺳���������λ��
extern unsigned char  MQTT_CMDBuf[C_NUM][BUFF_UNIT];          //�ⲿ�����������������ݵĽ��ջ�����
extern unsigned char *MQTT_CMDInPtr;                           //�ⲿ����������ָ�򻺳���������ݵ�λ��
extern unsigned char *MQTT_CMDOutPtr;                          //�ⲿ����������ָ�򻺳�����ȡ���ݵ�λ��
extern unsigned char *MQTT_CMDEndPtr;                          //�ⲿ����������ָ�򻺳���������λ��

extern char ClientID[128];     //�ⲿ������������ſͻ���ID�Ļ�����
extern int  ClientID_len;      //�ⲿ������������ſͻ���ID�ĳ���
extern char Username[128];     //�ⲿ��������������û����Ļ�����
extern int  Username_len;	   //�ⲿ��������������û����ĳ���
extern char Passward[128];     //�ⲿ�����������������Ļ�����
extern int  Passward_len;	   //�ⲿ�����������������ĳ���
extern char ServerIP[128];     //�ⲿ������������ŷ�����IP��������
extern int  ServerPort;        //�ⲿ������������ŷ������Ķ˿ں�

extern char pingFlag;          //�ⲿ����������ping����״̬      0������״̬���ȴ���ʱʱ�䵽������Ping����
                               //�ⲿ����������ping����״̬      1��Ping�����ѷ��ͣ����յ� �������ظ����ĵĺ� ��1��Ϊ0
extern char connectFlag;       //�ⲿ����������ͬ����������״̬  0����û�����ӷ�����  1�������Ϸ�������
extern char reConnectFlag;     //�ⲿ��������������������״̬    0�����ӻ�����  1�����ӶϿ�������
extern char connectPackFlag;   //�ⲿ����������CONNECT����״̬   1��CONNECT���ĳɹ�
extern char subcribePackFlag;  //�ⲿ�������������ı���״̬      1�����ı��ĳɹ�



void MQTT_Buff_Init(void);
void AliIoT_Parameter_Init(void);
//�����������������������г�ʼ������


void MQTT_ConectPack(void);
void MQTT_Subscribe(char *, int);
void MQTT_PingREQ(void);
void MQTT_PublishQs0(char *, char *, int);
void MQTT_DealPushdata_Qs0(unsigned char *);	
void TxDataBuf_Deal(unsigned char *, int);
void CMDBuf_Deal(unsigned char *, int);
void MQTT_Buff_ReInit(void);
void send_data(u8 *tem,u8 *hum,int *turann,int *cooo,int *guangg,int *aa,int *bb,int *cc,int *dd,int *nn);
#endif
