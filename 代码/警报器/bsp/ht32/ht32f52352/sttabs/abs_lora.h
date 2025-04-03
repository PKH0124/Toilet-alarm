#ifndef __ABS_LORA_H__
#define __ABS_LORA_H__
 
#include "ht32.h"
#include "bsp_lora.h"

extern char s_abs_lora_temperature[10];
extern char s_abs_lora_humidity[10];
extern char s_abs_lora_co[10];
extern char s_abs_lora_radar[10];
extern char s_abs_lora_network[10];
extern char s_abs_lora_battery[10];

int32_t Abs_Lora_Wakeup(void);
int32_t Abs_Lora_EnterAT(void);
int32_t Abs_Lora_SetAT(void);
void Abs_Lora_Res(void);
void Abs_Lora_Init(void);
void Abs_Lora_Getdata(BSP_LORA_USART struction);

#endif







