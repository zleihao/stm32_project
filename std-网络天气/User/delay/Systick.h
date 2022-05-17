#ifndef _SYSTICK_
#define _SYSTICK_

#include "stm32f10x.h"
#include "core_cm3.h"


void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);

#endif
