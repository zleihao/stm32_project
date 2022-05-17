#include "bsp_esp8266_test.h"

volatile uint8_t ucTcpClosedFlag = 0;

/******************************************************************
*    !!!!! 注意：ESP8266 接收到的数据存储在数组 strEsp8266_Fram_Record .Data_RX_BUF 中，
*               需要解析数据，并做出对应的操作
******************************************************************/


/********************************************连接服务器*************************************************************************/

/**
  * @brief  ESP8266 StaTcpClient Unvarnish 配置测试函数
  * @param  无
  * @retval 无
  */
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
  //正在配置 ESP8266
  printf( "\r\nConfiguring ESP8266 ......\r\n" );
  //使能ESP8266
  printf( "\r\nENABLE ESP8266 ......\r\n" );
	macESP8266_CH_ENABLE();
	while( ! ESP8266_AT_Test() );

  //正在配置工作模式
  printf( "\r\nConfiguring work mode: STA ......\r\n" );
	while( ! ESP8266_Net_Mode_Choose ( STA ) );
  
  //正在连接
  printf( "\r\nConnecting WiFi ......\r\n" );
  while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
  //禁止多连接
  printf( "\r\nDisable multiple connections ......\r\n" );
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
	
  //正在连接服务器
  printf( "\r\nConnecting to server ......\r\n" );
	while( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
  //进入透传发送模式
  printf( "\r\nEnter transparent transmission mode ......\r\n" );
	while( ! ESP8266_UnvarnishSend () );
	
  //配置 ESP8266 完毕
	printf( "\r\nConfiguration of ESP8266 is complete\r\n" );
  
  //开始透传
	printf ( "\r\nstart passthrough......\r\n" );
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

  if( strEsp8266_Fram_Record .InfBit .FramFinishFlag )   //接收到数据
  {
      USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, DISABLE ); //禁用串口接收中断
      strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
      
      //使用USART1将esp8266接收到的数据通过串口调试助手打印出来
      printf("%s\n",strEsp8266_Fram_Record.Data_RX_BUF);

      //解析数据后，执行的操作函数在这里调用

      strEsp8266_Fram_Record .InfBit .FramLength = 0;                             //接收数据长度置零
      strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;                           //接收标志置零
      USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, ENABLE ); //使能串口接收中断
  }

  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      //正在重连热点和服务器
      printf ( "\r\nReconnecting to hotspot and server ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      //重连热点和服务器成功
      printf ( "\r\nReconnect to hotspot and server successfully\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}



