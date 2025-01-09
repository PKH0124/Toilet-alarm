#ifndef __BSP_HT32LED_H__
#define __BSP_HT32LED_H__
 
#include "ht32.h"

#define BSP_HT32LED_CLK(CK)		(CKCUClock.Bit.PC)/*时钟*/

#define BSP_HT32LED_GPIO 	(HT_GPIOC)/*GPIO*/
#define BSP_HT32LED1_GPIO_PIN	(GPIO_PIN_14)/*引脚*/
#define BSP_HT32LED2_GPIO_PIN	(GPIO_PIN_15)

/*枚举灯的编号*/
enum BSP_HT32LED_NUMBER{
	BSP_HT32LED1,
	BSP_HT32LED2
};

void Bsp_Ht32led_Config(void);
void Bsp_Ht32led_On(enum BSP_HT32LED_NUMBER number);
void Bsp_Ht32led_Off(enum BSP_HT32LED_NUMBER number);

#endif
