/*
		��ƴ�ʦ
		
		����: im_leihao@163.com
*/

/*
		GPIO: PA6
		
		0��  --> 195
		45�� --> 190
		90�� --> 185
		135�� --> 180
		180�� --> 175
*/

#include "bsp_sg90.h"


int main()
{
	SG90_Init();

	TIM_SetComparex(TIMx,180);  //����ת���Ƕ�
	while (1)
	{

	}
}
