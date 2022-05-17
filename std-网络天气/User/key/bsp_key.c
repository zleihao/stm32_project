#include "bsp_key.h"   


void KEY_GPIO_Config()
{
	//�κ�ʱ����Ҫ����CRL
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//��ʼ��CRL
	GPIO_InitTypeDef GPIO_InitStruct;
	//��������
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
	//����ģʽΪ��������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//��Ϊ����Ϊ��������Ҫ��������
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
}

uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON )
	{
		// ���ּ��
		while( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON );
		return KEY_ON;
	}
	else return KEY_OFF;
}
