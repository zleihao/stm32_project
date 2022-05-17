#ifndef _BSP_DEBUG_USART_H
#define _BSP_DEBUG_USART_H

#include"stm32f10x.h"
#include<stdio.h>


//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch); //定义为putchar应用




//串口1-USART1
#define	DEBUG_USART_APBxClkCmd RCC_APB2PeriphClockCmd
#define DEBUG_USART_CLK  RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE  115200
#define DEBUG_USARTx_IRn USART1_IRQn
#define DEBUG_USARTx USART1


//USART GPIO 引脚宏定义
#define	DEBUG_USART_GPIO_APBxClkCmd  RCC_APB2PeriphClockCmd
#define DEBUG_USART_GPIO_CLK  RCC_APB2Periph_GPIOA

#define DEBUG_USART_TX_GPIO_PIN  GPIO_Pin_9
#define DEBUG_USART_TX_GPIO_PORT  GPIOA

#define DEBUG_USART_RX_GPIO_PIN  GPIO_Pin_10
#define DEBUG_USART_RX_GPIO_PORT  GPIOA


void USART_Config();
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data);

void Usart_SendArra(USART_TypeDef* pUSARTx,uint16_t *arra,uint8_t num);
void Usart_SendStr(USART_TypeDef* pUSARTx,uint8_t *str);

#endif /* _BSP_DEBUG_USART_H */
