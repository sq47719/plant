//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "mqttkit.h"

//�㷨
#include "base64.h"
#include "hmac_sha1.h"

//Ӳ������
#include "usart.h"
#include "usart2.h"
#include "delay.h"

//C��
#include <string.h>
#include <stdio.h>



#define PROID			"hb6pr4OLYo"

#define ACCESS_KEY		"5QFV2aVXbwnLaSV7dekLLTc9gcNR2acbxe9LyS9pkUs="

#define DEVICE_NAME		"device"


char devid[16];

char key[48];


/*
************************************************************
*	�������ƣ�	OTA_UrlEncode
*
*	�������ܣ�	sign��Ҫ����URL����
*
*	��ڲ�����	sign�����ܽ��
*
*	���ز�����	0-�ɹ�	����-ʧ��
*
*	˵����		+			%2B
*				�ո�		%20
*				/			%2F
*				?			%3F
*				%			%25
*				#			%23
*				&			%26
*				=			%3D
************************************************************
*/
static unsigned char OTA_UrlEncode(char *sign)
{

	char sign_t[40];
	unsigned char i = 0, j = 0;
	unsigned char sign_len = strlen(sign);
	
	if(sign == (void *)0 || sign_len < 28)
		return 1;
	
	for(; i < sign_len; i++)
	{
		sign_t[i] = sign[i];
		sign[i] = 0;
	}
	sign_t[i] = 0;
	
	for(i = 0, j = 0; i < sign_len; i++)
	{
		switch(sign_t[i])
		{
			case '+':
				strcat(sign + j, "%2B");j += 3;
			break;
			
			case ' ':
				strcat(sign + j, "%20");j += 3;
			break;
			
			case '/':
				strcat(sign + j, "%2F");j += 3;
			break;
			
			case '?':
				strcat(sign + j, "%3F");j += 3;
			break;
			
			case '%':
				strcat(sign + j, "%25");j += 3;
			break;
			
			case '#':
				strcat(sign + j, "%23");j += 3;
			break;
			
			case '&':
				strcat(sign + j, "%26");j += 3;
			break;
			
			case '=':
				strcat(sign + j, "%3D");j += 3;
			break;
			
			default:
				sign[j] = sign_t[i];j++;
			break;
		}
	}
	
	sign[j] = 0;
	
	return 0;

}

/*
************************************************************
*	�������ƣ�	OTA_Authorization
*
*	�������ܣ�	����Authorization
*
*	��ڲ�����	ver��������汾�ţ����ڸ�ʽ��Ŀǰ��֧�ָ�ʽ"2018-10-31"
*				res����Ʒid
*				et������ʱ�䣬UTC��ֵ
*				access_key��������Կ
*				dev_name���豸��
*				authorization_buf������token��ָ��
*				authorization_buf_len������������(�ֽ�)
*
*	���ز�����	0-�ɹ�	����-ʧ��
*
*	˵����		��ǰ��֧��sha1
************************************************************
*/
#define METHOD		"sha1"
static unsigned char OneNET_Authorization(char *ver, char *res, unsigned int et, char *access_key, char *dev_name,
											char *authorization_buf, unsigned short authorization_buf_len, _Bool flag)
{
	
	size_t olen = 0;
	
	char sign_buf[64];								//����ǩ����Base64������ �� URL������
	char hmac_sha1_buf[64];							//����ǩ��
	char access_key_base64[64];						//����access_key��Base64������
	char string_for_signature[72];					//����string_for_signature������Ǽ��ܵ�key

//----------------------------------------------------�����Ϸ���--------------------------------------------------------------------
	if(ver == (void *)0 || res == (void *)0 || et < 1564562581 || access_key == (void *)0
		|| authorization_buf == (void *)0 || authorization_buf_len < 120)
		return 1;
	
//----------------------------------------------------��access_key����Base64����----------------------------------------------------
	memset(access_key_base64, 0, sizeof(access_key_base64));
	BASE64_Decode((unsigned char *)access_key_base64, sizeof(access_key_base64), &olen, (unsigned char *)access_key, strlen(access_key));
	//UsartPrintf(Usart_Num_1, "access_key_base64: %s\r\n", access_key_base64);
	
//----------------------------------------------------����string_for_signature-----------------------------------------------------
	memset(string_for_signature, 0, sizeof(string_for_signature));
	if(flag)
		snprintf(string_for_signature, sizeof(string_for_signature), "%d\n%s\nproducts/%s\n%s", et, METHOD, res, ver);
	else
		snprintf(string_for_signature, sizeof(string_for_signature), "%d\n%s\nproducts/%s/devices/%s\n%s", et, METHOD, res, dev_name, ver);
	//UsartPrintf(Usart_Num_1, "string_for_signature: %s\r\n", string_for_signature);
	
//----------------------------------------------------����-------------------------------------------------------------------------
	memset(hmac_sha1_buf, 0, sizeof(hmac_sha1_buf));
	
	hmac_sha1((unsigned char *)access_key_base64, strlen(access_key_base64),
				(unsigned char *)string_for_signature, strlen(string_for_signature),
				(unsigned char *)hmac_sha1_buf);
	
	//UsartPrintf(Usart_Num_1, "hmac_sha1_buf: %s\r\n", hmac_sha1_buf);
	
//----------------------------------------------------�����ܽ������Base64����------------------------------------------------------
	olen = 0;
	memset(sign_buf, 0, sizeof(sign_buf));
	BASE64_Encode((unsigned char *)sign_buf, sizeof(sign_buf), &olen, (unsigned char *)hmac_sha1_buf, strlen(hmac_sha1_buf));

//----------------------------------------------------��Base64����������URL����---------------------------------------------------
	OTA_UrlEncode(sign_buf);
	//UsartPrintf(Usart_Num_1, "sign_buf: %s\r\n", sign_buf);
	
//----------------------------------------------------����Token--------------------------------------------------------------------
	if(flag)
		snprintf(authorization_buf, authorization_buf_len, "version=%s&res=products%%2F%s&et=%d&method=%s&sign=%s", ver, res, et, METHOD, sign_buf);
	else
		snprintf(authorization_buf, authorization_buf_len, "version=%s&res=products%%2F%s%%2Fdevices%%2F%s&et=%d&method=%s&sign=%s", ver, res, dev_name, et, METHOD, sign_buf);
	//UsartPrintf(Usart_Num_1, "Token: %s\r\n", authorization_buf);
	
	return 0;

}

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//Э���

	unsigned char *dataPtr;
	
	char authorization_buf[160];
	
	_Bool status = 1;
	
	OneNET_Authorization("2018-10-31", PROID, 1956499200, ACCESS_KEY, DEVICE_NAME,
								authorization_buf, sizeof(authorization_buf), 0);
	
