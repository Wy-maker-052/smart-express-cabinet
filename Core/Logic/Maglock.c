#include "Maglock.h"



void Maglock_On(void)
{
	HAL_GPIO_WritePin(Maglock_GPIO_Port, Maglock_Pin, GPIO_PIN_RESET);
}


void Maglock_Off(void)
{
	HAL_GPIO_WritePin(Maglock_GPIO_Port, Maglock_Pin, GPIO_PIN_SET);
}


