/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	sample.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-06-14
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		���ļ���������룬����ֻ��SDKʹ�õ���ʾ
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/


#include "mqttkit.h"


unsigned char dataMem[128];		//ȫ�����鷽ʽ


//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	devid�������豸��devid
//				proid����ƷID
//				auth_key�������豸��masterKey��apiKey���豸��Ȩ��Ϣ
//
//	���ز�����	��
//
//	˵����		��onenetƽ̨�������ӣ��ɹ������oneNetInfo.netWork����״̬��־
//==========================================================
void OneNet_DevLink(const char* devid, const char *proid, const char* auth_info)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};
	
	edpPacket._data = dataMem;				//ȫ�����鷽ʽ
	edpPacket._size = sizeof(dataMem);		//ȫ�����鷽ʽ
	
//---------------------------------------------����һ�����---------------------------------------------
	if(MQTT_PacketConnect(proid, auth_info, devid, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
//---------------------------------------------���������������-----------------------------------------
		NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);

//---------------------------------------------���������жϷ�������--------------------------------------
		if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
		{
//---------------------------------------------�����ģ��������ؽ��--------------------------------------
			switch(MQTT_UnPacketConnectAck(dataPtr))
			{
				case 0:
					UsartPrintf(Usart_Num_1, "Tips:	���ӳɹ�\r\n");
					oneNetInfo.netWork = 1;
				break;
				
				case 1:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ�Э�����\r\n");break;
				case 2:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ��Ƿ���clientid\r\n");break;
				case 3:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
				case 4:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ��û������������\r\n");break;
				case 5:UsartPrintf(Usart_Num_1, "WARN:	����ʧ�ܣ��Ƿ�����(����token�Ƿ�)\r\n");break;
				
				default:UsartPrintf(Usart_Num_1, "ERR:	����ʧ�ܣ�δ֪����\r\n");break;
			}
		}
		
//---------------------------------------------�����壺ɾ��---------------------------------------------
		MQTT_DeleteBuffer(&mqttPacket);
	}
	else
		UsartPrintf(Usart_Num_1, "WARN:	MQTT_PacketConnect Failed\r\n");
	
}

//==========================================================
//	�������ƣ�	OneNet_DisConnect
//
//	�������ܣ�	��ƽ̨�Ͽ�����
//
//	��ڲ�����	��
//
//	���ز�����	0-�ɹ�		1-ʧ��
//
//	˵����		
//==========================================================
_Bool OneNet_DisConnect(void)
{

	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};
	unsigned char dataMem1[8];				//�ֲ����鷽ʽ
	
	edpPacket._data = dataMem;				//�ֲ����鷽ʽ
	edpPacket._size = sizeof(dataMem);		//�ֲ����鷽ʽ
	
//---------------------------------------------����һ�����---------------------------------------------
	if(MQTT_PacketDisConnect(&mqttPacket) == 0)
	{
//---------------------------------------------���������������-----------------------------------------
		NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
		
//---------------------------------------------��������ɾ��---------------------------------------------
		MQTT_DeleteBuffer(&mqttPacket);
	}
	
	return 0;

}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//				devid���豸ID
//				apikey���豸apikey
//				streamArray��������
//				streamArrayNum������������
//
//	���ز�����	0-�ɹ�		1-ʧ��
//
//	˵����		
//==========================================================
_Bool OneNet_SendData(FORMAT_TYPE type, char *devid, char *apikey, DATA_STREAM *streamArray, unsigned short streamArrayCnt)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};
	
	_Bool status = 0;
	short body_len = 0;
	
	UsartPrintf(Usart_Num_1, "Tips:	OneNet_SendData-MQTT_TYPE%d\r\n", type);
	
//---------------------------------------------����һ����������������---------------------------------------------
	body_len = DSTREAM_GetDataStream_Body_Measure(type, streamArray, streamArrayCnt, 0);
	if(body_len)
	{
//---------------------------------------------���������дЭ��ͷ-------------------------------------------------
		if(MQTT_PacketSaveData(devid, body_len, NULL, (uint8)type, &mqttPacket) == 0)
		{
//---------------------------------------------�����������-------------------------------------------------------
			body_len = DSTREAM_GetDataStream_Body(type, streamArray, streamArrayCnt, mqttPacket._data, mqttPacket._size, mqttPacket._len);
			
			if(body_len)
			{
				mqttPacket._len += body_len;
				UsartPrintf(Usart_Num_1, "Send %d Bytes\r\n", mqttPacket._len);
//---------------------------------------------�����ģ���������---------------------------------------------------
				NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
			}
			else
				UsartPrintf(Usart_Num_1, "WARN:	DSTREAM_GetDataStream_Body Failed\r\n");
			
//---------------------------------------------�����壺ɾ��-------------------------------------------------------
			MQTT_DeleteBuffer(&mqttPacket);
		}
		else
			UsartPrintf(Usart_Num_1, "WARN:	MQTT_NewBuffer Failed\r\n");
	}
	else
		status = 1;
	
	return status;
	
}