//	UsartPrintf(Usart_Num_1, "OneNET_DevLink\r\n"
//							"NAME: %s,	PROID: %s,	KEY:%s\r\n"
//                        , DEVICE_NAME, PROID, authorization_buf);
//	
	if(MQTT_PacketConnect(PROID, authorization_buf, DEVICE_NAME, 256, 1, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
//		UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ�Э�����\r\n");
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//�ϴ�ƽ̨
//		UsartPrintf(Usart_Num_1, "ERR:	����\r\n");
		dataPtr = ESP8266_GetIPD(250);

				//�ȴ�ƽ̨��Ӧ
//		UsartPrintf(Usart_Num_1,"1\r\n");
		if(dataPtr != NULL)
		{
//			UsartPrintf(Usart_Num_1,"2\r\n");
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:
  						UsartPrintf(Usart_Num_1, "Tips:	���ӳɹ�\r\n");status = 0;
					    break;
					
//					case 1:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ�Э�����\r\n");break;
//					case 2:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ��Ƿ���clientid\r\n");break;
//					case 3:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
//					case 4:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ��û������������\r\n");break;
//					case 5:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ��Ƿ�����(����token�Ƿ�)\r\n");break;
					
					default:
  						UsartPrintf(Usart_Num_1, "ERR:	����ʧ�ܣ�δ֪����\r\n");
					    break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//ɾ��
	}
//	else
//		UsartPrintf(Usart_Num_1, "WARN:	MQTT_PacketConnect Failed\r\n");
	
	return status;
	
}

unsigned char OneNet_FillBuf(u8 temperature,u8 humidity,_Bool Nios_Flag,_Bool Water_Flag,_Bool On_Bed_Flag, char *buf)
{
	
	char text[48];
	
	memset(text, 0, sizeof(text));
	
	strcpy(buf, "{\"id\":123,\"dp\":{");
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Te\":[{\"v\":%d}],", temperature);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Hu\":[{\"v\":%d}],",humidity);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Ni\":[{\"v\":%d}],",Nios_Flag);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Wa\":[{\"v\":%d}],",Water_Flag);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"Be\":[{\"v\":%d}]",On_Bed_Flag);
	strcat(buf, text);
	
	strcat(buf, "}}");
	
	return strlen(buf);

}



//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(short body_len,char *buf)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//Э���
	

	
	short i = 0;
	
	if(body_len)
	{
		if(MQTT_PacketSaveData(PROID, DEVICE_NAME, body_len, NULL, &mqttPacket) == 0)				//���
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//�ϴ����ݵ�ƽ̨
//			UsartPrintf(Usart_Num_1, "Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//ɾ��
		}
