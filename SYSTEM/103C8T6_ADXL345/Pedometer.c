/******************************************************************************

 ******************************************************************************
*  文 件 名   : Pedometer.c
Pedometer计步算法子程序
******************************************************************************/
#include "adxl345.h"
#include "Pedometer.h"



_Bool ADXL345_FLAG=0;  			//读取标志位 利用定时器取200ms读取一次数据 人的步数大概是1S一步
//unsigned char START_FLAG=0;				//开始计步标志位
//unsigned char number=0;

unsigned char  bad_flag[3];
unsigned int  array0[3]={1,1,1};
unsigned int  array1[3]={1,1,1};
unsigned int  array2[3]={0,0,0};
unsigned int  adresult[3];
unsigned int  max[3]={0,0,0};
unsigned int  min[3]={1000,1000,1000};
unsigned int  dc[3]={500,500,500};
unsigned int  vpp[3]={30,30,30};	
unsigned int  precision[3]={5,5,5};	
unsigned int  old_fixed[3];
unsigned int  new_fixed[3];
unsigned int  STEPS=0;
//unsigned int  time=0;
										
//float  speed=0;
//float  dist=0;
//float  kalul=0;
/*------------------------------------------------------------------------------------------------------------------------
*Name: 		step_counter()
*Function:	实现Pedometer的基本算法.
*Input:		void
*Output: 	void
*------------------------------------------------------------------------------------------------------------------------*/
void step_counter(void)
{
	static unsigned char sampling_counter=0;
	unsigned char  jtemp;
	
	short x,y,z;
	
	ADXL345_RD_XYZ(&x,&y,&z);	//连续读出数据，存储在BUF中
	//------------------------------------------采样滤波----------------------//
	for(jtemp=0;jtemp<=2;jtemp++)      //jtemp 0,1,2分别代表x，y，z
	{		
		array2[jtemp]=array1[jtemp];
		array1[jtemp]=array0[jtemp];			
   		array0[jtemp]=DATBUF[2*jtemp]+(DATBUF[2*jtemp+1]<<8);
   		
   		adresult[jtemp]=array0[jtemp]+array1[jtemp]+array2[jtemp];
  	 	adresult[jtemp]=adresult[jtemp]/3;
		if(adresult[jtemp]>max[jtemp])               {max[jtemp]=adresult[jtemp];}
		if(adresult[jtemp]<min[jtemp])               {min[jtemp]=adresult[jtemp];}
	}
  	sampling_counter=sampling_counter+1;
	//----------------------------------计算动态门限和动态精度-----------------------//
    if(sampling_counter>=50)
    {                
      	sampling_counter=0;			
		for(jtemp=0;jtemp<=2;jtemp++)
		{
			vpp[jtemp]=max[jtemp]-min[jtemp];
        	dc[jtemp] =min[jtemp]+(vpp[jtemp]>>1);    //dc为阈值
			max[jtemp]=0;
        	min[jtemp]=1023;
			bad_flag[jtemp]=0;
			if(vpp[jtemp]>=160)
			{
				precision[jtemp]=vpp[jtemp]/32; //8
			}
        	else if((vpp[jtemp]>=50)&& (vpp[jtemp]<160))            
			{
				precision[jtemp]=4;
			}
       		else if((vpp[jtemp]>=15) && (vpp[jtemp]<50))  
            {
				precision[jtemp]=3;
			}  			
			else
       		{ 
          		precision[jtemp]=2;
            	bad_flag[jtemp]=1;
        	}
		}
  	}		
	//--------------------------线性移位寄存器--------------------------------------
	for(jtemp=0;jtemp<=2;jtemp++)
	{
		old_fixed[jtemp]=new_fixed[jtemp];

    	if(adresult[jtemp]>=new_fixed[jtemp])                         
    	{   
     		if((adresult[jtemp]-new_fixed[jtemp])>=precision[jtemp])   {new_fixed[jtemp]=adresult[jtemp];}
    	}
    	else if(adresult[jtemp]<new_fixed[jtemp])
   	 	{   
       		if((new_fixed[jtemp]-adresult[jtemp])>=precision[jtemp])   {new_fixed[jtemp]=adresult[jtemp];}
    	}
	}
	//------------------------- 动态门限判决 ----------------------------------
	if((vpp[0]>=vpp[1])&&(vpp[0]>=vpp[2]))   //x轴最活跃
	{
		if((old_fixed[0]>=dc[0])&&(new_fixed[0]<dc[0])&&(bad_flag[0]==0))        
		{
			STEPS=STEPS+1;
		} 
	}
	else if((vpp[1]>=vpp[0])&&(vpp[1]>=vpp[2]))  //y轴最活跃
	{
		if((old_fixed[1]>=dc[1])&&(new_fixed[1]<dc[1])&&(bad_flag[1]==0))        
		{
			STEPS=STEPS+1;
		}
	}
	else if((vpp[2]>=vpp[1])&&(vpp[2]>=vpp[0]))    //z轴最活跃
	{
		if((old_fixed[2]>=dc[2])&&(new_fixed[2]<dc[2])&&(bad_flag[2]==0))        
		{
			STEPS=STEPS+1;
		}
	}
}

