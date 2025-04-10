#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__
 
#include "ht32.h"

#define BSP_KEY_CLK(CK)		(CKCUClock.Bit.PC)/*时钟*/
#define BSP_KEY_GPIO 	(HT_GPIOC)/*GPIO*/
#define BSP_KEY_GPIO_PIN	(GPIO_PIN_3)/*引脚*/



void Bsp_Key_Config(void);
uint8_t Bsp_Key_Read(void);

#endif
