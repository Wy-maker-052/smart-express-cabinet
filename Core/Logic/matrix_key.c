#include "matrix_key.h"

#define H1_LOW() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4|GPIO_PIN_3,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);\
   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET) //0111 
	 
	 
#define H2_LOW() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5|GPIO_PIN_3,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);\
   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET) //1011
	 
	 
#define H3_LOW() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5|GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);\
   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET) //1101
	 
	 
#define H4_LOW() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3,GPIO_PIN_SET);\
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET) //1110
	 
	 
#define L_HIGHT() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET)



#define L4_READ() HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)
#define L3_READ() HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11)
#define L2_READ() HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)
#define L1_READ() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)

void Matrix_KeyInit()
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	
	
	
	
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	
}

#define key_delay 1



void matrix_delay(uint32_t i)
{
	uint16_t n = 0;
	while(i--)
		for(n = 0;n < 36;n++)
			__nop();
	
}



unsigned char Matrix_Key()
{
  uint8_t KeyNumber = 0;
  H1_LOW();
	matrix_delay(1);
  if (L1_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L1_READ() == GPIO_PIN_RESET)
    {
			if(!L1_READ())
      KeyNumber = 1;
    }  
  }

  if (L2_READ() == GPIO_PIN_RESET)
  {   
    HAL_Delay(key_delay);
    if (L2_READ() == GPIO_PIN_RESET)
    {
     
      if (!L2_READ())
      KeyNumber = 2;
    }   
  }

  if (L3_READ() == GPIO_PIN_RESET)
  {
    HAL_Delay(key_delay);
    if (L3_READ() == GPIO_PIN_RESET)
    {
      if (!L3_READ())
      KeyNumber = 3;
    } 
  } 

  if (L4_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L4_READ() == GPIO_PIN_RESET)
    {
      if (!L4_READ())
      KeyNumber = 4;
    }    
  }
                                                                                                                                        
  H2_LOW();
	matrix_delay(1);
  if (L1_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L1_READ() == GPIO_PIN_RESET)
    {
      if (!L1_READ())
      KeyNumber = 5;
    }  
  }

  if (L2_READ() == GPIO_PIN_RESET)
  {   
    HAL_Delay(key_delay);
    if (L2_READ() == GPIO_PIN_RESET)
    {
     
      if (!L2_READ())
      KeyNumber = 6;
    }   
  }

  if (L3_READ() == GPIO_PIN_RESET)
  {
    HAL_Delay(key_delay);
    if (L3_READ() == GPIO_PIN_RESET)
    {
      if (!L3_READ())
      KeyNumber = 7;
    } 
  } 

  if (L4_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L4_READ() == GPIO_PIN_RESET)
    {
      if (!L4_READ())
      KeyNumber = 8;
    }    
  }
  
  H3_LOW();
	matrix_delay(1);
  if (L1_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L1_READ() == GPIO_PIN_RESET)
    {
      if (!L1_READ())
      KeyNumber = 9;
    }  
  }

  if (L2_READ() == GPIO_PIN_RESET)
  {   
    HAL_Delay(key_delay);
    if (L2_READ() == GPIO_PIN_RESET)
    {
     
      if (!L2_READ())
      KeyNumber = 10;
    }   
  }

  if (L3_READ() == GPIO_PIN_RESET)
  {
    HAL_Delay(key_delay);
    if (L3_READ() == GPIO_PIN_RESET)
    {
      if (!L3_READ())
      KeyNumber = 11;
    } 
  } 

  if (L4_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L4_READ() == GPIO_PIN_RESET)
    {
      if (!L4_READ())
      KeyNumber = 12;
    }    
  }

  H4_LOW();
	matrix_delay(1);
  if (L1_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L1_READ() == GPIO_PIN_RESET)
    {
      if (!L1_READ())
      KeyNumber = 13;
    }  
  }

  if (L2_READ() == GPIO_PIN_RESET)
  {   
    HAL_Delay(key_delay);
    if (L2_READ() == GPIO_PIN_RESET)
    {
     
      if (!L2_READ())
      KeyNumber = 14;
    }   
  }

  if (L3_READ() == GPIO_PIN_RESET)
  {
    HAL_Delay(key_delay);
    if (L3_READ() == GPIO_PIN_RESET)
    {
      if (!L3_READ())
      KeyNumber = 15;
    } 
  } 

  if (L4_READ() == GPIO_PIN_RESET)
  { 
    HAL_Delay(key_delay);
    if (L4_READ() == GPIO_PIN_RESET)
    {
      if (!L4_READ())
      KeyNumber = 16;
    }    
  }
	
   L_HIGHT();
  return KeyNumber;
	
}

uint8_t Press_NumberConfirm(void) 								//根据按键位置和状态变化，进行按键值确认
{		
	 uint8_t keyNum;
	 static unsigned nowState,lastState;
	
	 keyNum = 0;
   lastState = nowState; 													//将当前状态的值赋给上一个状态
	 nowState = Matrix_Key();
	
	 if(lastState == Num_1 && nowState ==0 )				//如果上一次检测按键被按下，下一次检测按键未按下，则按键已经弹开。
	 {
			keyNum = Num_1;
	 }
	 
	 if(lastState == Num_2 && nowState ==0 )
	 {
			keyNum = Num_2;
	 }
	 
	 if(lastState == Num_3 && nowState ==0 )
	 {
			keyNum = Num_3;
	 }
	 
	 if(lastState == Num_4 && nowState ==0 )					//备用
	 {
			keyNum = Num_13;
	 }
	 
	 if(lastState == Num_5 && nowState ==0 )
	 {
			keyNum = Num_4;
	 }	
	 	 
	 if(lastState == Num_6 && nowState ==0 )
	 {
			keyNum = Num_5;
	 }	
	 
	 if(lastState == Num_7 && nowState ==0 )
	 {
			keyNum = Num_6;
	 }	
	 
	 if(lastState == Num_8 && nowState ==0 )				 //备用
	 {
			keyNum = Num_14;
	 }	
	 		 
	 if(lastState == Num_9 && nowState ==0 )
	 {
			keyNum = Num_7;
	 }	
	 
	 if(lastState == Num_10 && nowState ==0 )
	 {
			keyNum = Num_8;
	 }	
	 
	 if(lastState == Num_11 && nowState ==0 )
	 {
			keyNum = Num_9;
	 }	
	 
	 if(lastState == Num_12 && nowState ==0 )					//备用
	 {
			keyNum = Num_15;
	 }	
	 
	 if(lastState == Num_13 && nowState ==0 )
	 {
			keyNum = Num_11;
	 }	
	 
	 if(lastState == Num_14 && nowState ==0 )
	 {
			keyNum = Num_10;
	 }	
	 
   if(lastState == Num_15 && nowState ==0 )
	 {
			keyNum = Num_12;
	 }	
	 
   if(lastState == Num_16 && nowState ==0 )					//备用
	 {
			keyNum = Num_16;
	 }	
	 
	 return keyNum;	 
}








void Matrix_KeyTest()
{
	#include "stdio.h"
	unsigned int n = Matrix_Key();
	if (n)
	{
		printf("%u\n",n);
		//OLED_ShowNum(1,1,n,2,16,0);
	}
}
