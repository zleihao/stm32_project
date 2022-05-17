/**		 
 * @Date:               2022.3.16 
 * @Revision:           V1.0
 * @Writer:             点灯大师
 * @Affiliated unit：   黄河科技学院
 * @Description:        基于STM32F103的固件库工程模板
 * @Email:              im_leihao@163.com
 * @gitee:              https://gitee.com/zleihao/STM32F103.git
 */
#include "bsp_debug_usart.h"
#include"bsp_iic.h"
#include "bh1750.h"


int main(void) {

	//初始化USART1
	USART_Config();
	SysTick_Init();
	printf("BH1750实验\n");
	if (bh_CheckOk() == 0) {
		printf("检测到bh1750设备\n");
	} else {
		printf("设备不存在，已退出\n");
		return 0;
	}
    //初始化bh1750
	bh1570_Init();
	while (1) {
		printf("%0.3f\n",read_result());
		//200ms读取一次
		SysTick_Delay_Ms(200);
	}

}
