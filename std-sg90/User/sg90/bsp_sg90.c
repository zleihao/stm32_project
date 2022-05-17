#include "bsp_sg90.h"

//GPIO初始化
static void SG90_GPIO_MODE_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	
	SG90_GPIO_CLOCK_FUN(SG90_GPIO_CLOCK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = SG90_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(SG90_GPIO_PORT,&GPIO_InitStruct);
}

//PWM初始化
static void SG90_PWM_MODE_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;  //定义时基单元结构体变量
	TIM_OCInitTypeDef  TIM_OCInitStruct;             //输出比较
	
	TIMx_CLOCK_FUN(TIMx_CLOCK,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = (200 - 1);   
	TIM_TimeBaseInitStruct.TIM_Prescaler = (7200 - 1);
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCxInit(TIMx,&TIM_OCInitStruct);
	TIM_Cmd(TIMx,ENABLE);
	TIM_OCxPreloadConfig(TIMx,TIM_OCPreload_Enable);

}

void SG90_Init(void)
{
	SG90_GPIO_MODE_Config();
	SG90_PWM_MODE_Config();
}
