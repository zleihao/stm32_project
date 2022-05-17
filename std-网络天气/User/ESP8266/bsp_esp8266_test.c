#include "bsp_esp8266_test.h"
#include "bsp_esp8266.h"
#include "./dwt_delay/core_delay.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "bsp_key.h"
#include "bsp_usart.h"


volatile uint8_t ucTcpClosedFlag = 0;

typedef struct Date
{
	char text_day[10];    //天气
	uint8_t text_temp;   //温度
	char text_date[30];  //日期
}WEATHER_InitTypeDef;
	
//打印天气
void Display_Weather(void)
{
	WEATHER_InitTypeDef WEATHER_InitStruct;
	char *ss;
	//打印位置信息
	printf("\n位置：郑州\n");
	OLED_ShowChinese(0,0,1,16);  //位
	OLED_ShowChinese(17,0,2,16); //置
	OLED_ShowString(34,0,":",16);
	OLED_ShowChinese(41,0,3,16);  //郑
	OLED_ShowChinese(58,0,4,16); //州
	//解析天气
	ss = strstr(strEsp8266_Fram_Record .Data_RX_BUF,"text");
	ss = ss + 7;
	sscanf(ss,"%[^\"]",WEATHER_InitStruct.text_day);
	OLED_ShowChinese(0,16,7,16);  //天
	OLED_ShowChinese(17,16,8,16); //气
	OLED_ShowString(34,16,":",16);
	
	printf("天气：");
	if (strcmp(WEATHER_InitStruct.text_day,"Haze") == 0)
	{
		printf("霾\n");
		OLED_ShowChinese(41,16,9,16);  //霾
		OLED_ShowString(58,16,"   ",16);
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Overcast") == 0)
	{
		printf("阴天\n");
		OLED_ShowChinese(41,16,10,16);  //阴
		OLED_ShowChinese(58,16,11,16);  //天
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Light rain") == 0)
	{
		printf("小雨\n");
		OLED_ShowChinese(41,16,12,16);  //小
		OLED_ShowChinese(58,16,13,16);  //雨
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Cloudy") == 0)
	{
		printf("多云\n");
		OLED_ShowChinese(41,16,14,16);  //多
		OLED_ShowChinese(58,16,15,16);  //云
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Clear") == 0)
	{
		printf("晴\n");
		OLED_ShowChinese(41,16,16,16);  //晴
//		OLED_ShowString(58,20," ",16);
	}
	else 
	{
		printf("未知");
		OLED_ShowChinese(41,16,16,16);  //晴
	}
	//	//解析温度
	ss = strstr(strEsp8266_Fram_Record .Data_RX_BUF,"temperature");
	ss = ss + 14;
	sscanf(ss,"%2d",&WEATHER_InitStruct.text_temp);
	printf("温度：%d°\n",WEATHER_InitStruct.text_temp);


	OLED_ShowChinese(0,32,5,16);  //温
	OLED_ShowChinese(17,32,6,16); //度
	OLED_ShowString(34,32,":",16);
	
	OLED_ShowNum(43,32,WEATHER_InitStruct.text_temp,2,16);
	OLED_ShowChinese(60,32,0,16);

	//解析日期
	ss = strstr(strEsp8266_Fram_Record .Data_RX_BUF,"last_update");
	ss = ss + 14;
	sscanf(ss,"%[^T]",WEATHER_InitStruct.text_date);
	printf("日期:");
	printf("%s\n",WEATHER_InitStruct.text_date);
	OLED_ShowChinese(0,48,17,16);  //日
	OLED_ShowChinese(17,48,18,16); //期
	OLED_ShowString(34,48,":",16);
	OLED_ShowString(40,48,WEATHER_InitStruct.text_date,16);
	
}

/********************************************连接服务器*************************************************************************/

/**
  * @brief  ESP8266 StaTcpClient Unvarnish 配置测试函数
  * @param  无
  * @retval 无
  */
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
  printf( "\r\n正在配置 ESP8266 ......\r\n" );
  printf( "\r\n使能 ESP8266 ......\r\n" );
	
	OLED_ShowString(0,0,"Enable ESP8266",16);
	OLED_Refresh();
	
	macESP8266_CH_ENABLE();
	OLED_ShowString(0,0,"AT Test ......",16);
	OLED_Refresh();
	while( ! ESP8266_AT_Test() );
  OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n正在配置工作模式 STA ......\r\n" );

	OLED_ShowString(0,0,"Set STA_Mode .",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
	while( ! ESP8266_Net_Mode_Choose ( STA ) );
  OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n正在连接 WiFi ......\r\n" );
	OLED_ShowString(0,0,"Link WIFI ....",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
  while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n禁止多连接 ......\r\n" );
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
	
  printf( "\r\n正在连接心知天气 ......\r\n" );
	OLED_ShowString(0,0,"Link Server ...",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
	while( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n进入透传发送模式 ......\r\n" );
	OLED_ShowString(0,0,"Send mode ...",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
	while( ! ESP8266_UnvarnishSend () );
	OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
	printf( "\r\n配置 ESP8266 完毕\r\n" );
	printf ( "\r\n开始透传......\r\n" );
	OLED_ShowString(0,0,"Finish         ",16);
	OLED_ShowString(0,17,"Press down K1 ",16);
	OLED_Refresh();
}

/*************************************************************************************************************************/

/**
  * @brief  ESP8266 检查是否接收到了数据，检查连接和掉线重连
  * @param  无
  * @retval 无
  */
void ESP8266_CheckRecvDataTest(void)
{
  uint8_t ucStatus;
	

  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      printf ( "\r\n正在重连热点和服务器 ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n重连热点和服务器成功\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}



