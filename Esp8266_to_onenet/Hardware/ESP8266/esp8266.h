#ifndef _ESP8266_H_
#define _ESP8266_H_


#define      User_ESP8266_ApSsid                      "Redmi K40"        //要连接的热点的名称
#define      User_ESP8266_ApPwd                       "h123456."         //要连接的热点的密钥

#define      User_ESP8266_TcpServer_IP                "183.230.40.39"    //要连接的服务器的 IP
#define      User_ESP8266_TcpServer_Port              "6002"              //要连接的服务器的端口


/******************************** ESP8266 连接引脚定义 ***********************************/
//EN
#define      ESP8266_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      ESP8266_CH_PD_CLK                             RCC_APB2Periph_GPIOA  
#define      ESP8266_CH_PD_PORT                            GPIOA
#define      ESP8266_CH_PD_PIN                             GPIO_Pin_5
//RST
#define      ESP8266_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      ESP8266_RST_CLK                               RCC_APB2Periph_GPIOA
#define      ESP8266_RST_PORT                              GPIOA
#define      ESP8266_RST_PIN                               GPIO_Pin_4

/**********************************stm32控制esp8266*************************************************/
//RX --> PA2  TX --> PA3 
#define       ESP8266_USART_BAUD_RATE                       115200

#define       ESP8266_USARTx                                USART2
#define       ESP8266_USART_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define       ESP8266_USART_CLK                             RCC_APB1Periph_USART2
#define       ESP8266_USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define       ESP8266_USART_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define       ESP8266_USART_TX_PORT                         GPIOA   
#define       ESP8266_USART_TX_PIN                          GPIO_Pin_2
#define       ESP8266_USART_RX_PORT                         GPIOA
#define       ESP8266_USART_RX_PIN                          GPIO_Pin_3
#define       ESP8266_USART_IRQ                             USART2_IRQn
#define       ESP8266_USART_INT_FUN                         USART2_IRQHandler
/************************************************************************************************/


#define      ESP8266_CH_ENABLE()                 GPIO_SetBits (  ESP8266_CH_PD_PORT,  ESP8266_CH_PD_PIN )
#define      ESP8266_CH_DISABLE()                GPIO_ResetBits (  ESP8266_CH_PD_PORT,  ESP8266_CH_PD_PIN )

#define      ESP8266_RST_HIGH_LEVEL()            GPIO_SetBits ( ESP8266_RST_PORT, ESP8266_RST_PIN )
#define      ESP8266_RST_LOW_LEVEL()             GPIO_ResetBits ( ESP8266_RST_PORT, ESP8266_RST_PIN )

#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志


void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

void esp8266_to_server(void);


#endif
