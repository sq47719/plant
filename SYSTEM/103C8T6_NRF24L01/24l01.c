#include "24l01.h"



	


const uint8_t TX_ADDRESS_X[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//发送端地址
const uint8_t RX_ADDRESS_X[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//接收端地址


/*******************************************************************
以下是SP2的相关函数
*********************************************************************/
/*****************************************************************************
* 函  数：uint8_t SPI2_ReadWrite_Byte(uint8_t tx_dat)
* 功  能：SPI2收发数据
* 参  数：tx_dat:发送的数据
* 返回值：接收的数据
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Receive_SPI2_ReadWrite_Byte(uint8_t tx_dat)
{
		u8 retry=0;
	while(SPI_I2S_GetFlagStatus(NRF24L01_Receive_SPI_Num,SPI_I2S_FLAG_TXE)==RESET)
	{
		retry++;
		if(retry>200)return 0;
	}
	SPI_I2S_SendData(NRF24L01_Receive_SPI_Num,tx_dat);
	retry=0;
	while(SPI_I2S_GetFlagStatus(NRF24L01_Receive_SPI_Num,SPI_I2S_FLAG_RXNE)==RESET)
	{
		retry++;
		if(retry>200)return 0;
	}
	
		return SPI_I2S_ReceiveData(NRF24L01_Receive_SPI_Num);
}

void NRF24L01_Receive_SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	NRF24L01_Receive_SPI_Num->CR1&=0XFFC7;
	NRF24L01_Receive_SPI_Num->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(NRF24L01_Receive_SPI_Num,ENABLE); 

} 

/*******************************************************************
以上是SP2的相关函数
*********************************************************************/

void NRF24L01_Receive_SPI2_Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  SPI_InitTypeDef  SPI2_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Receive_SPI2_GPIO_Port,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_NRF24L01_Receive_SPI_Num,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Receive_SPI_GPIO_Pin_Num_CLK|NRF24L01_Receive_SPI_GPIO_Pin_Num_MISO|NRF24L01_Receive_SPI_GPIO_Pin_Num_MOSI;    //NRF24L01
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(NRF24L01_Receive_SPI_GPIO_Port,&GPIO_InitStructure);
	  GPIO_SetBits(NRF24L01_Receive_SPI_GPIO_Port,NRF24L01_Receive_SPI_GPIO_Pin_Num_CLK|NRF24L01_Receive_SPI_GPIO_Pin_Num_MISO|NRF24L01_Receive_SPI_GPIO_Pin_Num_MOSI);
	
		SPI2_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI2_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI2_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI2_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//空闲状态
		SPI2_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		SPI2_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI2_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
		SPI2_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI2_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(NRF24L01_Receive_SPI_Num,&SPI2_InitStructure);
		SPI_Cmd(NRF24L01_Receive_SPI_Num,ENABLE);

		NRF24L01_Receive_SPI2_ReadWrite_Byte(0xFF);//启动传输
}

void NRF24L01_Receive_GPIO_Init()
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Receive_GPIO_Port,ENABLE);
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Receive_SPI_GPIO_Pin_Num_CE2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_Receive_GPIO_Port,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Receive_SPI_GPIO_Pin_Num_IRQ2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                   //中断上拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_Receive_GPIO_Port,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Receive_SPI_GPIO_Pin_Num_CS2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_Receive_GPIO_Port,&GPIO_InitStructure);
		
		GPIO_SetBits(NRF24L01_Receive_GPIO_Port,NRF24L01_Receive_SPI_GPIO_Pin_Num_IRQ2|NRF24L01_Receive_SPI_GPIO_Pin_Num_CE2);
		GPIO_SetBits(GPIOC,NRF24L01_Receive_SPI_GPIO_Pin_Num_CS2);
}

void NRF24L01_Receive_Init()
{
    NRF24L01_Receive_GPIO_Init();
	  NRF24L01_Receive_SPI2_Init();
	
	  NRF24l01_Receive_CS2_HIGH;   //SPI片选取消 
    NRF24L01_Recevie_CE2_LOW;	   //使能24L01
}



