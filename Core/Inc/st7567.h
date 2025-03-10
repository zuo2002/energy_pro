#ifndef __ST7567_H
#define __ST7567_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define u8              uint8_t
#define u16             uint16_t

//12864点阵屏引脚定义
//#define LDZ_CS_PORT     (GPIOC)
//#define LDZ_CS_PIN      (GPIO_Pin_5)
//#define LDZ_RE_PORT     (GPIOB)
//#define LDZ_RE_PIN      (GPIO_Pin_0)
//#define LDZ_DC_PORT     (GPIOB)
//#define LDZ_DC_PIN      (GPIO_Pin_1)
//#define LDZ_SCK_PORT    (GPIOB)
//#define LDZ_SCK_PIN     (GPIO_Pin_2)
//#define LDZ_SDA_PORT    (GPIOC)
//#define LDZ_SDA_PIN     (GPIO_Pin_7)


 
#define LDZ_CS_L()      HAL_GPIO_WritePin(LDZ_CS_GPIO_Port, LDZ_CS_Pin,0)
#define LDZ_CS_H()      HAL_GPIO_WritePin(LDZ_CS_GPIO_Port, LDZ_CS_Pin,1)
#define LDZ_RE_L()      HAL_GPIO_WritePin(LDZ_RE_GPIO_Port, LDZ_RE_Pin,0)
#define LDZ_RE_H()      HAL_GPIO_WritePin(LDZ_RE_GPIO_Port, LDZ_RE_Pin,1)
#define LDZ_DC_L()      HAL_GPIO_WritePin(LDZ_DC_GPIO_Port, LDZ_DC_Pin,0)
#define LDZ_DC_H()      HAL_GPIO_WritePin(LDZ_DC_GPIO_Port, LDZ_DC_Pin,1)
#define LDZ_SCK_L()     HAL_GPIO_WritePin(LDZ_SCK_GPIO_Port, LDZ_SCK_Pin,0)
#define LDZ_SCK_H()     HAL_GPIO_WritePin(LDZ_SCK_GPIO_Port, LDZ_SCK_Pin,1)
#define LDZ_SDA_L()     HAL_GPIO_WritePin(LDZ_SDA_GPIO_Port, LDZ_SDA_Pin,0)
#define LDZ_SDA_H()     HAL_GPIO_WritePin(LDZ_SDA_GPIO_Port, LDZ_SDA_Pin,1)
 
void LDZ_SendBit(u8 bit);
void LDZ_WriteCMD(u8 cmd);
void LDZ_WriteDAT(u8 dat);
void LDZ_Cfg(void);
void LDZ_SetAddr(u8 page, u8 col);
void LDZ_ClearPage(u8 page);
void LDZ_Clear(void);
void LDZ_ShowASC8(u8 page, u8 col, u8 id);
void LDZ_ShowENG16(u8 page, u8 col, u8 id);
void LDZ_ShowASC16(u8 page, u8 col, u8 id);
void LDZ_ShowCHN16(u8 page, u8 col, u8 id);
void LDZ_ShowASC32(u8 page, u8 col, u8 id);
void LDZ_ShowCHN32(u8 page, u8 col, u8 id);
void LDZ_Init(void);
void Ddl_Delay1ms(uint32_t ms);
uint8_t Take_smallernumber(float num);
void LDZ_Clean(u8 page, u8 col, u8 id);
void LDZ_ShowBMP(u8 page, u8 col, u8 id);
void LDZ_ShowPictureAnimation(u8 page_start, u8 page_end, u8 col_start, u8 col_end, const uint8_t *picture_data);

void LDZ_ShowPicture(u8 page_start, u8 page_end, u8 col_start, u8 col_end, const uint8_t *picture_data);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
