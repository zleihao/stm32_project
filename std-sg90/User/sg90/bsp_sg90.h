#ifndef _BSP_SG90_H
#define _BSP_SG90_H

#include "stm32f10x.h"

//TIM2
#define TIMx   							TIM3
#define TIMx_CLOCK_FUN   		RCC_APB1PeriphClockCmd
#define TIMx_CLOCK       		RCC_APB1Periph_TIM3

//TIM2_GPIO
#define SG90_GPIO_CLOCK_FUN   	RCC_APB2PeriphClockCmd
#define SG90_GPIO_CLOCK  				RCC_APB2Periph_GPIOA
#define SG90_GPIO_PORT          GPIOA
#define SG90_GPIO_PIN           GPIO_Pin_6

#define TIM_SetComparex         TIM_SetCompare1
#define TIM_OCxInit             TIM_OC1Init
#define TIM_OCxPreloadConfig    TIM_OC1PreloadConfig

void SG90_Init(void);

#endif
