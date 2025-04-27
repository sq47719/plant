 #include "adc.h"
 #include "delay.h"	
 #include "math.h"


   
 void  Adc_Init(void)//ADC初始化调用函数
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port |RCC_APB2Periph_AD_Num	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num;// 模拟通道输入引脚         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(ADC1_GPIO_Port, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel =1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC_Num, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC_Num, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC_Num);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//等待复位校准结束
	
	ADC_StartCalibration(ADC_Num);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //等待校准结束

}				  

u16 Get_Adc(u8 ch)   //获得ADC值
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC_Num, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC_Num, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC_Num, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC_Num);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)//ADC调用，获取ADC平均值
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
void Get_Adc_Convert_Data(float *Smo) //得到ADC的最终数字量值
{
	  u16   AD_Convert_Data;//ADC采样得到的数字量
	
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num,1);
	  *Smo = (float)AD_Convert_Data*5/4096;
		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
		*Smo *=100;             //浓度单位  PPM
}

void Get_Adc_Convert_Data_MQ135(float *Smo) //得到ADC的最终数字量值
{
	  u16   AD_Convert_Data;//ADC采样得到的数字量
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num,1);
	  *Smo = (float)AD_Convert_Data*5/4096;
		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
		*Smo *=100;             //浓度单位  PPM
}

void Get_Adc_Convert_Data_MQ_2(float *Smo) //得到ADC的最终数字量值
{
	  u16   AD_Convert_Data;//ADC采样得到的数字量
	
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_3,1);
	  *Smo = (float)AD_Convert_Data*5/4096;
		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
		*Smo *=100;             //浓度单位  PPM
}

void Adc_Init1(void)//ADC初始化调用函数
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_1 |RCC_APB2Periph_AD_Num_1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_1;// 模拟通道输入引脚         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(ADC1_GPIO_Port_1, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel =1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC_Num, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC_Num, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC_Num);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//等待复位校准结束
	
	ADC_StartCalibration(ADC_Num);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //等待校准结束

}	

void Adc_Init2(void)//ADC初始化调用函数
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_2 |RCC_APB2Periph_AD_Num_2	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_2;// 模拟通道输入引脚         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(ADC1_GPIO_Port_2, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel =1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC_Num, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC_Num, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC_Num);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//等待复位校准结束
	
	ADC_StartCalibration(ADC_Num);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //等待校准结束

}	

void  Adc_Init3(void)//ADC初始化调用函数
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_3 |RCC_APB2Periph_AD_Num_3	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_3;// 模拟通道输入引脚         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(ADC1_GPIO_Port_3, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel =1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC_Num, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC_Num, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC_Num);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//等待复位校准结束
	
	ADC_StartCalibration(ADC_Num);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //等待校准结束

}		
void  Adc_Init4(void)//ADC初始化调用函数
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD1_GPIO_Port_4 |RCC_APB2Periph_AD_Num_4	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_Pin_Num_4;// 模拟通道输入引脚         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(ADC1_GPIO_Port_4, &GPIO_InitStructure);	

	ADC_DeInit(ADC_Num);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel =1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC_Num, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC_Num, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC_Num);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC_Num));	//等待复位校准结束
	
	ADC_StartCalibration(ADC_Num);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC_Num));	 //等待校准结束

}		

void Get_adc(float *Smo)
{
	
		u16   AD_Convert_Data;//ADC采样得到的数字量
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num,1);
	  *Smo = (float)AD_Convert_Data/4096*100;
}
void Get_adc1(int *water_high)
{
	  u16 AD_Convert_Data;//ADC采样得到的数字量
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_1,1);
		*water_high = 100-(float)AD_Convert_Data/4096*100;

}
void Get_adc2(float *co2)
{
		u16   AD_Convert_Data;//ADC采样得到的数字量
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_2,1);
	  *co2 = (float)AD_Convert_Data/4096*100;
//		*co2 *=100;             //浓度单位  PPM
}
void Get_adc3(float *Smo)
{
		u16   AD_Convert_Data;//ADC采样得到的数字量
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_3,1);
	  *Smo = (float)AD_Convert_Data/4096*100;
//		*Smo *=100;             //浓度单位  PPM
}

void Get_adc4(float *Smo)
{
		u16   AD_Convert_Data;//ADC采样得到的数字量
  	AD_Convert_Data=Get_Adc_Average(ADC1_Channel_num_4,1);
	  *Smo = (float)AD_Convert_Data/4096*100;
//		*Smo =pow(11.5428*35.9*(*Smo)/(25.5-5.1*(*Smo)),0.6549);
//		*Smo *=100;             //浓度单位  PPM
}







