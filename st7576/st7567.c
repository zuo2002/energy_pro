#include "st7567.h"


void LDZ_SendBit(u8 bit)
{	
	u8 i;
	for(i = 0;i < 8;i ++)
	{
		LDZ_SCK_L();
		if(bit & 0x80)
		   LDZ_SDA_H();
		else
		   LDZ_SDA_L();
		LDZ_SCK_H();
		bit <<= 1;
	}
} 
 
/**************************************************************************
* �������ƣ� LDZ_WriteCMD/LDZ_WriteDAT
* ���������� д����/д����
**************************************************************************/
void LDZ_WriteCMD(u8 cmd)
{
    LDZ_CS_L();
    LDZ_DC_L();
    LDZ_SendBit(cmd);
    LDZ_CS_H();
}
    
void LDZ_WriteDAT(u8 dat)
{
    LDZ_CS_L();
    LDZ_DC_H();
    LDZ_SendBit(dat);
    LDZ_CS_H();
}

/**************************************************************************
* �������ƣ� LDZ_Cfg
* ���������� ������Ļ
**************************************************************************/
void LDZ_Cfg(void)
{
    LDZ_WriteCMD(0xE2); //reset
    Ddl_Delay1ms(10);
    LDZ_WriteCMD(0xA2); //����ƫѹ��Ϊ1/9
    LDZ_WriteCMD(0xA0); //����segɨ������seg0~seg131
    LDZ_WriteCMD(0xC8); //����comɨ�跴��com63~com0
    LDZ_WriteCMD(0x24); //�Աȶȴֵ�
    LDZ_WriteCMD(0x81); //�Աȶ�˫ָ��
    LDZ_WriteCMD(0x2B); //�Աȶ�΢��
    LDZ_WriteCMD(0x2F); //��Դ����
    LDZ_WriteCMD(0xB0); //����ҳ��ַ
    LDZ_WriteCMD(0xAF); //��ʾ��
    LDZ_WriteCMD(0xA6); //������ʾ����ת
}

/**************************************************************************
* �������ƣ� LDZ_SetAddr/LDZ_ClearPage/LDZ_Clear
* ���������� ���õ�ַ/����ҳ/��ȫ��
**************************************************************************/
void LDZ_SetAddr(u8 page, u8 col)
{
    LDZ_WriteCMD(0xB0|page);
    LDZ_WriteCMD((col >> 4)| 0x10);
    LDZ_WriteCMD(col & 0x0F);
}
 
void LDZ_ClearPage(u8 page)
{
    u8 i;
    LDZ_SetAddr(page, 0);
    for(i = 0;i < 128;i ++)
        LDZ_WriteDAT(0x00);
}
 
void LDZ_Clear(void)
{
    u8 i;
    for(i = 0;i < 8;i ++)
        LDZ_ClearPage(i);
}

/**************************************************************************
* �������ƣ� LDZ_ShowASC16/LDZ_ShowASC32/LDZ_ShowCHN16/LDZ_ShowCHN32
* ���������� ��ʾ�ַ�
* ����˵���� [1]ҳ��ַ / [2]�е�ַ / [3]�ַ�λ�ڶ�Ӧ�����е����
**************************************************************************/
void LDZ_ShowASC16(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 2;i ++)//һ��2��
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 8;j ++)  //һ��8�ֽ�
			LDZ_WriteDAT(ASC16[j + i*8 + id*16]);
	}
}
 
void LDZ_ShowCHN16(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 2;i ++)   //һ��2��
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 16;j ++)  //һ��16�ֽ�
			LDZ_WriteDAT(CHN16[j + i*16 + id*32]);
	}
}
 
void LDZ_ShowASC32(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 4;i ++)   //һ��4��
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 16;j ++)  //һ��16�ֽ�
			LDZ_WriteDAT(ASC32[j+ i*16 + id*64]);
	}
}
 
void LDZ_ShowCHN32(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 4;i ++)   //һ��4��
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 32;j ++)  //һ��32�ֽ�
			LDZ_WriteDAT(CHN32[j + i*32 + id*128]);
	}
}


/**************************************************************************
* �������ƣ� LDZ_Init
* ���������� LDZ��ʼ��
**************************************************************************/
void LDZ_Init(void)
{
    LDZ_CS_H();
    LDZ_SCK_H();
    LDZ_SDA_H();
    
    LDZ_RE_H(); Ddl_Delay1ms(10);
    LDZ_RE_L(); Ddl_Delay1ms(10);
    LDZ_RE_H(); Ddl_Delay1ms(50);
}

void Ddl_Delay1ms(uint32_t ms)
{
	HAL_Delay(ms);
	
}