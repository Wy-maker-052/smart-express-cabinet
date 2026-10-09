#include "bsp_time.h"
#include "ExtendTimer.h"

uint16_t b = 0;
uint32_t Time_Count = 0;
//定时器中断处理函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&htim6))
    {
		Etimer_Ticks();
		b++;
		if(b > 100)
		{
			b = 0;
			Time_Count++;
		}	
    }

}




















