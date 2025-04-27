#include "24l01.h"



	


const uint8_t TX_ADDRESS_X[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//���Ͷ˵�ַ
const uint8_t RX_ADDRESS_X[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//���ն˵�ַ


/*******************************************************************
������SP2����غ���
*********************************************************************/
/*****************************************************************************
* ��  ����uint8_t SPI2_ReadWrite_Byte(uint8_t tx_dat)
* ��  �ܣ�SPI2�շ�����
* ��  ����tx_dat:���͵�����
* ����ֵ�����յ�����
* ��  ע����
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
	NRF24L01_Receive_SPI_Num->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(NRF24L01_Receive_SPI_Num,ENABLE); 

} 

/*******************************************************************
������SP2����غ���
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
		SPI2_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//����״̬
		SPI2_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		SPI2_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI2_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
		SPI2_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI2_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(NRF24L01_Receive_SPI_Num,&SPI2_InitStructure);
		SPI_Cmd(NRF24L01_Receive_SPI_Num,ENABLE);

		NRF24L01_Receive_SPI2_ReadWrite_Byte(0xFF);//��������
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
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                   //�ж���������
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
	
	  NRF24l01_Receive_CS2_HIGH;   //SPIƬѡȡ�� 
    NRF24L01_Recevie_CE2_LOW;	   //ʹ��24L01
}



/*****************************************************************************
* ��  ����uint8_t NRF24L01_Read_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* ��  �ܣ���ָ��λ�ö�ȡһ�����ȵ�����
* ��  ����res:ָ��λ��;len:���ݳ���;*pBuf:ָ�����ݵ��׵�ַ
* ����ֵ��status:�Ĵ�����״̬
* ��  ע����
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
* ��  ����uint8_t NRF24L01_Write_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* ��  �ܣ���ָ��λ��д��һ�����ȵ�����
* ��  ����res:ָ��λ��;len:���ݳ���;*pBuf:ָ�����ݵ��׵�ַ
* ����ֵ��status:�Ĵ�����״̬
* ��  ע����
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

	return status;	//���ؼĴ���״ֵ̬
}

/*****************************************************************************
* ��  ����uint8_t NRF24L01_Read_Reg(uint8_t res)
* ��  �ܣ��ӼĴ�����ȡһ�ֽ�����
* ��  ����res:�Ĵ�����ַ
* ����ֵ��ret:��ȡ��ֵ
* ��  ע����
*****************************************************************************/
uint8_t NRF24L01_Receive_Read_Reg2(uint8_t res)
{
	uint8_t ret;
	
	NRF24L01_Receive_CS2_LOW;
	NRF24L01_Receive_SPI2_ReadWrite_Byte(res);
	ret = NRF24L01_Receive_SPI2_ReadWrite_Byte(0xFF);	//�ڶ�ȡ����ǰ�ȶ�MISO�ĵ�ƽ,��ֹ����slave�豸
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
* ��  ����uint8_t NRF24L01_Check(void)
* ��  �ܣ����NRF24L01�Ƿ����
* ��  ������
* ����ֵ��0:�ɹ���1:ʧ��
* ��  ע����
*****************************************************************************/
uint8_t NRF24L01_Check2(void)
{
	uint8_t buf[5]={0xa5,0xa5,0xa5,0xa5,0xa5};
	uint8_t i;

	NRF24L01_Receive_Write_Buf2(W_REGISTER+TX_ADDR,5, buf);//д��5�ֽڵĵ�ַ
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
* ��  ����void NRF24L01_TX_Mode(void)
* ��  �ܣ�NRF24L01����ģʽ����
* ��  ������
* ����ֵ����
* ��  ע����
*****************************************************************************/
void NRF24L01_RX_Mode2(void)
{
	NRF24L01_Receive_CS2_LOW;
	NRF24L01_Receive_Write_Buf2(W_REGISTER+RX_ADDR_P0, RX_ADR_WIDTH, (uint8_t *) RX_ADDRESS_X);//дRX��ַ�ڵ�
	NRF24L01_Receive_Write_Reg2(W_REGISTER+EN_AA,0x01);//ʹ��ͨ��0�Զ�Ӧ��
	NRF24L01_Receive_Write_Reg2(W_REGISTER+EN_RXADDR,0x01);//ʹ��ͨ��0���յ�ַ
	NRF24L01_Receive_Write_Reg2(W_REGISTER+RF_CH, 40);                                           //����RFͨ��Ƶ��
	NRF24L01_Receive_Write_Reg2(W_REGISTER+RX_PW_P0,RX_PLOAD_WIDTH);                              //ѡ��ͨ��0��Ч���ݿ��
	NRF24L01_Receive_Write_Reg2(W_REGISTER+RF_SETUP, 0x0f);                                      //����TX�������:0db����,2Mbps,���������濪��
	NRF24L01_Receive_Write_Reg2(W_REGISTER+NRF24L01_CONFIG, 0x0f);                               //��������:PWR_UP;EN_CRC;16BIT_CRC;����ģʽ;���������ж�
	NRF24L01_Recevie_CE2_HIGH;                                                                   //CEΪ��,�������ģʽ
}

/*****************************************************************************
* ��  ����uint8_t NRF24L01_RX_Packet(uint8_t *rxbuf)
* ��  �ܣ�NRF24L01����һ������
* ��  ����*rxbuf���ȴ��������ݵ��׵�ַ
* ����ֵ��0:���ճɹ�;1:��������ʧ��
* ��  ע����
*****************************************************************************/
uint8_t NRF24L01_Receive_RX_Packet2(uint8_t *rxbuf)
{
	uint8_t ret;
  NRF24L01_Receive_SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
	ret = NRF24L01_Receive_Read_Reg2(NRF24L01_STATUS);               //��ȡ״̬�Ĵ�����ֵ
	NRF24L01_Receive_Write_Reg2(W_REGISTER+NRF24L01_STATUS, ret);    //���TX_DS or MAX_RT���жϱ�־
	if(ret&RX_OK)//���յ�����
		{
			NRF24L01_Receive_Read_Buf2(R_RX_PAYLOAD,RX_PLOAD_WIDTH,rxbuf);       //��ȡ����
			NRF24L01_Receive_Write_Reg2(FLUSH_RX,0xFF);                  //���RX FIFO�Ĵ���
			return 0;
	}
	return 1;                                                        //û�н��յ�����
}


/*****************************************************************************************************
������NRF24L01  ����ģʽ  SPI2������
******************************************************************************************************/

/*****************************************************************************************************
������NRF24L01  ����ģʽ  SPI1������
******************************************************************************************************/

/*****************************************************************************
* ��  ����uint8_t SPI1_ReadWrite_Byte(uint8_t tx_dat)
* ��  �ܣ�SPI1�շ�����
* ��  ����tx_dat:���͵�����
* ����ֵ�����յ�����
* ��  ע����
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
	NRF24L01_Launch_SPI_Num->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(NRF24L01_Launch_SPI_Num,ENABLE); 

} 

void NRF24L01_Launch_SPI1_Init()
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  SPI_InitTypeDef SPI1_InitStructure;
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Launch_SPI1_GPIO_Port,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_NRF24L01_Launch_SPI_Num,ENABLE);//spi1��APB2������
	
		GPIO_InitStructure.GPIO_Pin = NRF24L01_Launch_SPI_GPIO_Pin_Num_CLK|NRF24L01_Launch_SPI_GPIO_Pin_Num_MISO|NRF24L01_Launch_SPI_GPIO_Pin_Num_MOSI;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(NRF24L01_Launch_SPI_GPIO_Port,&GPIO_InitStructure);
		GPIO_SetBits(NRF24L01_Launch_SPI_GPIO_Port,NRF24L01_Launch_SPI_GPIO_Pin_Num_CLK|NRF24L01_Launch_SPI_GPIO_Pin_Num_MOSI|NRF24L01_Launch_SPI_GPIO_Pin_Num_MISO);
	
		SPI1_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
		SPI1_InitStructure.SPI_Mode = SPI_Mode_Master;//����SPI����ģʽ:����Ϊ��SPI
		SPI1_InitStructure.SPI_DataSize = SPI_DataSize_8b;//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
		SPI1_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//ѡ���˴���ʱ�ӵ���̬:ʱ�����յ͵�ƽ
		SPI1_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//���ݲ����ڵ�һ��ʱ����
		SPI1_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
		SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16:72/16=4.5MHz
		SPI1_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
		SPI1_InitStructure.SPI_CRCPolynomial = 7;//CRCֵ����Ķ���ʽ
		SPI_Init(NRF24L01_Launch_SPI_Num,&SPI1_InitStructure);
		SPI_Cmd(NRF24L01_Launch_SPI_Num,ENABLE);

		NRF24L01_Launch_SPI1_ReadWrite_Byte(0xFF);//��������
	
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
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                 //�ж���������
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
* ��  ����uint8_t NRF24L01_Write_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* ��  �ܣ���ָ��λ��д��һ�����ȵ�����
* ��  ����res:ָ��λ��;len:���ݳ���;*pBuf:ָ�����ݵ��׵�ַ
* ����ֵ��status:�Ĵ�����״̬
* ��  ע����
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
* ��  ����uint8_t NRF24L01_Write_Reg(uint8_t res,uint8_t value)
* ��  �ܣ��ӼĴ���д��һ�ֽ�����
* ��  ����res:�Ĵ�����ַ;value:д���ֵ
* ����ֵ��status:��ȡ�ļĴ���״ֵ̬
* ��  ע����
*****************************************************************************/
uint8_t NRF24L01_Launch_Write_Reg(uint8_t res,uint8_t value)
{
	uint8_t status;
	
	NRF24L01_Launch_CS_LOW;
	status = NRF24L01_Launch_SPI1_ReadWrite_Byte(res);
	NRF24L01_Launch_SPI1_ReadWrite_Byte(value);
	NRF24l01_Launch_CS_HIGH;

	return status;	//���ؼĴ���״ֵ̬
}

/*****************************************************************************
* ��  ����uint8_t NRF24L01_Read_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
* ��  �ܣ���ָ��λ�ö�ȡһ�����ȵ�����
* ��  ����res:ָ��λ��;len:���ݳ���;*pBuf:ָ�����ݵ��׵�ַ
* ����ֵ��status:�Ĵ�����״̬
* ��  ע����
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
* ��  ����uint8_t NRF24L01_Read_Reg(uint8_t res)
* ��  �ܣ��ӼĴ�����ȡһ�ֽ�����
* ��  ����res:�Ĵ�����ַ
* ����ֵ��ret:��ȡ��ֵ
* ��  ע����
*****************************************************************************/
uint8_t NRF24L01_Launch_Read_Reg(uint8_t res)
{
	uint8_t ret;
	
	NRF24L01_Launch_CS_LOW;
	NRF24L01_Launch_SPI1_ReadWrite_Byte(res);
	ret = NRF24L01_Launch_SPI1_ReadWrite_Byte(0xFF);	//�ڶ�ȡ����ǰ�ȶ�MISO�ĵ�ƽ,��ֹ����slave�豸
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
* ��  ����uint8_t NRF24L01_Check(void)
* ��  �ܣ����NRF24L01�Ƿ����
* ��  ������
* ����ֵ��0:�ɹ���1:ʧ��
* ��  ע����NRF24L01�ķ��͵�ַ�Ĵ���д��5�ֽ������ٶ�����,�ж�24L01�Ƿ�����������
*****************************************************************************/
uint8_t NRF24L01_Launch_Check(void)
{
	uint8_t buf[5]={0xA5,0xA5,0xA5,0xA5,0xA5};
	uint8_t i;

	NRF24L01_Launch_Write_Buf(W_REGISTER+TX_ADDR,5,buf);//д��5�ֽڵĵ�ַ
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
* ��  ����void NRF24L01_TX_Mode(void)
* ��  �ܣ�NRF24L01����ģʽ����
* ��  ������
* ����ֵ����
* ��  ע����
*****************************************************************************/
void NRF24L01_Launch_TX_Mode(void)
{
	NRF24L01_Launch_CE_LOW;
	NRF24L01_Launch_Write_Buf(W_REGISTER+TX_ADDR,TX_ADR_WIDTH,(uint8_t *)TX_ADDRESS_X);//дTX�ڵ��ַ
	NRF24L01_Launch_Write_Buf(W_REGISTER+RX_ADDR_P0,RX_ADR_WIDTH, (uint8_t *) RX_ADDRESS_X);//дRX�ڵ��ַ,Ϊ���Զ�ʹ��ACK
	NRF24L01_Launch_Write_Reg(W_REGISTER+EN_AA, 0x01);//ʹ��ͨ��0�Զ�Ӧ��
	NRF24L01_Launch_Write_Reg(W_REGISTER+EN_RXADDR, 0x01);//ʹ��ͨ��0���յ�ַ
	NRF24L01_Launch_Write_Reg(W_REGISTER+SETUP_PETR, 0x1a);//�����Զ��ط����ʱ��:500us+86us,����ش����:10��
	NRF24L01_Launch_Write_Reg(W_REGISTER+RF_CH, 40);//����ͨ��Ϊ40
	NRF24L01_Launch_Write_Reg(W_REGISTER+RF_SETUP, 0x0f);//���÷������:0dB����;2Mnps;���������濪��
	NRF24L01_Launch_Write_Reg(W_REGISTER+NRF24L01_CONFIG,0x0e);//��������:PWR_UP;EN_CRC;16BIT_CRC;����ģʽ;���������ж�
	NRF24L01_Launch_CE_HIGH;//NRF_CEΪ��,10us��������������
	delay_us(12);
}

/*****************************************************************************
* ��  ����uint8_t NRF24L01_TX_Packet(uint8_t *txbuf)
* ��  �ܣ�NRF24L01����һ������
* ��  ����*txbuf���ȴ��������ݵ��׵�ַ
* ����ֵ��MAX_TX:����ط�����;TX_OK:�������;0xFF:����ʧ��
* ��  ע����
*****************************************************************************/
uint8_t NRF24L01_Launch_TX_Packet(uint8_t *txbuf)
{
	uint8_t ret;
  NRF24L01_Launch_SPI1_SetSpeed(SPI_BaudRatePrescaler_8);
	NRF24L01_Launch_CE_LOW;
	NRF24L01_Launch_Write_Buf(W_TX_PAYLOAD, TX_PLOAD_WIDTH, txbuf);       //д���ݵ�txbuf,32�ֽ�
	NRF24L01_Launch_CE_HIGH;                                         //��������
	
	while (NRF24L01_Launch_IRQ_STATUS);//�ȴ��������
	ret = NRF24L01_Launch_Read_Reg(NRF24L01_STATUS);//��ȡ״̬�Ĵ�����ֵ
	NRF24L01_Launch_Write_Reg(W_REGISTER+NRF24L01_STATUS, ret);//���TX_DS or MAX_RT���жϱ�־
	if(ret&MAX_TX)//�ﵽ����ط�����
		{
			NRF24L01_Launch_Write_Reg(FLUSH_TX, 0XFF);//���TX FIFO	�Ĵ���
			return MAX_TX;
	}
	if(ret&TX_OK)	//�������
		{
			return TX_OK;
	}
	return 0xFF;//����ʧ��
}







