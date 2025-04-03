#ifndef __BSP_DEBUG_H__
#define __BSP_DEBUG_H__
 
#include "ht32.h"

#define BSP_DEBUG_MAX_LEN (200)/*最大缓存长度*/

#define BSP_DEBUG (HT_USART0)

#define BSP_DEBUG_CLK(CK) (CKCUClock.Bit.USART0)

#define BSP_DEBUG_AFIO 	(GPIO_PA)
#define BSP_DEBUG_AFIO_TX	(AFIO_PIN_2)
#define BSP_DEBUG_AFIO_RX	(AFIO_PIN_3)

#define BSP_DEBUG_IRQN (USART0_IRQn)
#define BSP_DEBUG_IRQHANDLER (USART0_IRQHandler)/*接收中断函数*/


void Bsp_Debug_Config(void);
void Bsp_Debug_Sendbyte(uint8_t Data);
void Bsp_Debug_SendArray(uint8_t *array,u8 num);
void Bsp_Debug_SendStr(char *str);
void Bsp_Debug_Printf(char* fmt,...);

#endif