/*****************************************************************************
* 函  数：uint8_t NRF24L01_Read_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* 功  能：在指定位置读取一定长度的数据
* 参  数：res:指定位置;len:数据长度;*pBuf:指定数据的首地址
* 返回值：status:寄存器的状态
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Receive_Read_Buf2(uint8_t res,uint8_t len,uint8_t *pBuf)
{
	uint8_t status,i;

	NRF24L01_Receive_CS2_LOW;
	status = NRF24L01_Receive_SPI2_ReadWrite_Byte(res);
	for(i=0;i<len;i++)
		{
			pBuf[i] = NRF24L01_Receive_SPI2_ReadWrite_Byte(0xFF);
	}
	NRF24l01_Receive_CS2_HIGH;

	return status;
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_Write_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* 功  能：在指定位置写入一定长度的数据
* 参  数：res:指定位置;len:数据长度;*pBuf:指定数据的首地址
* 返回值：status:寄存器的状态
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Receive_Write_Buf2(uint8_t res,uint8_t len,uint8_t *pBuf)
{
	uint8_t status,i;

	NRF24L01_Receive_CS2_LOW;
	status = NRF24L01_Receive_SPI2_ReadWrite_Byte(res);
	for (i = 0; i < len; i++)
		{
			NRF24L01_Receive_SPI2_ReadWrite_Byte(*pBuf++);
			//SPI1_ReadWrite_Byte(pBuf[i]);
		}
	NRF24l01_Receive_CS2_HIGH;
	
	return status;
}


uint8_t NRF24L01_Receive_Write_Reg2(uint8_t res,uint8_t value)
{
	uint8_t status;
	
	NRF24L01_Receive_CS2_LOW;
	status = NRF24L01_Receive_SPI2_ReadWrite_Byte(res);
	NRF24L01_Receive_SPI2_ReadWrite_Byte(value);
	NRF24l01_Receive_CS2_HIGH;

	return status;	//返回寄存器状态值
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_Read_Reg(uint8_t res)
* 功  能：从寄存器读取一字节数据
* 参  数：res:寄存器地址
* 返回值：ret:读取的值
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Receive_Read_Reg2(uint8_t res)
{
	uint8_t ret;
	
	NRF24L01_Receive_CS2_LOW;
	NRF24L01_Receive_SPI2_ReadWrite_Byte(res);
	ret = NRF24L01_Receive_SPI2_ReadWrite_Byte(0xFF);	//在读取数据前稳定MISO的电平,防止触发slave设备
	NRF24l01_Receive_CS2_HIGH;

	return ret;
}

void NRF24L01_Receive_Power_Down_Mode2(void)
{
	NRF24L01_Receive_CS2_LOW;
	NRF24L01_Receive_Write_Reg2(NRF24L01_CONFIG, 0x00);
	NRF24l01_Receive_CS2_HIGH;
	
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_Check(void)
* 功  能：检测NRF24L01是否存在
* 参  数：无
* 返回值：0:成功；1:失败
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Check2(void)
{
	uint8_t buf[5]={0xa5,0xa5,0xa5,0xa5,0xa5};
	uint8_t i;

	NRF24L01_Receive_Write_Buf2(W_REGISTER+TX_ADDR,5, buf);//写入5字节的地址
	NRF24L01_Receive_Read_Buf2(TX_ADDR, 5,buf);
	for(i=0;i<5;i++)
		{
			if(buf[i]!=0xa5)
				break;
	}
	if(i!=5)
		return 1;
	return 0;
}

/*****************************************************************************
* 函  数：void NRF24L01_TX_Mode(void)
* 功  能：NRF24L01发送模式配置
* 参  数：无
* 返回值：无
* 备  注：无
*****************************************************************************/
void NRF24L01_RX_Mode2(void)
{
	NRF24L01_Receive_CS2_LOW;
	NRF24L01_Receive_Write_Buf2(W_REGISTER+RX_ADDR_P0, RX_ADR_WIDTH, (uint8_t *) RX_ADDRESS_X);//写RX地址节点
	NRF24L01_Receive_Write_Reg2(W_REGISTER+EN_AA,0x01);//使能通道0自动应答
	NRF24L01_Receive_Write_Reg2(W_REGISTER+EN_RXADDR,0x01);//使能通道0接收地址
	NRF24L01_Receive_Write_Reg2(W_REGISTER+RF_CH, 40);                                           //设置RF通信频率
	NRF24L01_Receive_Write_Reg2(W_REGISTER+RX_PW_P0,RX_PLOAD_WIDTH);                              //选择通道0有效数据宽度
	NRF24L01_Receive_Write_Reg2(W_REGISTER+RF_SETUP, 0x0f);                                      //设置TX发射参数:0db增益,2Mbps,低噪声增益开启
	NRF24L01_Receive_Write_Reg2(W_REGISTER+NRF24L01_CONFIG, 0x0f);                               //基本参数:PWR_UP;EN_CRC;16BIT_CRC;接收模式;开启所有中断
	NRF24L01_Recevie_CE2_HIGH;                                                                   //CE为高,进入接收模式
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_RX_Packet(uint8_t *rxbuf)
* 功  能：NRF24L01接收一次数据
* 参  数：*rxbuf：等待接收数据的首地址
* 返回值：0:接收成功;1:接收数据失败
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Receive_RX_Packet2(uint8_t *rxbuf)
{
	uint8_t ret;
  NRF24L01_Receive_SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
	ret = NRF24L01_Receive_Read_Reg2(NRF24L01_STATUS);               //读取状态寄存器的值
	NRF24L01_Receive_Write_Reg2(W_REGISTER+NRF24L01_STATUS, ret);    //清除TX_DS or MAX_RT的中断标志
	if(ret&RX_OK)//接收到数据
		{
			NRF24L01_Receive_Read_Buf2(R_RX_PAYLOAD,RX_PLOAD_WIDTH,rxbuf);       //读取数据
			NRF24L01_Receive_Write_Reg2(FLUSH_RX,0xFF);                  //清除RX FIFO寄存器
			return 0;
	}
	return 1;                                                        //没有接收到数据
}


/*****************************************************************************************************
以上是NRF24L01  接收模式  SPI2的配置
******************************************************************************************************/

/*****************************************************************************************************
以上是NRF24L01  发射模式  SPI1的配置
******************************************************************************************************/

/*****************************************************************************
* 函  数：uint8_t SPI1_ReadWrite_Byte(uint8_t tx_dat)
* 功  能：SPI1收发数据
* 参  数：tx_dat:发送的数据
* 返回值：接收的数据
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Launch_SPI1_ReadWrite_Byte(uint8_t tx_dat)
{
		u8 retry=0;	
	 while(SPI_I2S_GetFlagStatus(NRF24L01_Launch_SPI_Num,SPI_I2S_FLAG_TXE)==RESET)
	 {
		   retry++;
		   if(retry>200)return 0;
	 }
		SPI_I2S_SendData(NRF24L01_Launch_SPI_Num,tx_dat);
	  	retry=0;
	 while(SPI_I2S_GetFlagStatus(NRF24L01_Launch_SPI_Num,SPI_I2S_FLAG_RXNE)==RESET)
		{
		   retry++;
		   if(retry>200)return 0;
		}	  
		return SPI_I2S_ReceiveData(NRF24L01_Launch_SPI_Num);
}

void NRF24L01_Launch_SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	NRF24L01_Launch_SPI_Num->CR1&=0XFFC7;
	NRF24L01_Launch_SPI_Num->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(NRF24L01_Launch_SPI_Num,ENABLE); 

} 

void NRF24L01_Launch_SPI1_Init()
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  SPI_InitTypeDef SPI1_InitStructure;
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Launch_SPI1_GPIO_Port,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Launch_SPI_Num,ENABLE);//spi1在APB2总线上
	
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Launch_SPI_GPIO_Pin_Num_CLK|NRF24L01_Launch_SPI_GPIO_Pin_Num_MISO|NRF24L01_Launch_SPI_GPIO_Pin_Num_MOSI;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(NRF24L01_Launch_SPI_GPIO_Port,&GPIO_InitStructure);
		GPIO_SetBits(NRF24L01_Launch_SPI_GPIO_Port,NRF24L01_Launch_SPI_GPIO_Pin_Num_CLK|NRF24L01_Launch_SPI_GPIO_Pin_Num_MOSI|NRF24L01_Launch_SPI_GPIO_Pin_Num_MISO);
	
		SPI1_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
		SPI1_InitStructure.SPI_Mode = SPI_Mode_Master;//设置SPI工作模式:设置为主SPI
		SPI1_InitStructure.SPI_DataSize = SPI_DataSize_8b;//设置SPI的数据大小:SPI发送接收8位帧结构
		SPI1_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//选择了串行时钟的稳态:时钟悬空低电平
		SPI1_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//数据捕获于第一个时钟沿
		SPI1_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//定义波特率预分频的值:波特率预分频值为16:72/16=4.5MHz
		SPI1_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI1_InitStructure.SPI_CRCPolynomial = 7;//CRC值计算的多项式
		SPI_Init(NRF24L01_Launch_SPI_Num,&SPI1_InitStructure);
		SPI_Cmd(NRF24L01_Launch_SPI_Num,ENABLE);

		NRF24L01_Launch_SPI1_ReadWrite_Byte(0xFF);//启动传输
	
}

void NRF24L01_Launch_GPIO_Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Launch_GPIO_Port,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Launch_SPI_GPIO_Pin_Num_CE;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_Launch_GPIO_Port,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Launch_SPI_GPIO_Pin_Num_IRQ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                 //中断上拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_Launch_GPIO_Port,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Launch_SPI_GPIO_Pin_Num_CS;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_Launch_GPIO_Port,&GPIO_InitStructure);
		
		GPIO_SetBits(NRF24L01_Launch_GPIO_Port,NRF24L01_Launch_SPI_GPIO_Pin_Num_IRQ|NRF24L01_Launch_SPI_GPIO_Pin_Num_CE);
		GPIO_SetBits(NRF24L01_Launch_GPIO_Port,NRF24L01_Launch_SPI_GPIO_Pin_Num_CS);
}

void NRF24L01_Launch_Init()
{
	 NRF24L01_Launch_SPI1_Init();
	 NRF24L01_Launch_GPIO_Init();
	 NRF24l01_Launch_CS_HIGH;
	 NRF24L01_Launch_CE_LOW;
}




/*****************************************************************************
* 函  数：uint8_t NRF24L01_Write_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* 功  能：在指定位置写入一定长度的数据
* 参  数：res:指定位置;len:数据长度;*pBuf:指定数据的首地址
* 返回值：status:寄存器的状态
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Launch_Write_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
{
	uint8_t status,i;

	NRF24L01_Launch_CS_LOW;
	status = NRF24L01_Launch_SPI1_ReadWrite_Byte(res);
	for (i = 0; i < len; i++)
		{
			NRF24L01_Launch_SPI1_ReadWrite_Byte(*pBuf++);
		}
	NRF24l01_Launch_CS_HIGH;
	
	return status;
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_Write_Reg(uint8_t res,uint8_t value)
* 功  能：从寄存器写入一字节数据
* 参  数：res:寄存器地址;value:写入的值
* 返回值：status:读取的寄存器状态值
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Launch_Write_Reg(uint8_t res,uint8_t value)
{
	uint8_t status;
	
	NRF24L01_Launch_CS_LOW;
	status = NRF24L01_Launch_SPI1_ReadWrite_Byte(res);
	NRF24L01_Launch_SPI1_ReadWrite_Byte(value);
	NRF24l01_Launch_CS_HIGH;

	return status;	//返回寄存器状态值
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_Read_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* 功  能：在指定位置读取一定长度的数据
* 参  数：res:指定位置;len:数据长度;*pBuf:指定数据的首地址
* 返回值：status:寄存器的状态
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Launch_Read_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
{
	uint8_t status,i;

	NRF24L01_Launch_CS_LOW;
	status = NRF24L01_Launch_SPI1_ReadWrite_Byte(res);
	for(i=0;i<len;i++)
		{
			pBuf[i] = NRF24L01_Launch_SPI1_ReadWrite_Byte(0xFF);
	}
	NRF24l01_Launch_CS_HIGH;

	return status;
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_Read_Reg(uint8_t res)
* 功  能：从寄存器读取一字节数据
* 参  数：res:寄存器地址
* 返回值：ret:读取的值
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Launch_Read_Reg(uint8_t res)
{
	uint8_t ret;
	
	NRF24L01_Launch_CS_LOW;
	NRF24L01_Launch_SPI1_ReadWrite_Byte(res);
	ret = NRF24L01_Launch_SPI1_ReadWrite_Byte(0xFF);	//在读取数据前稳定MISO的电平,防止触发slave设备
	NRF24l01_Launch_CS_HIGH;

	return ret;
}

void NRF24L01_Launch_Power_Down_Mode(void)
{
	NRF24L01_Launch_CS_LOW;
	NRF24L01_Launch_Write_Reg(NRF24L01_CONFIG, 0x00);
	NRF24l01_Launch_CS_HIGH;
	
}


/*****************************************************************************
* 函  数：uint8_t NRF24L01_Check(void)
* 功  能：检测NRF24L01是否存在
* 参  数：无
* 返回值：0:成功；1:失败
* 备  注：往NRF24L01的发送地址寄存器写入5字节数据再读出来,判断24L01是否已正常工作
*****************************************************************************/
uint8_t NRF24L01_Launch_Check(void)
{
	uint8_t buf[5]={0xA5,0xA5,0xA5,0xA5,0xA5};
	uint8_t i;

	NRF24L01_Launch_Write_Buf(W_REGISTER+TX_ADDR,5,buf);//写入5字节的地址
	NRF24L01_Launch_Read_Buf(TX_ADDR,5,buf);
	for(i=0;i<5;i++)
		{
			if(buf[i]!=0xA5)
				break;
	  }
	if(i!=5)
		return 1;
	return 0;
}

/*****************************************************************************
* 函  数：void NRF24L01_TX_Mode(void)
* 功  能：NRF24L01发送模式配置
* 参  数：无
* 返回值：无
* 备  注：无
*****************************************************************************/
void NRF24L01_Launch_TX_Mode(void)
{
	NRF24L01_Launch_CE_LOW;
	NRF24L01_Launch_Write_Buf(W_REGISTER+TX_ADDR,TX_ADR_WIDTH,(uint8_t *)TX_ADDRESS_X);//写TX节点地址
	NRF24L01_Launch_Write_Buf(W_REGISTER+RX_ADDR_P0,RX_ADR_WIDTH, (uint8_t *) RX_ADDRESS_X);//写RX节点地址,为了自动使能ACK
	NRF24L01_Launch_Write_Reg(W_REGISTER+EN_AA, 0x01);//使能通道0自动应答
	NRF24L01_Launch_Write_Reg(W_REGISTER+EN_RXADDR, 0x01);//使能通道0接收地址
	NRF24L01_Launch_Write_Reg(W_REGISTER+SETUP_PETR, 0x1a);//设置自动重发间隔时间:500us+86us,最大重大次数:10次
	NRF24L01_Launch_Write_Reg(W_REGISTER+RF_CH, 40);//设置通道为40
	NRF24L01_Launch_Write_Reg(W_REGISTER+RF_SETUP, 0x0f);//设置发射参数:0dB增益;2Mnps;低噪声增益开启
	NRF24L01_Launch_Write_Reg(W_REGISTER+NRF24L01_CONFIG,0x0e);//基本参数:PWR_UP;EN_CRC;16BIT_CRC;发送模式;开启所有中断
	NRF24L01_Launch_CE_HIGH;//NRF_CE为高,10us后启动发送数据
	delay_us(12);
}

/*****************************************************************************
* 函  数：uint8_t NRF24L01_TX_Packet(uint8_t *txbuf)
* 功  能：NRF24L01发送一次数据
* 参  数：*txbuf：等待发送数据的首地址
* 返回值：MAX_TX:最大重发次数;TX_OK:发送完成;0xFF:发送失败
* 备  注：无
*****************************************************************************/
uint8_t NRF24L01_Launch_TX_Packet(uint8_t *txbuf)
{
	uint8_t ret;
  NRF24L01_Launch_SPI1_SetSpeed(SPI_BaudRatePrescaler_8);
	NRF24L01_Launch_CE_LOW;
	NRF24L01_Launch_Write_Buf(W_TX_PAYLOAD, TX_PLOAD_WIDTH, txbuf);       //写数据到txbuf,32字节
	NRF24L01_Launch_CE_HIGH;                                         //启动发送
	
	while (NRF24L01_Launch_IRQ_STATUS);//等待发送完成
	ret = NRF24L01_Launch_Read_Reg(NRF24L01_STATUS);//读取状态寄存器的值
	NRF24L01_Launch_Write_Reg(W_REGISTER+NRF24L01_STATUS, ret);//清除TX_DS or MAX_RT的中断标志
	if(ret&MAX_TX)//达到最大重发次数
		{
			NRF24L01_Launch_Write_Reg(FLUSH_TX, 0XFF);//清除TX FIFO	寄存器
			return MAX_TX;
	}
	if(ret&TX_OK)	//发送完成
		{
			return TX_OK;
	}
	return 0xFF;//发送失败
}