//==========================================================
//	�������ƣ�	OneNet_HeartBeat
//
//	�������ܣ�	�������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_HeartBeat(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};

	unsigned char sCount = 3;
	
//---------------------------------------------����һ�����---------------------------------------------
	if(MQTT_PacketPing(&mqttPacket))
		return;
	
	while(sCount--)
	{
//---------------------------------------------���������������-----------------------------------------
		NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);

//---------------------------------------------��������������������-------------------------------------
		if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_PINGRESP)
		{
			UsartPrintf(Usart_Num_1, "Tips:	HeartBeat OK\r\n");
			
			break;
		}
		else
		{
			UsartPrintf(Usart_Num_1, "Check Device\r\n");
		}
		
		RTOS_TimeDly(2);
	}
	
//---------------------------------------------�����ģ�ɾ��---------------------------------------------
	MQTT_DeleteBuffer(&mqttPacket);

}

//==========================================================
//	�������ƣ�	OneNet_Publish
//
//	�������ܣ�	������Ϣ
//
//	��ڲ�����	topic������������
//				msg����Ϣ����
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool OneNet_Publish(const char *topic, const char *msg)
{

	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};
	
	UsartPrintf(Usart_Num_1, "Publish Topic: %s, Msg: %s\r\n", topic, msg);
	
//---------------------------------------------����һ�����---------------------------------------------
	if(MQTT_PacketPublish(MQTT_PUBLISH_ID, topic, msg, strlen(msg), MQTT_QOS_LEVEL2, 0, 1, &mqttPacket) == 0)
	{
//---------------------------------------------���������������-----------------------------------------
		NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
		
//---------------------------------------------��������ɾ��---------------------------------------------
		MQTT_DeleteBuffer(&mqttPacket);
	}
	
	return 0;

}

//==========================================================
//	�������ƣ�	OneNet_Subscribe
//
//	�������ܣ�	����
//
//	��ڲ�����	topics�����ĵ�topic
//				topic_cnt��topic����
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool OneNet_Subscribe(const char *topics[], unsigned char topic_cnt)
{
	
	unsigned char i = 0;
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};							//Э���
	
	for(; i < topic_cnt; i++)
		UsartPrintf(Usart_Num_1, "Subscribe Topic: %s\r\n", topics[i]);
	
//---------------------------------------------����һ�����---------------------------------------------
	if(MQTT_PacketSubscribe(MQTT_SUBSCRIBE_ID, MQTT_QOS_LEVEL2, topics, topic_cnt, &mqttPacket) == 0)
	{
//---------------------------------------------���������������-----------------------------------------
		NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);					//��ƽ̨���Ͷ�������
		
//---------------------------------------------��������ɾ��---------------------------------------------
		MQTT_DeleteBuffer(&mqttPacket);											//ɾ��
	}
	
	return 0;

}

//==========================================================
//	�������ƣ�	OneNet_UnSubscribe
//
//	�������ܣ�	ȡ������
//
//	��ڲ�����	topics�����ĵ�topic
//				topic_cnt��topic����
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool OneNet_UnSubscribe(const char *topics[], unsigned char topic_cnt)
{
	
	unsigned char i = 0;
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};							//Э���
	
	for(; i < topic_cnt; i++)
		UsartPrintf(Usart_Num_1, "UnSubscribe Topic: %s\r\n", topics[i]);
	
//---------------------------------------------����һ�����---------------------------------------------
	if(MQTT_PacketUnSubscribe(MQTT_UNSUBSCRIBE_ID, topics, topic_cnt, &mqttPacket) == 0)
	{
//---------------------------------------------���������������-----------------------------------------
		NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);					//��ƽ̨����ȡ����������
		
//---------------------------------------------��������ɾ��---------------------------------------------
		MQTT_DeleteBuffer(&mqttPacket);											//ɾ��
	}
	
	return 0;

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
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	unsigned char type = 0;
	unsigned char qos = 0;
	static unsigned short pkt_id = 0;
	
	short result = -1;
	
//---------------------------------------------����һ����ȡ������������---------------------------------------------
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
//---------------------------------------------����������ú�������-------------------------------------------------
		case MQTT_PKT_CMD:															//�����·�
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload);				//���topic����Ϣ��
			if(result == 0)
			{
				UsartPrintf(Usart_Num_1, "cmdid: %s, req: %s\r\n", cmdid_topic, req_payload);
				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//����ظ����
				{
					UsartPrintf(Usart_Num_1, "Tips:	Send CmdResp\r\n");
					
					NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);			//�ظ�����
					MQTT_DeleteBuffer(&mqttPacket);									//ɾ��
				}
			}
		
		break;
			
		case MQTT_PKT_PUBLISH:														//���յ�Publish��Ϣ
		
			result = MQTT_UnPacketPublish(cmd, &cmdid_topic, &req_payload, &qos, &pkt_id);
			if(result == 0)
			{
				UsartPrintf(Usart_Num_1, "topic: %s\r\npayload: %s\r\n", cmdid_topic, req_payload);
				
				switch(qos)
				{
					case 1:															//�յ�publish��qosΪ1���豸��Ҫ�ظ�Ack
					
						if(MQTT_PacketPublishAck(pkt_id, &mqttPacket) == 0)
						{
							UsartPrintf(Usart_Num_1, "Tips:	Send PublishAck\r\n");
							NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
							MQTT_DeleteBuffer(&mqttPacket);
						}
					
					break;
					
					case 2:															//�յ�publish��qosΪ2���豸�Ȼظ�Rec
																					//ƽ̨�ظ�Rel���豸�ٻظ�Comp
						if(MQTT_PacketPublishRec(pkt_id, &mqttPacket) == 0)
						{
							UsartPrintf(Usart_Num_1, "Tips:	Send PublishRec\r\n");
							NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
							MQTT_DeleteBuffer(&mqttPacket);
						}
					
					break;
					
					default:
						break;
				}
			}
		
		break;
			
		case MQTT_PKT_PUBACK:														//����Publish��Ϣ��ƽ̨�ظ���Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				UsartPrintf(Usart_Num_1, "Tips:	MQTT Publish Send OK\r\n");
			
		break;
			
		case MQTT_PKT_PUBREC:														//����Publish��Ϣ��ƽ̨�ظ���Rec���豸��ظ�Rel��Ϣ
		
			if(MQTT_UnPacketPublishRec(cmd) == 0)
			{
				UsartPrintf(Usart_Num_1, "Tips:	Rev PublishRec\r\n");
				if(MQTT_PacketPublishRel(MQTT_PUBLISH_ID, &mqttPacket) == 0)
				{
					UsartPrintf(Usart_Num_1, "Tips:	Send PublishRel\r\n");
					NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
					MQTT_DeleteBuffer(&mqttPacket);
				}
			}
		
		break;
			
		case MQTT_PKT_PUBREL:														//�յ�Publish��Ϣ���豸�ظ�Rec��ƽ̨�ظ���Rel���豸���ٻظ�Comp
			
			if(MQTT_UnPacketPublishRel(cmd, pkt_id) == 0)
			{
				UsartPrintf(Usart_Num_1, "Tips:	Rev PublishRel\r\n");
				if(MQTT_PacketPublishComp(MQTT_PUBLISH_ID, &mqttPacket) == 0)
				{
					UsartPrintf(Usart_Num_1, "Tips:	Send PublishComp\r\n");
					NET_DEVICE_SendData(mqttPacket._data, mqttPacket._len);
					MQTT_DeleteBuffer(&mqttPacket);
				}
			}
		
		break;
		
		case MQTT_PKT_PUBCOMP:														//����Publish��Ϣ��ƽ̨����Rec���豸�ظ�Rel��ƽ̨�ٷ��ص�Comp
		
			if(MQTT_UnPacketPublishComp(cmd) == 0)
			{
				UsartPrintf(Usart_Num_1, "Tips:	Rev PublishComp\r\n");
			}
		
		break;
			
		case MQTT_PKT_SUBACK:														//����Subscribe��Ϣ��Ack
		
			if(MQTT_UnPacketSubscribe(cmd) == 0)
				UsartPrintf(Usart_Num_1, "Tips:	MQTT Subscribe OK\r\n");
			else
				UsartPrintf(Usart_Num_1, "Tips:	MQTT Subscribe Err\r\n");
		
		break;
			
		case MQTT_PKT_UNSUBACK:														//����UnSubscribe��Ϣ��Ack
		
			if(MQTT_UnPacketUnSubscribe(cmd) == 0)
				UsartPrintf(Usart_Num_1, "Tips:	MQTT UnSubscribe OK\r\n");
			else
				UsartPrintf(Usart_Num_1, "Tips:	MQTT UnSubscribe Err\r\n");
		
		break;
	}
	
//---------------------------------------------�������������---------------------------------------------
	if(req)
	{
		
	}
//---------------------------------------------�����ģ��ͷ��ڴ�---------------------------------------------
	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
