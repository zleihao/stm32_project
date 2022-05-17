#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f10x.h"



/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "Redmi K40"                //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "h123456."                 //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                 "api.seniverse.com"      //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port               "80"               //要连接的服务器的端口

//从心知天气获取信息
#define      TEMP_DATA                                    "GET  https://api.seniverse.com/v3/weather/now.json?key=S-5Y6pZcsXEXjZF_1&location=zhengzhou&language=en&unit=c\r\n"

/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;

/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_CheckRecvDataTest(void);

#endif

