#ifndef _BSP_IIC_H
#define _BSP_IIC_H

/*
   !!! 在访问I2C设备前，请先调用 iic_check_device() 检测I2C设备是否正常，该函数会配置GPIO
*/
#include "stm32f10x.h"

#define IIC_WR	0		/* 写控制bit */
#define IIC_RD	1		/* 读控制bit */


/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面代码即可任意改变SCL和SDA的引脚 */
#define IIC_RCC_PORT 	RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
//SCL
#define IIC_SCL_GPIO_PORT	GPIOB			        /* GPIO端口 */
#define IIC_SCL_PIN		    GPIO_Pin_6	            /* 连接到SCL时钟线的GPIO */
//SDA
#define IIC_SDA_GPIO_PORT	GPIOB			        /* GPIO端口 */
#define IIC_SDA_PIN		    GPIO_Pin_7			    /* 连接到SDA数据线的GPIO */
/*--------------------------------------------------------------------------*/

/*　注意：如下写法，在IAR最高级别优化时，会被编译器错误优化 */
#define IIC_SCL_Hight()  IIC_SCL_GPIO_PORT->BSRR = IIC_SCL_PIN		    /* SCL = 1 */
#define IIC_SCL_Low()    IIC_SCL_GPIO_PORT->BRR = IIC_SCL_PIN				/* SCL = 0 */

#define IIC_SDA_Hight()  IIC_SDA_GPIO_PORT->BSRR = IIC_SDA_PIN			/* SDA = 1 */
#define IIC_SDA_Low()    IIC_SDA_GPIO_PORT->BRR = IIC_SDA_PIN				/* SDA = 0 */

#define IIC_SDA_READ()  ((IIC_SDA_GPIO_PORT->IDR & IIC_SDA_PIN) != 0)	/* 读SDA口线状态 */
/*--------------------------------------------------------------------------*/


void    iic_start(void);
void    iic_stop(void);
void    iic_send_byte(uint8_t _ucByte);
uint8_t iic_read_byte(void);
uint8_t iic_wait_ack(void);
void    iic_ack(void);
void    iic_no_ack(void);
uint8_t iic_check_device(uint8_t _Address);


#endif