//		else
//			UsartPrintf(Usart_Num_1, "WARN:	EDP_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	�������ƣ�	OneNET_Publish
//
//	�������ܣ�	������Ϣ
//
//	��ڲ�����	topic������������
//				msg����Ϣ����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNET_Publish(const char *topic, const char *msg)
{

	MQTT_PACKET_STRUCTURE mqtt_packet = {NULL, 0, 0, 0};						//Э���
	
//	UsartPrintf(Usart_Num_1, "Publish Topic: %s, Msg: %s\r\n", topic, msg);
	
	if(MQTT_PacketPublish(MQTT_PUBLISH_ID, topic, msg, strlen(msg), MQTT_QOS_LEVEL0, 0, 1, &mqtt_packet) == 0)
	{
		ESP8266_SendData(mqtt_packet._data, mqtt_packet._len);					//��ƽ̨���Ͷ�������
		
		MQTT_DeleteBuffer(&mqtt_packet);										//ɾ��
	}

}

//==========================================================
//	�������ƣ�	OneNET_Subscribe
//
//	�������ܣ�	����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNET_Subscribe(void)
{
	
	MQTT_PACKET_STRUCTURE mqtt_packet = {NULL, 0, 0, 0};						//Э���
	
	char topic_buf[56];
	const char *topic = topic_buf;
	
	snprintf(topic_buf, sizeof(topic_buf), "$sys/%s/%s/cmd/#", PROID, DEVICE_NAME);
	
//	UsartPrintf(Usart_Num_1, "Subscribe Topic: %s\r\n", topic_buf);
	
	if(MQTT_PacketSubscribe(MQTT_SUBSCRIBE_ID, MQTT_QOS_LEVEL0, &topic, 1, &mqtt_packet) == 0)
	{
		ESP8266_SendData(mqtt_packet._data, mqtt_packet._len);					//��ƽ̨���Ͷ�������
		
		MQTT_DeleteBuffer(&mqtt_packet);										//ɾ��
	}

}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short topic_len = 0;
	unsigned short req_len = 0;
	
	unsigned char qos = 0;
	static unsigned short pkt_id = 0;
	
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		case MQTT_PKT_PUBLISH:																//���յ�Publish��Ϣ
		
			result = MQTT_UnPacketPublish(cmd, &cmdid_topic, &topic_len, &req_payload, &req_len, &qos, &pkt_id);
			if(result == 0)
			{
				char *data_ptr = NULL;
				
//				UsartPrintf(Usart_Num_1, "topic: %s, topic_len: %d, payload: %s, payload_len: %d\r\n",
//																	cmdid_topic, topic_len, req_payload, req_len);
				
				data_ptr = strstr(cmdid_topic, "request/");									//����cmdid
				if(data_ptr)
				{
					char topic_buf[80], cmdid[40];
					
					data_ptr = strchr(data_ptr, '/');
					data_ptr++;
					
					memcpy(cmdid, data_ptr, 36);											//����cmdid
					cmdid[36] = 0;
					
					snprintf(topic_buf, sizeof(topic_buf), "$sys/%s/%s/cmd/response/%s",
															PROID, DEVICE_NAME, cmdid);
					OneNET_Publish(topic_buf, "ojbk");										//�ظ�����
				}
			}
			
		case MQTT_PKT_PUBACK:														//����Publish��Ϣ��ƽ̨�ظ���Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
//				UsartPrintf(Usart_Num_1, "Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		case MQTT_PKT_SUBACK:																//����Subscribe��Ϣ��Ack
		
//			if(MQTT_UnPacketSubscribe(cmd) == 0)
//				UsartPrintf(Usart_Num_1, "Tips:	MQTT Subscribe OK\r\n");
//			else
//				UsartPrintf(Usart_Num_1, "Tips:	MQTT Subscribe Err\r\n");
		
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//��ջ���
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, '}');					//����':'

	if(dataPtr != NULL)					//����ҵ���
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		numBuf[num] = 0;
		
		num = atoi((const char *)numBuf);				//תΪ��ֵ��ʽ
		if(strstr((char *)req_payload, "redled"))		//����"redled"
		{
			if(num == 1)								//�����������Ϊ1������
			{
//				UsartPrintf(Usart_Num_1, "GOOOFFFF\r\n");
			}
			else if(num == 0)							//�����������Ϊ0�������
			{
//				UsartPrintf(Usart_Num_1, "Tips:	ASDASDAD\r\n");
			}
		}
														//��ͬ

	}

	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
