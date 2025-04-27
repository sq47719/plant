#ifndef _ONENET_H_
#define _ONENET_H_
#include "dht11.h"



_Bool OneNet_DevLink(void);

void OneNet_SendData(short body_len,char *buf);

void OneNET_Subscribe(void);

void OneNet_RevPro(unsigned char *cmd);

unsigned char OneNet_FillBuf(u8 temperature,u8 humidity,_Bool Nios_Flag,_Bool Water_Flag,_Bool On_Bed_Flag, char *buf);

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"

#endif
