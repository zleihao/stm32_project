#ifndef _ONENET_H_
#define _ONENET_H_

//单片机头文件
#include "stm32f10x.h"

//网络设备
#include "esp8266.h"

//协议文件
#include "MqttKit.h"

//C库
#include <string.h>
#include <stdio.h>

//硬件驱动
#include "usart.h"
#include "delay.h"
#include "bsp_led.h"

/********************更改为自己的********************************/
#define PROID		"471989"     //产品ID

#define AUTH_INFO	"12345"      //鉴权信息

#define DEVID		"857569357"  //设备ID

/**********************END***************************************/


/*********************函数声明区********************************/
_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

void OneNet_RevPro(unsigned char *cmd);

/**********************END***************************************/

#endif
