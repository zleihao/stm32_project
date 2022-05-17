/**
 * @brief               bsp_exti.c
 * @Date:               2022.4.20
 * @Revision:           V1.0
 * @Writer:             点灯大师
 * @Affiliated unit：   黄河科技学院
 * @Email:              im_leihao@163.com
 * @gitee:              https://gitee.com/zleihao/st_stm32_drive.git
 * @note:               参考野火例程
 */
#include "bsp_iic.h"

/**
 * @brief   iic_delay
 * @param   无
 * @return  无
 * @note    I2C总线位延迟，最快400KHz
 */
static void iic_delay(void)
{
	uint8_t i;
	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
        工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
	for (i = 0; i < 10; i++);
}

/**
 * @brief    iic_start
 * @param    无
 * @return   无
 * @note     CPU发起I2C总线启动信号
 * @remark   起始时序      
 *           SDA   ˉˉˉˉˉ\_______
 *           SCL    ˉˉˉˉˉˉˉˉ\_______           
 *                    |   |
 * 			          START
 */
void iic_start(void)
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	IIC_SDA_Hight();
	IIC_SCL_Hight();
	iic_delay();
	IIC_SDA_Low();
	iic_delay();
	IIC_SCL_Low();
	iic_delay();
}

/**
 * @brief    iic_stop
 * @param    无
 * @return   无
 * @note     CPU发起I2C总线停止信号
 * @remark   停止时序
 *           SCL _____/ˉˉˉˉˉˉˉ
 *           SDA _________/ˉˉˉˉˉ
 *                     |   |
 *                     STOP    
 */
void iic_stop(void)
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	IIC_SDA_Low();
	IIC_SCL_Hight();
	iic_delay();
	IIC_SDA_Hight();
}

/**
 * @brief    iic_send_byte
 * @param    _ucByte  等待发送的字节
 * @return   无
 * @note     CPU向I2C总线设备发送8bit数据
 */
void iic_send_byte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			IIC_SDA_Hight();
		}
		else
		{
			IIC_SDA_Low();
		}
		iic_delay();
		IIC_SCL_Hight();
		iic_delay();	
		IIC_SCL_Low();
		if (i == 7)
		{
			IIC_SDA_Hight(); // 释放总线
		}
		_ucByte <<= 1;	/* 左移一个bit */
		iic_delay();
	}
}

/**
 * @brief    iic_read_byte
 * @param    无
 * @return   读到的数据
 * @note     CPU从I2C总线设备读取8bit数据
 */
uint8_t iic_read_byte(void)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		IIC_SCL_Hight();
		iic_delay();
		if (IIC_SDA_READ())
		{
			value++;
		}
		IIC_SCL_Low();
		iic_delay();
	}
	return value;
}

/**
 * @brief    iic_wait_ack
 * @param    无
 * @return   返回0表示正确应答，1表示无器件响应
 * @note     CPU产生一个时钟，并读取器件的ACK应答信号
 */
uint8_t iic_wait_ack(void)
{
	uint8_t re;

	IIC_SDA_Hight();	/* CPU释放SDA总线 */
	iic_delay();
	IIC_SCL_Hight();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	iic_delay();
	if (IIC_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	IIC_SCL_Low();
	iic_delay();
	return re;
}

/**
 * @brief    iic_ack
 * @param    无
 * @return   无
 * @note     CPU产生一个ACK信号
 */
void iic_ack(void)
{
	IIC_SDA_Low();	/* CPU驱动SDA = 0 */
	iic_delay();
	IIC_SCL_Hight();	/* CPU产生1个时钟 */
	iic_delay();
	IIC_SCL_Low();
	iic_delay();
	IIC_SDA_Hight();	/* CPU释放SDA总线 */
}

/**
 * @brief    iic_no_ack
 * @param    无
 * @return   无
 * @note     CPU产生1个NACK信号
 */
void iic_no_ack(void)
{
	IIC_SDA_Hight();	/* CPU驱动SDA = 1 */
	iic_delay();
	IIC_SCL_Hight();	/* CPU产生1个时钟 */
	iic_delay();
	IIC_SCL_Low();
	iic_delay();	
}

/**
 * @brief    iic_config_gpio
 * @param    无
 * @return   无
 * @note     配置I2C总线的GPIO，采用模拟IO的方式实现
 */
static void iic_config_gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(IIC_RCC_PORT, ENABLE);	/* 打开GPIO时钟 */
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* 开漏输出 */

	//SCL
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN;
	GPIO_Init(IIC_SCL_GPIO_PORT, &GPIO_InitStructure);

	//SDA
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_Init(IIC_SDA_GPIO_PORT, &GPIO_InitStructure);
	/* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
	iic_stop();
}

/**
 * @brief    iic_check_device
 * @param    _Address  设备的I2C总线地址
 * @return   返回值     0 表示正确， 返回1表示未探测到
 * @note     检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
 */
uint8_t iic_check_device(uint8_t _Address)
{
	uint8_t ucAck;

	iic_config_gpio();		/* 配置GPIO */

	
	iic_start();		/* 发送启动信号 */

	/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
	iic_send_byte(_Address | IIC_WR);
	ucAck = iic_wait_ack();	/* 检测设备的ACK应答 */

	iic_stop();			/* 发送停止信号 */

	return ucAck;
}
