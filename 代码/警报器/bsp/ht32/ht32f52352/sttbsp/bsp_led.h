#ifndef __BSP_LED_H__
#define __BSP_LED_H__
 
#include "ht32.h"

#define BSP_LED_CLK(CK)		(CKCUClock.Bit.PC)/*时钟*/

#define BSP_LED_GPIO 	(HT_GPIOC)/*GPIO*/
#define BSP_LED1_GPIO_PIN	(GPIO_PIN_4)/*引脚*/


void Bsp_Led_Config(void);
void Bsp_Led_On(void);
void Bsp_Led_Off(void);

#endif
