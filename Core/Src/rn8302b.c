/****************SPI 采用端口模拟**********************************/
#include "rn8302b.h"
#include "spi.h"
#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"


uint32_t temp = 0;
 
/*****************SPI 写单字节**************************/
void Write_SPI_OneByte(uint8_t TxData)
{
	uint8_t Rxdata;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//	HAL_SPI_Transmit(&hspi2,&TxData,1, 1000);
}
/*****************SPI 读单字节**************************/
uint8_t Read_SPI_OneByte(void)
{
	uint8_t Rxdata;
	uint8_t TxData=0;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
//	HAL_SPI_Receive(&hspi2,&Rxdata,1, 1000);
	return Rxdata;
}



static void RN8302_GraftDelay_us(uint32_t us)
{
	//Lib_DelayUs_Debug(1);
//	vTaskDelay(1);
	HAL_Delay(1);
}



/*
 * Function     ：static void RN8302_GraftDelay_ms(uint32_t ms)
 * Description  ：毫秒级延时
 * Input        ：ms--延时时间
 * Output       ：None
 * Return       ：None
 * Others       ：移植函数
 * Record       : gwh,2018.9.27
 */
static void RN8302_GraftDelay_ms(uint32_t ms)
{
//	vTaskDelay(ms);
	HAL_Delay(ms);
}



/*
 * Function     ：static void RN8302_GraftSpiWriteByte(uint8_t data)
 * Description  ：写单个字节
 * Input        ：data
 * Output       ：None
 * Return       ：None
 * Others       ：移植函数
 * Record       : gwh,2018.9.27
 */
void RN8302_GraftSpiInit(void)
{
	MX_SPI2_Init();
}


/*
 * Function     ：static void RN8302_GraftSpiWriteByte(uint8_t data)
 * Description  ：写单个字节
 * Input        ：data
 * Output       ：None
 * Return       ：None
 * Others       ：移植函数
 * Record       : gwh,2018.9.27
 */
static void RN8302_GraftSpiWriteByte(uint8_t TxData)
{
	uint8_t Rxdata;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
}



/*
 * Function     ：static uint8_t RN8302_GraftSpiReadByte(void)
 * Description  ：读单个字节
 * Input        ：None
 * Output       ：buff--写入的数据
 * Return       ：读取到的字节数据
 * Others       ：移植函数
 * Record       : gwh,2018.9.27
 */
static uint8_t RN8302_GraftSpiReadByte(void)
{
	uint8_t Rxdata;
	uint8_t TxData=0;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&Rxdata,1, 1000);
//	HAL_SPI_Receive(&hspi2,&Rxdata,1, 1000);
	return Rxdata;
}

/************************* READ_RN8302*************************************************/
uint32_t READ_SPI(uint16_t Address,uint8_t Data_len)
{
	SPI_HandleTypeDef hspi2;
	
	uint8_t i, DTemp,CheckSumR;
	uint32_t drData;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	DTemp = (uint8_t)(Address&0x00FF);//ADDR[7:0]
	CheckSumR = DTemp;
	Write_SPI_OneByte(DTemp);
	DTemp = (((uint8_t)(Address >> 4)) & 0xf0) ;//CMD=R/W+AD[10:8]+BL[1:0]+2’h0(MSB+LSB)
	CheckSumR += DTemp;
	Write_SPI_OneByte(DTemp);
	drData = 0x00000000;//Read 24bit

	for(i=0;i<Data_len;i++)//先发高字节，后发低字节
	{
		DTemp = Read_SPI_OneByte();
		drData = drData<<8;
		drData += DTemp;
		CheckSumR += DTemp;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
 
	CheckSumR = CheckSumR^0x0ff;//校验和算法： ADDR+CMD+DATA 单字节求和取反。
 
//	if (CheckSumR != Read_SPI_OneByte())//比较校验和
//	{
//		drData = 0xFFFFFFFF;
//	}
 
//	SPI_CS_HIGH();	  //关闭SPI传输
//	HAL_Delay(2);
	return drData;
}
/**************************Write RN8302******************************/
void Write_SPI(uint16_t Address, uint32_t dwData,uint8_t Date_len)
{
	uint8_t i,CheckSumR, DTemp,Repeat;
	for(Repeat = 3; Repeat > 0 ; --Repeat)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//	SPI_CS_LOW();	 //开启SPI传输
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//	SPI_CS_LOW();	 //开启SPI传输

		DTemp = (uint8_t)(Address&0x00FF);//
		CheckSumR = DTemp;
		Write_SPI_OneByte(DTemp);//写地址
		DTemp = (((uint8_t)(Address >> 4)) & 0xf0)+0x80 ;
		CheckSumR += DTemp;
		Write_SPI_OneByte(DTemp);//写命令
	 
		for (i =0 ;i < Date_len;i++)//先发高字节，后发低字节
		{
			DTemp = (uint8_t)(dwData>>(Date_len-1-i)*8);
			Write_SPI_OneByte(DTemp);//写命令
			CheckSumR += DTemp;
		}
	 
		CheckSumR = CheckSumR^0x0ff;//校验和算法： ADDR+CMD+DATA 单字节求和取反。
	 
		Write_SPI_OneByte(CheckSumR);//写命令
	 
	//	SPI_CS_HIGH();	    //结束传输
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	//	HAL_Delay(2);
	}
}
 
