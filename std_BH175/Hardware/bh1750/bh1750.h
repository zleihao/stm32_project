#ifndef _BH1750_H
#define _BH1750_H

#include "bsp_iic.h"
#include "bsp_SysTick.h"

//ADDR 引脚接线是否接地
#define ADDR_TO_GND 

#ifdef ADDR_TO_GND
    #define BH_DEVICE_ADDR 0x46   //ADDR引脚接地
#else
    #define BH_DEVICE_ADDR 0xB8   //ADDR引脚接VCC
#endif

//Rom指令
#define POWER_ON           0x01
#define H_RESOLUTION_MODE  0x10

uint8_t bh_CheckOk();
float   read_result(void);
void    bh1570_Init(void);

#endif