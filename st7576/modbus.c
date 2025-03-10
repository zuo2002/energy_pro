#include "modbus.h"
#include "usart.h"
MODBUS modbus;

extern float UA_val;//电压实际值
extern float UB_val;
extern float UC_val;

extern float IA_val;//电流实际值
extern float IB_val;
extern float IC_val;

extern float PA_val;//相有功功率实际值
extern float PB_val;
extern float PC_val;
extern float FEQT_val;

extern float Deplete_A_val;//功耗
extern float Deplete_B_val;
extern float Deplete_C_val;
extern float Deplete_all_val;

extern float pwr;

extern float UFreq_val;

extern uint16_t UA_val_h,UA_val_l;

uint8_t bytes[4];
void floatToUint16Pair(float f, uint16_t* part1, uint16_t* part2) {
    uint32_t temp = *(uint32_t *)&f;
    *part1 = temp >> 16;
    *part2 = temp & 0xFFFF;
}

uint16_t Reg[32] ={
           0};//reg是提前定义好的寄存器和寄存器数据，要读取和改写的部分内容
 // Modbus初始化函数
					 
					 
 void Modbus_Init(void)
 {
   modbus.myadd = 0x01; //从机设备地址为2
   modbus.timrun = 0;    //modbus定时器停止计算
	 modbus.slave_add=0x02;//主机要匹配的从机地址（本设备作为主机时）
	 modbus.reflag = 0;//无数据包处理
	 modbus.Host_time_flag = 0;//发送数据标志
	 modbus.recount = 0;//接收到的字节数
	 modbus.timout = 0;//超时时间 单位：ms
	 modbus.Host_Sendtime = 0;//发送完上一帧后的时间计数 单位：ms
 }
					 
 // Modbus事件处理函数
 void Modbus_Event(void)
 {
 	uint16_t crc,rccrc;//crc和接收到的crc
 	//没有收到数据包

   if(modbus.reflag == 0)  //如果接收未完成则返回空
 	{
 	   return;
 	}
 	//收到数据包(接收完成)
 	//通过读到的数据帧计算CRC
 	//参数1是数组首地址，参数2是要计算的长度（除了CRC校验位其余全算）
 	crc = Modbus_CRC16(&modbus.rcbuf[0],modbus.recount-2); //获取CRC校验位
 	// 读取数据帧的CRC
 	rccrc = modbus.rcbuf[modbus.recount-2]*256+modbus.rcbuf[modbus.recount-1];//计算读取的CRC校验位
 	//等价于下面这条语句
 	//rccrc=modbus.rcbuf[modbus.recount-1]|(((uint16_t)modbus.rcbuf[modbus.recount-2])<<8);//获取接收到的CRC
 	if(crc == rccrc) //CRC检验成功 开始分析包
 	{	
 	   if(modbus.rcbuf[0] == modbus.myadd)  // 检查地址是否时自己的地址
 		 {
 		   switch(modbus.rcbuf[1])   //分析modbus功能码
 			 {
 			   case 0:             break;
 				 case 1:             break;
 				 case 2:             break;
 				 case 3:       Modbus_Func3();break;//这是读取寄存器的数据
 				 case 4:             break;
 				 case 5:             break;
          case 6:      Modbus_Func6();      break;//这是写入单个寄存器数据
 				 case 7:             break;
 				 case 8:             break;
 				 case 9:             break;
 				 case 16:     Modbus_Func16(); 			break;//写入多个寄存器数据
 			 }
 		 }
 		 else if(modbus.rcbuf[0] == 0) //广播地址不予回应
 		 {
 		    
 		 }	 
 	}	
 	 modbus.recount = 0;//接收计数清零
   modbus.reflag = 0; //接收标志清零
 }

 /*
 ********************************************************************************
 主机：03
 01  03      00 01     00 01          D5 CA	从地址01开始读读取一个寄存器的数据内容
 ID 功能码  起始地址  读取寄存器的个数
 从机返回：
 01  03       02       00 03          F8 45 返回了两个字节的数据，数据是00 03
 ID  功能码  几个字节  返回的数据内容
 
 ********************************************************************************
 */
 // Modbus 3号功能码函数
 // Modbus 主机读取寄存器值
 void Modbus_Func3(void)
 {
   uint16_t Regadd,Reglen,crc;
 	uint8_t i,j;	
 	//得到要读取寄存器的首地址
    floatToUint16Pair(UA_val, &Reg[0], &Reg[1]);
    floatToUint16Pair(UB_val, &Reg[2], &Reg[3]);
    floatToUint16Pair(UC_val, &Reg[4], &Reg[5]);
    floatToUint16Pair(IA_val, &Reg[6], &Reg[7]);
    floatToUint16Pair(IB_val, &Reg[8], &Reg[9]);
    floatToUint16Pair(IC_val, &Reg[10], &Reg[11]);
    floatToUint16Pair(PA_val, &Reg[12], &Reg[13]);
    floatToUint16Pair(PB_val, &Reg[14], &Reg[15]);
    floatToUint16Pair(PC_val, &Reg[16], &Reg[17]);
    floatToUint16Pair(FEQT_val, &Reg[18], &Reg[19]);
    floatToUint16Pair(Deplete_A_val, &Reg[20], &Reg[21]);
    floatToUint16Pair(Deplete_B_val, &Reg[22], &Reg[23]);
    floatToUint16Pair(Deplete_C_val, &Reg[24], &Reg[25]);
    floatToUint16Pair(Deplete_all_val, &Reg[26], &Reg[27]);
    floatToUint16Pair(UFreq_val, &Reg[28], &Reg[29]);
    floatToUint16Pair(pwr, &Reg[30], &Reg[31]);

	 
 	Regadd = modbus.rcbuf[2]*256+modbus.rcbuf[3];//读取的首地址
 	//得到要读取寄存器的数据长度
 	Reglen = modbus.rcbuf[4]*256+modbus.rcbuf[5];//读取的寄存器个数
 	//发送回应数据包
 	i = 0;
 	modbus.sendbuf[i++] = modbus.myadd;      //ID号：发送本机设备地址
 	modbus.sendbuf[i++] = 0x03;              //发送功能码
   modbus.sendbuf[i++] = ((Reglen*2)%256);   //返回字节个数
 	for(j=0;j<Reglen;j++)                    //返回数据
 	{
 		//reg是提前定义好的16位数组（模仿寄存器）
 	  modbus.sendbuf[i++] = Reg[Regadd+j]/256;//高位数据
 		modbus.sendbuf[i++] = Reg[Regadd+j]%256;//低位数据
 	}
 	crc = Modbus_CRC16(modbus.sendbuf,i);    //计算要返回数据的CRC
 	modbus.sendbuf[i++] = crc/256;//校验位高位
 	modbus.sendbuf[i++] = crc%256;//校验位低位
 	//数据包打包完成
 	// 开始返回Modbus数据
 	
 	RS485DIR_TX;//这是开启485发送
 	
 	for(j=0;j<i;j++)//发送数据
 	{
 	  Modbus_Send_Byte(modbus.sendbuf[j]);	
 	}
 	RS485DIR_RX;//这里是关闭485发送
 }


 
  // Modbus 6号功能码函数
 // Modbus 主机写入寄存器值
 void Modbus_Func6()  
 {
   uint16_t Regadd;//地址16位
 	uint16_t val;//值
 	uint16_t i,crc,j;
 	i=0;
   Regadd=modbus.rcbuf[2]*256+modbus.rcbuf[3];  //得到要修改的地址 
 	val=modbus.rcbuf[4]*256+modbus.rcbuf[5];     //修改后的值（要写入的数据）
 	Reg[Regadd]=val;  //修改本设备相应的寄存器
 	
 	//以下为回应主机
 	modbus.sendbuf[i++]=modbus.myadd;//本设备地址
   modbus.sendbuf[i++]=0x06;        //功能码 
   modbus.sendbuf[i++]=Regadd/256;//写入的地址
 	modbus.sendbuf[i++]=Regadd%256;
 	modbus.sendbuf[i++]=val/256;//写入的数值
 	modbus.sendbuf[i++]=val%256;
 	crc=Modbus_CRC16(modbus.sendbuf,i);//获取crc校验位
 	modbus.sendbuf[i++]=crc/256;  //crc校验位加入包中
 	modbus.sendbuf[i++]=crc%256;
 	//数据发送包打包完毕
 	RS485DIR_TX;;//使能485控制端(启动发送)  
 	for(j=0;j<i;j++)
 	{
 	 Modbus_Send_Byte(modbus.sendbuf[j]);
 	}
 	RS485DIR_RX;//失能485控制端（改为接收）
 }

  //这是往多个寄存器器中写入数据
 //功能码0x10指令即十进制16
 void Modbus_Func16()
 {
 		uint16_t Regadd;//地址16位
 		uint16_t Reglen;
 		uint16_t i,crc,j;
 		
 		Regadd=modbus.rcbuf[2]*256+modbus.rcbuf[3];  //要修改内容的起始地址
 		Reglen = modbus.rcbuf[4]*256+modbus.rcbuf[5];//读取的寄存器个数
 		for(i=0;i<Reglen;i++)//往寄存器中写入数据
 		{
 			//接收数组的第七位开始是数据
 			Reg[Regadd+i]=modbus.rcbuf[7+i*2]*256+modbus.rcbuf[8+i*2];//对寄存器一次写入数据
 		}
 		//写入数据完毕，接下来需要进行打包回复数据了
 		
 		//以下为回应主机内容
 		//内容=接收数组的前6位+两位的校验位
 		modbus.sendbuf[0]=modbus.rcbuf[0];//本设备地址
 		modbus.sendbuf[1]=modbus.rcbuf[1];  //功能码 
 		modbus.sendbuf[2]=modbus.rcbuf[2];//写入的地址
 		modbus.sendbuf[3]=modbus.rcbuf[3];
 		modbus.sendbuf[4]=modbus.rcbuf[4];
 		modbus.sendbuf[5]=modbus.rcbuf[5];
 		crc=Modbus_CRC16(modbus.sendbuf,6);//获取crc校验位
 		modbus.sendbuf[6]=crc/256;  //crc校验位加入包中
 		modbus.sendbuf[7]=crc%256;
 		//数据发送包打包完毕
 		
 		RS485DIR_TX;;//使能485控制端(启动发送)  
 		for(j=0;j<8;j++)
 		{
 			Modbus_Send_Byte(modbus.sendbuf[j]);
 		}
 		RS485DIR_RX;//失能485控制端（改为接收）
 }

  void Modbus_Send_Byte(  uint8_t ch )
 {
 	/* 发送一个字节数据到USART2 */
   HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xff);	
	 //while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//等待发送结束
 }
 
 int Modbus_CRC16(uint8_t buff[],int len)
{
    unsigned short tmp = 0xffff;
    unsigned short ret1 = 0;

    for(int n = 0; n < len; n++)  //此处的6 -- 要校验的位数为6个
     {
        tmp = buff[n] ^ tmp;
        for(int i = 0;i < 8;i++)  //此处的8 -- 指每一个char类型又8bit，每bit都要处理
        {
            if(tmp & 0x01)
             {
                tmp = tmp >> 1;
                tmp = tmp ^ 0xA001;
             }
            else
             {
                tmp = tmp >> 1;
             }
        }
    }

    ret1 = tmp >> 8;   //将CRC校验的高低位对换位置
    ret1 = ret1 | (tmp << 8);

    return ret1;
}
