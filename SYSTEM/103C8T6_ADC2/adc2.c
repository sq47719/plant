 #include "adc2.h"
 #include "delay.h"	

 #include "math.h"


   
void  Adc2_Init(void)//ADC初始化调用函数
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AD2_GPIO_Port | RCC_APB2Periph_AD2_Num , ENABLE );	  //使能ADC2通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	                
	GPIO_InitStructure.GPIO_Pin = ADC2_GPIO_Pin_Num;// 模拟通道输入引脚         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入引脚
	GPIO_Init(ADC2_GPIO_Port, &GPIO_InitStructure);	

	ADC_DeInit(ADC2_Num);  //复位ADC2,将外设 ADC2 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel =1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC2_Num, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC2_Num, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC2_Num);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC2_Num));	//等待复位校准结束
	
	ADC_StartCalibration(ADC2_Num);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC2_Num));	 //等待校准结束

}				  

u16 Get_Adc2(u8 ch)   //获得ADC值
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2_Num, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC2_Num, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2_Num, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC2_Num);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc2_Average(u8 ch,u8 times)//ADC调用，获取ADC平均值
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

void Get_Adc2_Convert_Data(float *Bea) //得到ADC的最终数字量值
{
	  u16   AD2_Convert_Data;//ADC采样得到的数字量
	
  	AD2_Convert_Data=Get_Adc2_Average(ADC2_Channel_num,10);
	  *Bea = (float)AD2_Convert_Data*3.3/4096;
		*Bea *=100;             //光照强度  
	  *Bea=330-*Bea;
}

