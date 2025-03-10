#include "modbus.h"
#include "usart.h"
MODBUS modbus;

extern float UA_val;//��ѹʵ��ֵ
extern float UB_val;
extern float UC_val;

extern float IA_val;//����ʵ��ֵ
extern float IB_val;
extern float IC_val;

extern float PA_val;//���й�����ʵ��ֵ
extern float PB_val;
extern float PC_val;
extern float FEQT_val;

extern float Deplete_A_val;//����
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
           0};//reg����ǰ����õļĴ����ͼĴ������ݣ�Ҫ��ȡ�͸�д�Ĳ�������
 // Modbus��ʼ������
					 
					 
 void Modbus_Init(void)
 {
   modbus.myadd = 0x01; //�ӻ��豸��ַΪ2
   modbus.timrun = 0;    //modbus��ʱ��ֹͣ����
	 modbus.slave_add=0x02;//����Ҫƥ��Ĵӻ���ַ�����豸��Ϊ����ʱ��
	 modbus.reflag = 0;//�����ݰ�����
	 modbus.Host_time_flag = 0;//�������ݱ�־
	 modbus.recount = 0;//���յ����ֽ���
	 modbus.timout = 0;//��ʱʱ�� ��λ��ms
	 modbus.Host_Sendtime = 0;//��������һ֡���ʱ����� ��λ��ms
 }
					 
 // Modbus�¼�������
 void Modbus_Event(void)
 {
 	uint16_t crc,rccrc;//crc�ͽ��յ���crc
 	//û���յ����ݰ�

   if(modbus.reflag == 0)  //�������δ����򷵻ؿ�
 	{
 	   return;
 	}
 	//�յ����ݰ�(�������)
 	//ͨ������������֡����CRC
 	//����1�������׵�ַ������2��Ҫ����ĳ��ȣ�����CRCУ��λ����ȫ�㣩
 	crc = Modbus_CRC16(&modbus.rcbuf[0],modbus.recount-2); //��ȡCRCУ��λ
 	// ��ȡ����֡��CRC
 	rccrc = modbus.rcbuf[modbus.recount-2]*256+modbus.rcbuf[modbus.recount-1];//�����ȡ��CRCУ��λ
 	//�ȼ��������������
 	//rccrc=modbus.rcbuf[modbus.recount-1]|(((uint16_t)modbus.rcbuf[modbus.recount-2])<<8);//��ȡ���յ���CRC
 	if(crc == rccrc) //CRC����ɹ� ��ʼ������
 	{	
 	   if(modbus.rcbuf[0] == modbus.myadd)  // ����ַ�Ƿ�ʱ�Լ��ĵ�ַ
 		 {
 		   switch(modbus.rcbuf[1])   //����modbus������
 			 {
 			   case 0:             break;
 				 case 1:             break;
 				 case 2:             break;
 				 case 3:       Modbus_Func3();break;//���Ƕ�ȡ�Ĵ���������
 				 case 4:             break;
 				 case 5:             break;
          case 6:      Modbus_Func6();      break;//����д�뵥���Ĵ�������
 				 case 7:             break;
 				 case 8:             break;
 				 case 9:             break;
 				 case 16:     Modbus_Func16(); 			break;//д�����Ĵ�������
 			 }
 		 }
 		 else if(modbus.rcbuf[0] == 0) //�㲥��ַ�����Ӧ
 		 {
 		    
 		 }	 
 	}	
 	 modbus.recount = 0;//���ռ�������
   modbus.reflag = 0; //���ձ�־����
 }

 /*
 ********************************************************************************
 ������03
 01  03      00 01     00 01          D5 CA	�ӵ�ַ01��ʼ����ȡһ���Ĵ�������������
 ID ������  ��ʼ��ַ  ��ȡ�Ĵ����ĸ���
 �ӻ����أ�
 01  03       02       00 03          F8 45 �����������ֽڵ����ݣ�������00 03
 ID  ������  �����ֽ�  ���ص���������
 
 ********************************************************************************
 */
 // Modbus 3�Ź����뺯��
 // Modbus ������ȡ�Ĵ���ֵ
 void Modbus_Func3(void)
 {
   uint16_t Regadd,Reglen,crc;
 	uint8_t i,j;	
 	//�õ�Ҫ��ȡ�Ĵ������׵�ַ
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

	 
 	Regadd = modbus.rcbuf[2]*256+modbus.rcbuf[3];//��ȡ���׵�ַ
 	//�õ�Ҫ��ȡ�Ĵ��������ݳ���
 	Reglen = modbus.rcbuf[4]*256+modbus.rcbuf[5];//��ȡ�ļĴ�������
 	//���ͻ�Ӧ���ݰ�
 	i = 0;
 	modbus.sendbuf[i++] = modbus.myadd;      //ID�ţ����ͱ����豸��ַ
 	modbus.sendbuf[i++] = 0x03;              //���͹�����
   modbus.sendbuf[i++] = ((Reglen*2)%256);   //�����ֽڸ���
 	for(j=0;j<Reglen;j++)                    //��������
 	{
 		//reg����ǰ����õ�16λ���飨ģ�¼Ĵ�����
 	  modbus.sendbuf[i++] = Reg[Regadd+j]/256;//��λ����
 		modbus.sendbuf[i++] = Reg[Regadd+j]%256;//��λ����
 	}
 	crc = Modbus_CRC16(modbus.sendbuf,i);    //����Ҫ�������ݵ�CRC
 	modbus.sendbuf[i++] = crc/256;//У��λ��λ
 	modbus.sendbuf[i++] = crc%256;//У��λ��λ
 	//���ݰ�������
 	// ��ʼ����Modbus����
 	
 	RS485DIR_TX;//���ǿ���485����
 	
 	for(j=0;j<i;j++)//��������
 	{
 	  Modbus_Send_Byte(modbus.sendbuf[j]);	
 	}
 	RS485DIR_RX;//�����ǹر�485����
 }


 
  // Modbus 6�Ź����뺯��
 // Modbus ����д��Ĵ���ֵ
 void Modbus_Func6()  
 {
   uint16_t Regadd;//��ַ16λ
 	uint16_t val;//ֵ
 	uint16_t i,crc,j;
 	i=0;
   Regadd=modbus.rcbuf[2]*256+modbus.rcbuf[3];  //�õ�Ҫ�޸ĵĵ�ַ 
 	val=modbus.rcbuf[4]*256+modbus.rcbuf[5];     //�޸ĺ��ֵ��Ҫд������ݣ�
 	Reg[Regadd]=val;  //�޸ı��豸��Ӧ�ļĴ���
 	
 	//����Ϊ��Ӧ����
 	modbus.sendbuf[i++]=modbus.myadd;//���豸��ַ
   modbus.sendbuf[i++]=0x06;        //������ 
   modbus.sendbuf[i++]=Regadd/256;//д��ĵ�ַ
 	modbus.sendbuf[i++]=Regadd%256;
 	modbus.sendbuf[i++]=val/256;//д�����ֵ
 	modbus.sendbuf[i++]=val%256;
 	crc=Modbus_CRC16(modbus.sendbuf,i);//��ȡcrcУ��λ
 	modbus.sendbuf[i++]=crc/256;  //crcУ��λ�������
 	modbus.sendbuf[i++]=crc%256;
 	//���ݷ��Ͱ�������
 	RS485DIR_TX;;//ʹ��485���ƶ�(��������)  
 	for(j=0;j<i;j++)
 	{
 	 Modbus_Send_Byte(modbus.sendbuf[j]);
 	}
 	RS485DIR_RX;//ʧ��485���ƶˣ���Ϊ���գ�
 }

  //����������Ĵ�������д������
 //������0x10ָ�ʮ����16
 void Modbus_Func16()
 {
 		uint16_t Regadd;//��ַ16λ
 		uint16_t Reglen;
 		uint16_t i,crc,j;
 		
 		Regadd=modbus.rcbuf[2]*256+modbus.rcbuf[3];  //Ҫ�޸����ݵ���ʼ��ַ
 		Reglen = modbus.rcbuf[4]*256+modbus.rcbuf[5];//��ȡ�ļĴ�������
 		for(i=0;i<Reglen;i++)//���Ĵ�����д������
 		{
 			//��������ĵ���λ��ʼ������
 			Reg[Regadd+i]=modbus.rcbuf[7+i*2]*256+modbus.rcbuf[8+i*2];//�ԼĴ���һ��д������
 		}
 		//д��������ϣ���������Ҫ���д���ظ�������
 		
 		//����Ϊ��Ӧ��������
 		//����=���������ǰ6λ+��λ��У��λ
 		modbus.sendbuf[0]=modbus.rcbuf[0];//���豸��ַ
 		modbus.sendbuf[1]=modbus.rcbuf[1];  //������ 
 		modbus.sendbuf[2]=modbus.rcbuf[2];//д��ĵ�ַ
 		modbus.sendbuf[3]=modbus.rcbuf[3];
 		modbus.sendbuf[4]=modbus.rcbuf[4];
 		modbus.sendbuf[5]=modbus.rcbuf[5];
 		crc=Modbus_CRC16(modbus.sendbuf,6);//��ȡcrcУ��λ
 		modbus.sendbuf[6]=crc/256;  //crcУ��λ�������
 		modbus.sendbuf[7]=crc%256;
 		//���ݷ��Ͱ�������
 		
 		RS485DIR_TX;;//ʹ��485���ƶ�(��������)  
 		for(j=0;j<8;j++)
 		{
 			Modbus_Send_Byte(modbus.sendbuf[j]);
 		}
 		RS485DIR_RX;//ʧ��485���ƶˣ���Ϊ���գ�
 }

  void Modbus_Send_Byte(  uint8_t ch )
 {
 	/* ����һ���ֽ����ݵ�USART2 */
   HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xff);	
	 //while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
 }
 
 int Modbus_CRC16(uint8_t buff[],int len)
{
    unsigned short tmp = 0xffff;
    unsigned short ret1 = 0;

    for(int n = 0; n < len; n++)  //�˴���6 -- ҪУ���λ��Ϊ6��
     {
        tmp = buff[n] ^ tmp;
        for(int i = 0;i < 8;i++)  //�˴���8 -- ָÿһ��char������8bit��ÿbit��Ҫ����
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

    ret1 = tmp >> 8;   //��CRCУ��ĸߵ�λ�Ի�λ��
    ret1 = ret1 | (tmp << 8);

    return ret1;
}
