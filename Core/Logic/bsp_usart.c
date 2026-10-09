#include "bsp_usart.h"

uint8_t Rx_Flag = 0,n = 0,Rx_Fulfill = 0;
uint8_t Data[4] = {0};

//usart中断处理函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart2)
  {
		if(Rx_Flag == 65)
		{
			if(n > 0)
				n--;			
			OLED_ShowString(30+16*n,30," ",8);
			OLED_Update();
			Data[n] = 0;
		}
		else
		{
			Data[n] = Rx_Flag - 48;
			OLED_ShowString(30+16*n,30,"*",8);
			OLED_Update();
			n++;
		
		}

		if(n > 3)
		{
			n = 0;
			Rx_Fulfill = 1;
		
		}
		
  }
    HAL_UART_Receive_IT(&huart2,&Rx_Flag,1); 

}



uint8_t Bsp_UsartInit(void)
{
  HAL_UART_Receive_IT(&huart2,&Rx_Flag,1);
	
	return 0;
}

























