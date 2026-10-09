#ifndef _MATRIX_KEY_H_
#define _MATRIX_KEY_H_

#include "Headerfile.h"


typedef enum 
{
	Num_1 = 1,
	Num_2,
	Num_3,
	Num_4,
	Num_5,
	Num_6,
	Num_7,
	Num_8,
	Num_9,
	Num_10,
	Num_11,
	Num_12,
	Num_13,
	Num_14,
	Num_15,
	Num_16,

}MATRIX_KEYNUM;


void Matrix_KeyInit(void);
unsigned char Matrix_Key(void);
uint8_t Press_NumberConfirm(void);
void Matrix_KeyTest(void);




#endif

