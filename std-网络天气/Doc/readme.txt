本实验最小系统为:STM32F103C6T6

按下按键获取天气，第一次上电需要按下两次才可获取到天气，默认获取天气为：郑州
本实验中连接的 WIFI：Redmi K40         密码：h123456.

如若修改连接WIFI与获取天气地区，打开"bsp_esp8266_test.h"即可修改

引脚连接

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

AT连接心知天气流程：https://www.cnblogs.com/lei-hao/p/15606750.html