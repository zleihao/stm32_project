#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

/*************************************************************
              GND  ��Դ��
              VCC  5v��Դ
              D0   PB12��SCL��
              D1   PB13��SDA�� 
              RES  PB14
              DC   PB15
              CS   PA8             
*************************************************************/

//-----------------OLED�˿ڶ���---------------- 

//SCL  --->  D0
#define OLED_SCLK_GPIO_CLK	   RCC_APB2Periph_GPIOB
#define OLED_SCLK_GPIO_PORT    GPIOB
#define OLED_SCLK_GPIO_PIN	   GPIO_Pin_12
//SDA  --->  D1
#define OLED_SDIN_GPIO_CLK	   RCC_APB2Periph_GPIOB
#define OLED_SDIN_GPIO_PORT    GPIOB
#define OLED_SDIN_GPIO_PIN	   GPIO_Pin_13
//RES
#define OLED_RST_GPIO_CLK	   RCC_APB2Periph_GPIOB
#define OLED_RST_GPIO_PORT   GPIOB
#define OLED_RST_GPIO_PIN	   GPIO_Pin_14
//DC
#define OLED_DC_GPIO_CLK	   RCC_APB2Periph_GPIOB
#define OLED_DC_GPIO_PORT      GPIOB
#define OLED_DC_GPIO_PIN	   GPIO_Pin_15
//CS
#define OLED_CS_GPIO_CLK	   RCC_APB2Periph_GPIOA
#define OLED_CS_GPIO_PORT    GPIOA
#define OLED_CS_GPIO_PIN	   GPIO_Pin_8

//-----------------OLED�˿ڶ���---------------- 

#define OLED_SCLK_Clr() GPIO_ResetBits(OLED_SCLK_GPIO_PORT,OLED_SCLK_GPIO_PIN)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(OLED_SCLK_GPIO_PORT,OLED_SCLK_GPIO_PIN)

#define OLED_SDIN_Clr() GPIO_ResetBits(OLED_SDIN_GPIO_PORT,OLED_SDIN_GPIO_PIN)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(OLED_SDIN_GPIO_PORT,OLED_SDIN_GPIO_PIN)

#define OLED_RST_Clr() GPIO_ResetBits(OLED_RST_GPIO_PORT,OLED_RST_GPIO_PIN)//RES
#define OLED_RST_Set() GPIO_SetBits(OLED_RST_GPIO_PORT,OLED_RST_GPIO_PIN)

#define OLED_DC_Clr() GPIO_ResetBits(OLED_DC_GPIO_PORT,OLED_DC_GPIO_PIN)//DC
#define OLED_DC_Set() GPIO_SetBits(OLED_DC_GPIO_PORT,OLED_DC_GPIO_PIN)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(OLED_CS_GPIO_PORT,OLED_CS_GPIO_PIN)//CS
#define OLED_CS_Set()  GPIO_SetBits(OLED_CS_GPIO_PORT,OLED_CS_GPIO_PIN)


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);

#endif
