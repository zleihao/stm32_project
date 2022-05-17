/*
		点灯大师
		
		邮箱: im_leihao@163.com
*/

/*
		GPIO: PA6
		
		0度  --> 195
		45度 --> 190
		90度 --> 185
		135度 --> 180
		180度 --> 175
*/

#include "bsp_sg90.h"


int main()
{
	SG90_Init();

	TIM_SetComparex(TIMx,180);  //更改转动角度
	while (1)
	{

	}
}
