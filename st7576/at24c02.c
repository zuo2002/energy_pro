/*
  ******************************************************************************
  * File Name          : at24c02.c
  * Description        : this code is used for at24c02 application
  * Author             : JackWang
  * Date               : 2019-05-07
  ******************************************************************************
*/
 
/*! -------------------------------------------------------------------------- */
/*! Include headers */
#include "at24c02.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/*! -------------------------------------------------------------------------- */
/*! Private macros define */
#define AT24CXX_Write_ADDR 0xA0
#define AT24CXX_Read_ADDR  0xA1
#define AT24CXX_MAX_SIZE   256
#define AT24CXX_PAGE_SIZE  8
#define AT24CXX_PAGE_TOTAL (AT24CXX_MAX_SIZE/AT24CXX_PAGE_SIZE)


//00-03��һ����Ȧ��ֵ
//04-07��������Ȧ��ֵ
//08���������

//09���Ͳ�����
//10����Ƶ��

//11����ģʽ

//12�ɼ�Ƶ��
//13 485��ַ

//14-17��ѹ����ֵ
//18-21��ѹ����ֵ
//22-25������ֵ
//26-29������ֵ
//30-33������ֵ

//40-50����


/*! -------------------------------------------------------------------------- */
/*! Public functions list */
int AT24C02_write(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
int AT24C02_read (uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
void sysDelay_ms(uint16_t num);
/*! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void sysDelay_ms(uint16_t num)
{
	HAL_Delay(num);
}

int AT24C02_write(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize)
{
	HAL_GPIO_WritePin(ERR_LD_GPIO_Port,ERR_LD_Pin,1);
    if (0 == dataSize) { return -1; }
    
    int res = HAL_OK;
    
    int selectPage_idx  = addr % AT24CXX_PAGE_SIZE;
    int selectPage_rest = AT24CXX_PAGE_SIZE - selectPage_idx;
    
    if (dataSize <= selectPage_rest) {
        res = HAL_I2C_Mem_Write(&hi2c1, 
                                 AT24CXX_Write_ADDR, 
                                 addr,
                                 I2C_MEMADD_SIZE_8BIT, 
                                 dataPtr,
                                 dataSize,
                                 0xFF);
        
        if (HAL_OK != res) { return -1; }
        
        sysDelay_ms(10);
        
    } else {
    
        /*! 1 write selectPage rest*/
        res = HAL_I2C_Mem_Write(&hi2c1, 
                                 AT24CXX_Write_ADDR, 
                                 addr,
                                 I2C_MEMADD_SIZE_8BIT, 
                                 dataPtr,
                                 selectPage_rest,
                                 0xFF);
        
        if (HAL_OK != res) { return -1; }
        
        addr     += selectPage_rest;
        dataSize -= selectPage_rest;
        dataPtr  += selectPage_rest;
        
        sysDelay_ms(5);
        
        /*! 2 write nextPage full */
        int fullPage = dataSize/AT24CXX_PAGE_SIZE;
        for (int iPage = 0; iPage < fullPage; ++iPage) {
            res = HAL_I2C_Mem_Write(&hi2c1, 
                                     AT24CXX_Write_ADDR, 
                                     addr,
                                     I2C_MEMADD_SIZE_8BIT, 
                                     dataPtr,
                                     AT24CXX_PAGE_SIZE,
                                     0xFF);
            
            if (HAL_OK != res) { return -1; }
            
            sysDelay_ms(5);
            
            addr     += AT24CXX_PAGE_SIZE;
            dataSize -= AT24CXX_PAGE_SIZE;
            dataPtr  += AT24CXX_PAGE_SIZE;
        }
        
        /*! 3 write rest */
        if (0 != dataSize) {
            res = HAL_I2C_Mem_Write(&hi2c1, 
                                     AT24CXX_Write_ADDR, 
                                     addr,
                                     I2C_MEMADD_SIZE_8BIT, 
                                     dataPtr,
                                     dataSize,
                                     0xFF);
        
            if (HAL_OK != res) { return -1; }
            
            sysDelay_ms(5);
        }
    }
    HAL_GPIO_WritePin(ERR_LD_GPIO_Port,ERR_LD_Pin,0);
    return 0;
}
 
/*! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int AT24C02_read(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize)
{
    int res = HAL_I2C_Mem_Read(&hi2c1,
                                AT24CXX_Read_ADDR,
                                addr,
                                I2C_MEMADD_SIZE_8BIT,
                                dataPtr,
                                dataSize,
                                0xFF);
    
    if (HAL_OK != res) { return -1; }
    osDelay(50);
    return 0;
}

int HAL_AT24C02_read(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize)
{
    int res = HAL_I2C_Mem_Read(&hi2c1,
                                AT24CXX_Read_ADDR,
                                addr,
                                I2C_MEMADD_SIZE_8BIT,
                                dataPtr,
                                dataSize,
                                0xFF);
    
    if (HAL_OK != res) { return -1; }
    HAL_Delay(50);
    return 0;
}

#if (1 == AT24CXX_TEST_ENABLE)
/*! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static uint8_t AT24CXX_testBuff[AT24CXX_TEST_BUFF_SIZE];
 
int 
AT24C02_Test(void)
{    
    for (int idx = 0; idx < AT24CXX_TEST_BUFF_SIZE; ++idx) {
        AT24CXX_testBuff[idx] = idx;
    }
    
    AT24C02_write(AT24CXX_TEST_ADDR, AT24CXX_testBuff+AT24CXX_TEST_ADDR, AT24CXX_TEST_SIZE);
    
    memset(AT24CXX_testBuff, 0, AT24CXX_TEST_BUFF_SIZE);
    
    AT24C02_read(AT24CXX_TEST_ADDR, AT24CXX_testBuff, AT24CXX_TEST_SIZE);  
    
    int err = 0;
    
    for (int idx = 0; idx < AT24CXX_TEST_SIZE; ++idx) {
        if ((AT24CXX_TEST_ADDR+idx) != AT24CXX_testBuff[idx]) err++;
    }
    
    return err;
    
}
#endif