static ErrorStatus RN8302_WriteData(uint16_t reg, uint8_t *buff, uint8_t data_len)
{
	uint8_t i, temp, Repeat;
	uint8_t chksum;
	ErrorStatus err = SUCCESS;

	/*防止溢出*/
	if((data_len == 0) || (data_len > 4))
	{
		return(ERROR);
	}

	for(Repeat = 3; Repeat > 0 ; --Repeat)
	{
		/*片选拉低*/
//		if(xTaskGetCurrentTaskHandle() == xTaskHandle_Meter)
//		{
//			CHG1_METER_EN();
//		}
//		else
//		{
//			CHG2_METER_EN();
//		}
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//	SPI_CS_LOW();	 //开启SPI传输

		//RN8302_SPI_CS_0;
		RN8302_GraftDelay_us(1);

		/*address*/
		temp = (uint8_t)(reg & 0x00ff);
		chksum = temp;

		RN8302_GraftSpiWriteByte(temp);

		/*cmd*/
		temp = (((uint8_t)(reg >> 4)) & 0xf0) + 0x80;
		chksum += temp;
		RN8302_GraftSpiWriteByte(temp);

		/*data*/
		for(i = data_len; i > 0; --i)
		{
			RN8302_GraftSpiWriteByte(buff[i - 1]);
			chksum += buff[i - 1];
		}

		/*checksum*/
		chksum = ~chksum;
		RN8302_GraftSpiWriteByte(chksum);
		RN8302_GraftDelay_ms(5);
		/*read reg in order to check*/
		RN8302_GraftSpiWriteByte(0x8D);
		chksum = 0x8D;

		temp = ((uint8_t)(0x018D >> 4) & 0xf0);
		RN8302_GraftSpiWriteByte(temp);
		chksum += temp;

		for(i = 3 ; i > 0 ; i--)//3
		{
			temp = RN8302_GraftSpiReadByte();

			if(data_len >= i)
			{
				if(temp != buff[i - 1])
				{
					err = ERROR;
					break;
				}
			}

			chksum += temp;
		}

		if(err == SUCCESS)
		{
			chksum = ~chksum;
			temp = RN8302_GraftSpiReadByte();

			if(temp != (uint8_t)chksum)
			{
				err = ERROR;
			}
		}

		RN8302_GraftDelay_us(1);

//		if(xTaskGetCurrentTaskHandle() == xTaskHandle_Meter)
//		{
//			CHG1_METER_DIS();
//		}
//		else
//		{
//			CHG2_METER_DIS();
//		}
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//	SPI_CS_LOW();	 //关闭SPI传输
		//RN8302_SPI_CS_1;

		if(err == SUCCESS)
		{
			break;
		}

		RN8302_GraftDelay_us(10);
	}

	return(err);
}


void ReadAmmeterData(void)
{
	
	
	uint8_t byte[1]={0xdc};
	uint8_t byte1[2]={0x07,0xd0};
	RN8302_WriteData(RN8302_WREN, byte, 1);
	temp=READ_SPI(RN8302_WREN,1);
	printf("%x\r\n",temp);
	
	byte[0]=0xE5;
	RN8302_WriteData(RN8302_WREN, byte, 1);
	temp=READ_SPI(RN8302_WREN,1);
	printf("%x\r\n",temp);
	
	byte[0]=0xa2;
	RN8302_WriteData(RN8302_WMSW, byte, 1);
	temp=READ_SPI(RN8302_WMSW,1);
	printf("%x\r\n",temp);
	
	byte[0]=0xfa;
	RN8302_WriteData(RN8302_SOFTRST, byte, 1);
	temp=READ_SPI(RN8302_SOFTRST,1);
	printf("%x\r\n",temp);
		
	HAL_Delay(20);
	byte[0]=0x00;
	RN8302_WriteData(RN8302_MODSEL, byte, 1);//0x00表示三相四线
	
		
	byte[0]=0xff;
	RN8302_WriteData(RN8302_EMUCON, byte, 1);
	temp=READ_SPI(RN8302_EMUCON,1);
	printf("%x\r\n",temp);
	
	byte[0]=0xfa;
	Write_SPI(RN8302_HFConst1, 0x07d0,0x02);//，配置HFConst1寄存器
	RN8302_WriteData(RN8302_HFConst1, byte1, 1);
	byte[0]=0xfa;
	Write_SPI(RN8302_HFConst2, 0x07d0,0x02);//，配置HFConst2寄存器
	RN8302_WriteData(RN8302_HFConst2, byte1, 1);
		
	byte[0]=0xdc;
	RN8302_WriteData(RN8302_WREN, byte, 1);

}

void delay_us(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}

