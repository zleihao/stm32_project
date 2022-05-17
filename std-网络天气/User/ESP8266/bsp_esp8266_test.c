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
	char text_day[10];    //����
	uint8_t text_temp;   //�¶�
	char text_date[30];  //����
}WEATHER_InitTypeDef;
	
//��ӡ����
void Display_Weather(void)
{
	WEATHER_InitTypeDef WEATHER_InitStruct;
	char *ss;
	//��ӡλ����Ϣ
	printf("\nλ�ã�֣��\n");
	OLED_ShowChinese(0,0,1,16);  //λ
	OLED_ShowChinese(17,0,2,16); //��
	OLED_ShowString(34,0,":",16);
	OLED_ShowChinese(41,0,3,16);  //֣
	OLED_ShowChinese(58,0,4,16); //��
	//��������
	ss = strstr(strEsp8266_Fram_Record .Data_RX_BUF,"text");
	ss = ss + 7;
	sscanf(ss,"%[^\"]",WEATHER_InitStruct.text_day);
	OLED_ShowChinese(0,16,7,16);  //��
	OLED_ShowChinese(17,16,8,16); //��
	OLED_ShowString(34,16,":",16);
	
	printf("������");
	if (strcmp(WEATHER_InitStruct.text_day,"Haze") == 0)
	{
		printf("��\n");
		OLED_ShowChinese(41,16,9,16);  //��
		OLED_ShowString(58,16,"   ",16);
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Overcast") == 0)
	{
		printf("����\n");
		OLED_ShowChinese(41,16,10,16);  //��
		OLED_ShowChinese(58,16,11,16);  //��
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Light rain") == 0)
	{
		printf("С��\n");
		OLED_ShowChinese(41,16,12,16);  //С
		OLED_ShowChinese(58,16,13,16);  //��
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Cloudy") == 0)
	{
		printf("����\n");
		OLED_ShowChinese(41,16,14,16);  //��
		OLED_ShowChinese(58,16,15,16);  //��
	}
	else if(strcmp(WEATHER_InitStruct.text_day,"Clear") == 0)
	{
		printf("��\n");
		OLED_ShowChinese(41,16,16,16);  //��
//		OLED_ShowString(58,20," ",16);
	}
	else 
	{
		printf("δ֪");
		OLED_ShowChinese(41,16,16,16);  //��
	}
	//	//�����¶�
	ss = strstr(strEsp8266_Fram_Record .Data_RX_BUF,"temperature");
	ss = ss + 14;
	sscanf(ss,"%2d",&WEATHER_InitStruct.text_temp);
	printf("�¶ȣ�%d��\n",WEATHER_InitStruct.text_temp);


	OLED_ShowChinese(0,32,5,16);  //��
	OLED_ShowChinese(17,32,6,16); //��
	OLED_ShowString(34,32,":",16);
	
	OLED_ShowNum(43,32,WEATHER_InitStruct.text_temp,2,16);
	OLED_ShowChinese(60,32,0,16);

	//��������
	ss = strstr(strEsp8266_Fram_Record .Data_RX_BUF,"last_update");
	ss = ss + 14;
	sscanf(ss,"%[^T]",WEATHER_InitStruct.text_date);
	printf("����:");
	printf("%s\n",WEATHER_InitStruct.text_date);
	OLED_ShowChinese(0,48,17,16);  //��
	OLED_ShowChinese(17,48,18,16); //��
	OLED_ShowString(34,48,":",16);
	OLED_ShowString(40,48,WEATHER_InitStruct.text_date,16);
	
}

/********************************************���ӷ�����*************************************************************************/

/**
  * @brief  ESP8266 StaTcpClient Unvarnish ���ò��Ժ���
  * @param  ��
  * @retval ��
  */
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
  printf( "\r\n�������� ESP8266 ......\r\n" );
  printf( "\r\nʹ�� ESP8266 ......\r\n" );
	
	OLED_ShowString(0,0,"Enable ESP8266",16);
	OLED_Refresh();
	
	macESP8266_CH_ENABLE();
	OLED_ShowString(0,0,"AT Test ......",16);
	OLED_Refresh();
	while( ! ESP8266_AT_Test() );
  OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n�������ù���ģʽ STA ......\r\n" );

	OLED_ShowString(0,0,"Set STA_Mode .",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
	while( ! ESP8266_Net_Mode_Choose ( STA ) );
  OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n�������� WiFi ......\r\n" );
	OLED_ShowString(0,0,"Link WIFI ....",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
  while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n��ֹ������ ......\r\n" );
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
	
  printf( "\r\n����������֪���� ......\r\n" );
	OLED_ShowString(0,0,"Link Server ...",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
	while( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
  printf( "\r\n����͸������ģʽ ......\r\n" );
	OLED_ShowString(0,0,"Send mode ...",16);
	OLED_ShowString(0,17,"  ",16);
	OLED_Refresh();
	while( ! ESP8266_UnvarnishSend () );
	OLED_ShowString(0,17,"OK",16);
	OLED_Refresh();
	
	printf( "\r\n���� ESP8266 ���\r\n" );
	printf ( "\r\n��ʼ͸��......\r\n" );
	OLED_ShowString(0,0,"Finish         ",16);
	OLED_ShowString(0,17,"Press down K1 ",16);
	OLED_Refresh();
}

/*************************************************************************************************************************/

/**
  * @brief  ESP8266 ����Ƿ���յ������ݣ�������Ӻ͵�������
  * @param  ��
  * @retval ��
  */
void ESP8266_CheckRecvDataTest(void)
{
  uint8_t ucStatus;
	

  if ( ucTcpClosedFlag )                                             //����Ƿ�ʧȥ����
  {
    ESP8266_ExitUnvarnishSend ();                                    //�˳�͸��ģʽ
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //��ȡ����״̬
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //ȷ��ʧȥ���Ӻ�����
    {
      printf ( "\r\n���������ȵ�ͷ����� ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}



