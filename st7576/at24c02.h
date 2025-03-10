/*
  ******************************************************************************
  * File Name          : at24c02.h
  * Description        : this code is used for at24c02 application
  * Author             : JackWang
  * Date               : 2019-05-07
  ******************************************************************************
*/
 
#ifndef __AT24C02_H
#define __AT24C02_H

#ifdef __cplusplus
 extern "C" {
#endif
 
/*! -------------------------------------------------------------------------- */
/*! Include headers */
#include <stdint.h>

#define AT24CXX_TEST_ENABLE     0
 
/*! -------------------------------------------------------------------------- */
/*! Public functions prototype */

int AT24C02_write(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
int AT24C02_read (uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
int HAL_AT24C02_read(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
void sysDelay_ms(uint16_t num);

#if (1 == AT24CXX_TEST_ENABLE)
/*! -------------------------------------------------------------------------- */
/*! Public test functions prototype */
#define AT24CXX_TEST_ADDR       39
#define AT24CXX_TEST_BUFF_SIZE  255
#define AT24CXX_TEST_SIZE       90
 
int AT24C02_Test(void);
#endif
 
#ifdef __cplusplus
}
#endif
 
#endif
/*! end of the file */