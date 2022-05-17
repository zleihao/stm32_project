#include "Systick.h"

void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	
	SysTick_Config(72);//72 1us

	for(i=0;i<us;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));		
		
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i;
	
	SysTick_Config(72000);//72000 1ms

	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));		
		
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
