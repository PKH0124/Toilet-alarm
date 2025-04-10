#ifndef __BSP_LCD_H__
#define __BSP_LCD_H__
 
#include "ht32.h"

#define BSP_Y100_MAX_LEN (200)/*??????*/

#define BSP_Y100 (HT_UART1)

#define BSP_Y100_CLK(CK) (CKCUClock.Bit.UART1)

#define BSP_Y100_AFIO 	(GPIO_PC)
#define BSP_Y100_AFIO_TX	(AFIO_PIN_12)
#define BSP_Y100_AFIO_RX	(AFIO_PIN_13)

#define BSP_Y100_IRQN (UART1_IRQn)
#define BSP_Y100_IRQHANDLER (UART1_IRQHandler)/*??????*/

void Bsp_Y100_Config(void);
void Bsp_Y100_Sendbyte(uint8_t Data);
void Bsp_Y100_SendArray(uint8_t *array,u8 num);
void Bsp_Y100_SendStr(char *str);
void Bsp_Y100_Printf(char* fmt,...);

 



#endif
