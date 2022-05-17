#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H


/********************************** 头文件包含区 **********************************/
#include "stm32f10x.h"
#include "bsp_esp8266.h"
#include "core_delay.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "bsp_usart.h"
/************************************* END *****************************************/


/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                      "Redmi K40"        //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                       "h123456."         //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                "192.168.227.90"    //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port              "8080"              //要连接的服务器的端口


/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_CheckRecvDataTest(void);

#endif

