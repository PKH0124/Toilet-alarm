#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__
 
#include "ht32.h"

#define BSP_BEEP_CLK(CK)		(CKCUClock.Bit.PC)/*时钟*/

#define BSP_BEEP_GPIO 	(HT_GPIOC)/*GPIO*/
#define BSP_BEEP1_GPIO_PIN	(GPIO_PIN_5)/*引脚*/


void Bsp_Beep_Config(void);
void Bsp_Beep_On(void);
void Bsp_Beep_Off(void);

#endif
