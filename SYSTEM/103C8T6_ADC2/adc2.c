 #include "adc2.h"
 #include "delay.h"	

 #include "math.h"


   
void  Adc2_Init(void)//ADC��ʼ�����ú���
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD2_GPIO_Port | RCC_APB2Periph_AD2_Num , ENABLE );	  //ʹ��ADC2ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC2_GPIO_Pin_Num;// ģ��ͨ����������         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ����������
	GPIO_Init(ADC2_GPIO_Port, &GPIO_InitStructure);	

	ADC_DeInit(ADC2_Num);  //��λADC2,������ ADC2 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel =1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC2_Num, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC2_Num, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC2_Num);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC2_Num));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC2_Num);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC2_Num));	 //�ȴ�У׼����

}				  

u16 Get_Adc2(u8 ch)   //���ADCֵ
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC2_Num, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC2_Num, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC2_Num, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC2_Num);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc2_Average(u8 ch,u8 times)//ADC���ã���ȡADCƽ��ֵ
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc2(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 

void Get_Adc2_Convert_Data(float *Bea) //�õ�ADC������������ֵ
{
	  u16   AD2_Convert_Data;//ADC�����õ���������
	
  	AD2_Convert_Data=Get_Adc2_Average(ADC2_Channel_num,10);
	  *Bea = (float)AD2_Convert_Data*3.3/4096;
		*Bea *=100;             //����ǿ��  
	  *Bea=330-*Bea;
}

