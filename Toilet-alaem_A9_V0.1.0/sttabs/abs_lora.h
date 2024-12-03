#ifndef __ABS_LORA_H__
#define __ABS_LORA_H__
 
#include "ht32.h"
#include "bsp_lora.h"

#define ABS_LORA_IRQHANDLER (USART0_IRQHandler)/*接收中断函数*/

typedef struct LORA_USART {
    char buffer[BSP_LORA_MAX_LEN];
    int length;
}LORA_USART;

void Abs_Lora_Clear_Struct(void);
int32_t Abs_Lora_Send_Cmd(char* cmd, char* reply, uint32_t wait);
int32_t Abs_Lora_Wakeup(void);
int32_t Abs_Lora_EnterAT(void);
int32_t Abs_Lora_SetAT(void);
void Abs_Lora_Res(void);
void Abs_Lora_Init(void);

#endif







