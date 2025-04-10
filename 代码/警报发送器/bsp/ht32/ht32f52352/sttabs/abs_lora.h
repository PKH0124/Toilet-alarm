#ifndef __ABS_LORA_H__
#define __ABS_LORA_H__
 
#include "ht32.h"
#include "bsp_lora.h"

typedef struct ABS_LORA_STRUCT {
	int temperature;
	int humidity;
	int co;
	char radar[3];
}ABS_LORA_STRUCT ;

extern ABS_LORA_STRUCT abs_lota_struction;

int32_t Abs_Lora_Wakeup(void);
int32_t Abs_Lora_EnterAT(void);
int32_t Abs_Lora_SetAT(void);
void Abs_Lora_Res(void);
void Abs_Lora_Init(void);
void Abs_Lora_Getdata(BSP_LORA_USART struction);

#endif







