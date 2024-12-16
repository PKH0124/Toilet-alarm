#ifndef __APP_LED_H__
#define __APP_LED_H__
 
#include "ht32.h"
#include "bsp_ht32led.h"

/*枚举灯的编号*/
enum HT32LED_NUMBER{
	HT32LED1,
	HT32LED2
};


void Abs_Ht32led_On(enum HT32LED_NUMBER number);
void Abs_Ht32led_Off(enum HT32LED_NUMBER number);

#endif







