 #include "adc.h"
 #include "delay.h"	
 #include "math.h"


   
 void  Adc_Init(void)//ADC��ʼ�����ú���
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port |RCC_APB2Periph_AD_Num	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num;// ģ��ͨ����������         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(ADC1_GPIO_Port, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel =1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC_Num, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC_Num, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC_Num);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC_Num);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //�ȴ�У׼����

}				  

u16 Get_Adc(u8 ch)   //���ADCֵ
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC_Num, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC_Num, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC_Num, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC_Num);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)//ADC���ã���ȡADCƽ��ֵ
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 
void Get_Adc_Convert_Data(float *Smo) //�õ�ADC������������ֵ
{
	  u16   AD_Convert_Data;//ADC�����õ���������
	
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num,1);
	  *Smo = (float)AD_Convert_Data*5/4096;
		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
		*Smo *=100;             //Ũ�ȵ�λ  PPM
}

void Get_Adc_Convert_Data_MQ135(float *Smo) //�õ�ADC������������ֵ
{
	  u16   AD_Convert_Data;//ADC�����õ���������
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num,1);
	  *Smo = (float)AD_Convert_Data*5/4096;
		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
		*Smo *=100;             //Ũ�ȵ�λ  PPM
}

void Get_Adc_Convert_Data_MQ_2(float *Smo) //�õ�ADC������������ֵ
{
	  u16   AD_Convert_Data;//ADC�����õ���������
	
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_3,1);
	  *Smo = (float)AD_Convert_Data*5/4096;
		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
		*Smo *=100;             //Ũ�ȵ�λ  PPM
}

void Adc_Init1(void)//ADC��ʼ�����ú���
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_1 |RCC_APB2Periph_AD_Num_1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_1;// ģ��ͨ����������         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(ADC1_GPIO_Port_1, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel =1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC_Num, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC_Num, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC_Num);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC_Num);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //�ȴ�У׼����

}	

void Adc_Init2(void)//ADC��ʼ�����ú���
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_2 |RCC_APB2Periph_AD_Num_2	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_2;// ģ��ͨ����������         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(ADC1_GPIO_Port_2, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel =1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC_Num, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC_Num, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC_Num);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC_Num);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //�ȴ�У׼����

}	

void  Adc_Init3(void)//ADC��ʼ�����ú���
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_3 |RCC_APB2Periph_AD_Num_3	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_3;// ģ��ͨ����������         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(ADC1_GPIO_Port_3, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel =1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC_Num, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC_Num, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC_Num);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC_Num);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //�ȴ�У׼����

}		
void  Adc_Init4(void)//ADC��ʼ�����ú���
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_4 |RCC_APB2Periph_AD_Num_4	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_4;// ģ��ͨ����������         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(ADC1_GPIO_Port_4, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel =1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC_Num, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC_Num, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC_Num);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC_Num);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //�ȴ�У׼����

}		

void Get_adc(float *Smo)
{
	
		u16   AD_Convert_Data;//ADC�����õ���������
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num,1);
	  *Smo = (float)AD_Convert_Data/4096*100;
}
void Get_adc1(int *water_high)
{
	  u16 AD_Convert_Data;//ADC�����õ���������
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_1,1);
		*water_high = 100-(float)AD_Convert_Data/4096*100;

}
void Get_adc2(float *co2)
{
		u16   AD_Convert_Data;//ADC�����õ���������
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_2,1);
	  *co2 = (float)AD_Convert_Data/4096*100;
//		*co2 *=100;             //Ũ�ȵ�λ  PPM
}
void Get_adc3(float *Smo)
{
		u16   AD_Convert_Data;//ADC�����õ���������
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_3,1);
	  *Smo = (float)AD_Convert_Data/4096*100;
//		*Smo *=100;             //Ũ�ȵ�λ  PPM
}

void Get_adc4(float *Smo)
{
		u16   AD_Convert_Data;//ADC�����õ���������
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_4,1);
	  *Smo = (float)AD_Convert_Data/4096*100;
//		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
//		*Smo *=100;             //Ũ�ȵ�λ  PPM
}







