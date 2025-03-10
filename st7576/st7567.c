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
* 函数名称： LDZ_WriteCMD/LDZ_WriteDAT
* 功能描述： 写命令/写数据
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
* 函数名称： LDZ_Cfg
* 功能描述： 配置屏幕
**************************************************************************/
void LDZ_Cfg(void)
{
    LDZ_WriteCMD(0xE2); //reset
    Ddl_Delay1ms(10);
    LDZ_WriteCMD(0xA2); //设置偏压比为1/9
    LDZ_WriteCMD(0xA0); //设置seg扫描正向seg0~seg131
    LDZ_WriteCMD(0xC8); //设置com扫描反向com63~com0
    LDZ_WriteCMD(0x24); //对比度粗调
    LDZ_WriteCMD(0x81); //对比度双指令
    LDZ_WriteCMD(0x2B); //对比度微调
    LDZ_WriteCMD(0x2F); //电源控制
    LDZ_WriteCMD(0xB0); //设置页地址
    LDZ_WriteCMD(0xAF); //显示打开
    LDZ_WriteCMD(0xA6); //正常显示不反转
}

/**************************************************************************
* 函数名称： LDZ_SetAddr/LDZ_ClearPage/LDZ_Clear
* 功能描述： 设置地址/清整页/清全屏
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
* 函数名称： LDZ_ShowASC16/LDZ_ShowASC32/LDZ_ShowCHN16/LDZ_ShowCHN32
* 功能描述： 显示字符
* 参数说明： [1]页地址 / [2]列地址 / [3]字符位于对应数组中的序号
**************************************************************************/
void LDZ_ShowASC16(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 2;i ++)//一共2行
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 8;j ++)  //一行8字节
			LDZ_WriteDAT(ASC16[j + i*8 + id*16]);
	}
}
 
void LDZ_ShowCHN16(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 2;i ++)   //一共2行
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 16;j ++)  //一行16字节
			LDZ_WriteDAT(CHN16[j + i*16 + id*32]);
	}
}
 
void LDZ_ShowASC32(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 4;i ++)   //一共4行
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 16;j ++)  //一行16字节
			LDZ_WriteDAT(ASC32[j+ i*16 + id*64]);
	}
}
 
void LDZ_ShowCHN32(u8 page, u8 col, u8 id)
{
    u8 i,j;
    for(i = 0;i < 4;i ++)   //一共4行
	{
        LDZ_SetAddr(page++, col);
		for(j = 0;j < 32;j ++)  //一行32字节
			LDZ_WriteDAT(CHN32[j + i*32 + id*128]);
	}
}


/**************************************************************************
* 函数名称： LDZ_Init
* 功能描述： LDZ初始化
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