/*
		黄河科技学院
		
		点灯大师
		
		邮箱: mail.leihao@gmail.com

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

		按键-->PB9
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

	/* 初始化 */
	OLED_Init();
  USART_Config ();                                                      //初始化串口1
  CPU_TS_TmrInit();                                                     //初始化DWT计数器，用于延时函数
	KEY_GPIO_Config();
	ESP8266_Init ();                                                      //初始化WiFi模块使用的接口和外设
	
	  
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          //对ESP8266进行配置
  
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
				USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, DISABLE ); //禁用串口接收中断
				strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
				
				Display_Weather();

			
				USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, ENABLE ); //使能串口接收中断
			}
		}
		OLED_Refresh();
  }
}
