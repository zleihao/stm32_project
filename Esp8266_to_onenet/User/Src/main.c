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
#include "usart.h"
#include "stm32f10x_it.h"
#include "esp8266.h"
#include "delay.h"
#include "string.h"
#include "bsp_led.h"
#include "onenet.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
	
int main ( void )
{
	unsigned short timeCount = 0;	//发送间隔变量
	
	unsigned char *dataPtr = NULL;

	LED_GPIO_Config();
	Delay_Init();									//systick初始化

	/* 初始化 */
	Usart1_Init (115200);                                                  //初始化串口1
	ESP8266_Init ();                                                      //初始化WiFi模块使用的接口和外设

	esp8266_to_server();

	while(OneNet_DevLink())			//接入OneNET
		DelayXms(500);
		
  	while ( 1 )
  	{
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL) {
			OneNet_RevPro(dataPtr);
			dataPtr = NULL;
		}
		DelayXms(10);	
  	}
	
}


/*********************************************END OF FILE**********************/

