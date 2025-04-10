#ifndef __BSP_ALARM_H__
#define __BSP_ALARM_H__
 
#include "ht32.h"

#define BSP_ALARM_CLK(CK)		(CKCUClock.Bit.PC)/*时钟*/

#define BSP_ALARM_GPIO 	(HT_GPIOC)/*GPIO*/
#define BSP_ALARM_GPIO_FELL_PIN	(GPIO_PIN_0)/*引脚*/
#define BSP_ALARM_GPIO_CO_PIN	(GPIO_PIN_1)

/*枚举灯的编号*/
enum BSP_ALARM_NUMBER{
	BSP_ALARM_FELL,
	BSP_ALARM_CO,
};

void Bsp_Alarm_Config(void);
void Bsp_Alarm_On(enum BSP_ALARM_NUMBER number);
void Bsp_Alarm_Off(enum BSP_ALARM_NUMBER numbe);

#endif
