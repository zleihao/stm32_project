#ifndef _BSP_KEY_H
#define _BSP_KEY_H

/*KEY1Òý½ÅÎªPB9*/

#include"stm32f10x.h"

#define KEY_ON 	0
#define KEY_OFF 1

#define KEY1_GPIO_PIN GPIO_Pin_9
#define KEY1_GPIO_PORT GPIOB

void KEY_GPIO_Config();
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif

