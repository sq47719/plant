#include "HX711.h"
#include "delay.h"




u32 Weight_Maopi;
s32 Weight_Shiwu;
/****************************************************
              电子称初始化引脚配置	
*****************************************************/
void HX711_InIt ( void ) 
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_HX711_GPIO_Port, ENABLE );   
    GPIO_InitStructure.GPIO_Pin = HX711_GPIO_Pin_Num_SCLK ;            //配置HX711的数据引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                   //配置推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init ( HX711_GPIO_Port , &GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = HX711_GPIO_Pin_Num_Data ;           //配置HX711的时钟引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             //配置浮点输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init ( HX711_GPIO_Port , &GPIO_InitStructure );
}
/****************************************************
              电子称读取当前质量
*****************************************************/
unsigned long HX711_Read() 
{
    unsigned int val = 0;
    unsigned char i = 0;
    DOUT = 1;
    SCK = 0;

    while ( DIN );

    delay_us ( 1 );

    for ( i = 0; i < 24; i++ ) {
        SCK = 1;
        val = val << 1;
        delay_us ( 1 );
        SCK = 0;

        if ( DIN ) {
            val++;
        }

        delay_us ( 1 );
    }

    SCK = 1;
    val = val ^ 0x800000;
    delay_us ( 1 );
    SCK = 0;
    delay_us ( 1 );
    return val;
}
/****************************************************
              电子称读取皮的重量
*****************************************************/
void Get_Maopi() 
{
    Weight_Maopi = HX711_Read();
}
/****************************************************
              电子称读取实物重量
*****************************************************/
void Get_Weight() 
{
    Weight_Shiwu = HX711_Read();
    Weight_Shiwu = Weight_Shiwu - Weight_Maopi;

    if ( Weight_Shiwu > 0 ) {
        Weight_Shiwu = ( unsigned short ) ( Weight_Shiwu * 1.0 / GapValue );
    } else {
        Weight_Shiwu = 0;
    }
}
