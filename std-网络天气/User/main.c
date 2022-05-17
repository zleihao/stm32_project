/*
		�ƺӿƼ�ѧԺ
		
		��ƴ�ʦ
		
		����: mail.leihao@gmail.com

		ESP8266:
		RX-->PA2
		TX-->PA3
		RST-->PA4
		EN-->PA5
		VCC-->3.3V
		GND-->GND

		OLED:
		CS-->PA8
		DC-->PB15
		RES-->PB14
		D1-->PB13
		D0-->PB12
		VCC-->5V
		GND-->GND

		����-->PB9
*/

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "stm32f10x_it.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "bsp_key.h"
#include "./dwt_delay/core_delay.h"
#include "string.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "Systick.h"
	
int main ( void )
{

	/* ��ʼ�� */
	OLED_Init();
  USART_Config ();                                                      //��ʼ������1
  CPU_TS_TmrInit();                                                     //��ʼ��DWT��������������ʱ����
	KEY_GPIO_Config();
	ESP8266_Init ();                                                      //��ʼ��WiFiģ��ʹ�õĽӿں�����
	
	  
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          //��ESP8266��������
  
  while ( 1 )
  {
    if (Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			OLED_ShowString(0,0, "              ",16);
			OLED_ShowString(0,17,"              ",16);
			OLED_Refresh();
			macESP8266_Usart(TEMP_DATA);
			
			if( strEsp8266_Fram_Record .InfBit .FramFinishFlag )
			{
				USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, DISABLE ); //���ô��ڽ����ж�
				strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
				
				Display_Weather();

			
				USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, ENABLE ); //ʹ�ܴ��ڽ����ж�
			}
		}
		OLED_Refresh();
  }
}
