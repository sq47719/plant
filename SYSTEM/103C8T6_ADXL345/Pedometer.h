#ifndef _Pedometer_H
#define _Pedometer_H




extern _Bool ADXL345_FLAG;  				//��ȡ��־λ ���ö�ʱ��ȡ200ms��ȡһ������ �˵Ĳ��������1Sһ��
//extern unsigned char START_FLAG;		//��ʼ�Ʋ���־λ
//extern unsigned char number;

extern unsigned int  STEPS;
//extern unsigned int  time;
										
//float  speed=0;
//float  dist=0;
//float  kalul=0;

void step_counter(void);

#endif
