#ifndef __BSP_LORA_H__
#define __BSP_LORA_H__
 
#include "ht32.h"

#define BSP_LORA_MAX_LEN (200)/*最大缓存长度*/

#define BSP_LORA (HT_USART0)

#define BSP_LORA_CLK(CK) (CKCUClock.Bit.USART0)

#define BSP_LORA_AFIO 	(GPIO_PA)
#define BSP_LORA_AFIO_TX	(AFIO_PIN_2)
#define BSP_LORA_AFIO_RX	(AFIO_PIN_3)

#define BSP_LORA_GPIO 	(HT_GPIOC)
#define	BSP_LORA_GPIO_RES	(GPIO_PIN_8)

#define BSP_LORA_IRQN (USART0_IRQn)

void Bsp_Lora_Res_Config(void);
void Bsp_Lora_Usart_Config(void);
void Bsp_Lora_Sendbyte(char Data);
void Bsp_Lora_SendArray(char array[],uint8_t num);
void Bsp_Lora_SendStr(char *str);
void Bsp_Lora_Printf(char* fmt,...);

#endif
