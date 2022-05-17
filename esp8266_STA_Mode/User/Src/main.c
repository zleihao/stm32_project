/**		 
 * @Date:               2022.3.16 
 * @Revision:           V1.0
 * @Writer:             点灯大师
 * @Affiliated unit：   黄河科技学院
 * @Description:        基于STM32F103的固件库工程模板
 * @Email:              im_leihao@163.com
 * @gitee:              https://github.com/zleihao
 */
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "stm32f10x_it.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "core_delay.h"
#include "string.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
	
int main ( void )
{

	/* 初始化 */
	USART_Config ();                                                      //初始化串口1
	CPU_TS_TmrInit();                                                     //初始化DWT计数器，用于延时函数
	ESP8266_Init ();                                                      //初始化WiFi模块使用的接口和外设

	  
	ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          //对ESP8266进行配置

  
  	while ( 1 )
  	{
		ESP8266_CheckRecvDataTest();
  	}
	
}


/*********************************************END OF FILE**********************/

