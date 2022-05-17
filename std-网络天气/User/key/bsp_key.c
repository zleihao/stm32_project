#include "bsp_key.h"   


void KEY_GPIO_Config()
{
	//任何时候都需要配置CRL
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//初始化CRL
	GPIO_InitTypeDef GPIO_InitStruct;
	//配置引脚
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
	//配置模式为浮空输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//因为按键为输入则不需要配置速率
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
}

uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON )
	{
		// 松手检测
		while( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON );
		return KEY_ON;
	}
	else return KEY_OFF;
}
