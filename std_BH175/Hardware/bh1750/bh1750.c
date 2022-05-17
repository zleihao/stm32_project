/**
 * @brief               bh1750.c
 * @Date:               2022.4.20
 * @Revision:           V1.0
 * @Writer:             点灯大师
 * @Affiliated unit：   黄河科技学院
 * @Email:              im_leihao@163.com          
 * @note:               参考BH1750数据手册，更多驱动：https://gitee.com/zleihao/st_stm32_drive.git
 */
#include "bh1750.h"

/**
 * @brief  bh_CheckOk
 * @param  无
 * @return 0: 检测到bh1750  1：没有检测到bh1750
 * @note   检测总线上是否有bh1750设备 
 */
uint8_t bh_CheckOk()
{
	if(iic_check_device(BH_DEVICE_ADDR) == 0)
	{
	   iic_stop();
	   return 0;
	}
	else {
        iic_stop();
		return 1;
    }
}

/**
 * @brief  bh1570_Init
 * @param  无
 * @return 无
 * @note   设置工作模式为：连续H分辨率模式
 *         设置步骤为：Power on -> Continuously H-Resolution Mode
 */
void bh1570_Init(void) {
    //power on
    iic_start();
    iic_send_byte(BH_DEVICE_ADDR);
    iic_wait_ack();
    iic_send_byte(POWER_ON);
    iic_wait_ack();
    iic_stop();

    //Continuously H-Resolution Mode
    iic_start();
    iic_send_byte(BH_DEVICE_ADDR);
    iic_wait_ack();
    iic_send_byte(H_RESOLUTION_MODE);
    iic_wait_ack();
    iic_stop();   

    //Wait to complete 1st H-resolution mode measurement.( max. 180ms. )
    SysTick_Delay_Ms(200);
}

/**
 * @brief  read_result
 * @param  无
 * @return 无
 * @note   读取到设备bh1750采集到值
 */
float read_result(void) {
    uint8_t msb,lsb;
    uint16_t dat;  
    float temp;

    iic_start();
    //读
    iic_send_byte(BH_DEVICE_ADDR | IIC_RD);
    iic_wait_ack();
    //读取高8位数据
    msb = iic_read_byte();
    iic_ack();
    //读取低8位数据
    lsb = iic_read_byte();
    iic_no_ack();
    iic_stop();
    SysTick_Delay_Ms(5);
    //合并数据
    dat = msb;
    dat = (dat << 8) | lsb;
    //换算比 1.2
    temp = (float)dat/1.2; 

    return temp;
}