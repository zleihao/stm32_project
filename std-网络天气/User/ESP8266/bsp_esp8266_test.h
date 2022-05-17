#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f10x.h"



/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "Redmi K40"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "h123456."                 //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "api.seniverse.com"      //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "80"               //Ҫ���ӵķ������Ķ˿�

//����֪������ȡ��Ϣ
#define      TEMP_DATA                                    "GET  https://api.seniverse.com/v3/weather/now.json?key=S-5Y6pZcsXEXjZF_1&location=zhengzhou&language=en&unit=c\r\n"

/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;

/********************************** ���Ժ������� ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_CheckRecvDataTest(void);

#endif

