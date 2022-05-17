#include "bsp_debug_usart.h"



void NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel = DEBUG_USARTx_IRn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}


void USART_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	//打开GPIO时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK,ENABLE);
	
	//打开串口时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK,ENABLE);

	//配置USRT_TX的GPIO结构体
	GPIO_InitStruct.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitStruct);
	//配置USART——RX的GPIO结构体
	GPIO_InitStruct.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitStruct);

	//初始化串口 USART_InitTypeDef
	USART_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
       USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(DEBUG_USARTx,&USART_InitStruct);

	//配置NVIC
//	NVIC_Config();
  //  USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);
	USART_Cmd(DEBUG_USARTx,ENABLE);
}

/* 发送一个字节 */
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
}

//发送数组
void Usart_SendArra(USART_TypeDef* pUSARTx,uint16_t *arra,uint8_t num)
{
	uint16_t i;
	for(i=0;i<num;i++)
	{
		Usart_SendByte(pUSARTx,*arra++);
	}
	//检测一帧是否发送完毕
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) == RESET);
}

//发送字符串
void Usart_SendStr(USART_TypeDef* pUSARTx,uint8_t *str)
{
	while(*str != '\0')
	{
		Usart_SendByte(pUSARTx,*str++);
	}
	while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TC) == RESET);
}



int _write (int fd, char *pBuffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成
        USART1->DR = (uint8_t) pBuffer[i];       //写DR,串口1将发送数据
    }
    return size;
}

// /**
//  * @brief  usart_init
//  * @param  flck 时钟频率
//  * 		   usart1频率为72M，其余串口为36M
//  * @return 无
//  * @note   初始化usart
//  */
// void usart_init(uint8_t flck) {
// 	float temp;
// 	uint16_t mantissa;  //波特率整数
// 	uint16_t fraction;  //波特率小数

// 	temp = (float)(flck*1000000)/(115200*16);  //得到 USARTDIV
// 	mantissa = temp;                           //得到整数部分
// 	fraction = (temp - mantissa)*16;           //得到小数部分
// 	mantissa <<= 4;
// 	mantissa += fraction;                      //写入到BRR的最终值

// 	//打开串口时钟
// 	RCC->APB2ENR |= (1 << 14);
// 	//打开GPIOA时钟
// 	RCC->APB2ENR |= (1 << 2);
	
// 	//配置TX、RX引脚
// 	GPIOA->CRH &= 0xFFFFF00F;  //清空 PIN10 PIN9
// 	// TX：复用推挽输出 RX：输入模式
// 	GPIOA->CRH |= 0x000008B0;  

// 	//复位串口
// 	RCC->APB2RSTR |= (1 << 14);
// 	//停止复位
// 	RCC->APB2RSTR &= ~(1 << 14);
// 	//usart工作模式
// 	USART1->BRR = mantissa; //波特率
// 	USART1->CR1 |= 0x200C;  //使能usart1、无校验位
// 	USART1->CR2 &= ~(3 << 12); //1个停止位
// }

// //重定向c库函数printf到串口，重定向后可使用printf函数
// int _write (int fd, char *pBuffer, int size)
// {
//     for (int i = 0; i < size; i++)
//     {
//         while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成
//         USART1->DR = (uint8_t) pBuffer[i];       //写DR,串口1将发送数据
//     }
//     return size;
// }
