#include "abs_ht32led.h"

/********************************************************
* Function name 				:Abs_Ht32led_On
* Description       :开灯 
* Parameter         :
* @number           选择开哪个灯 
* Return          		:无
**********************************************************/
void Abs_Ht32led_On(enum HT32LED_NUMBER number)
{
	switch(number)
	{
		case (HT32LED1):
			GPIO_WriteOutBits(BSP_HT32LED_GPIO,BSP_HT32LED1_GPIO_PIN,RESET);
			break;
		case (HT32LED2):
			GPIO_WriteOutBits(BSP_HT32LED_GPIO,BSP_HT32LED2_GPIO_PIN,RESET);
			break;
		default:
			break;
	}
}

/********************************************************
* Function name 				:Abs_Ht32led_Off
* Description       :关灯 
* Parameter         :
* @number           选择关哪个灯 
* Return          		:无
**********************************************************/
void Abs_Ht32led_Off(enum HT32LED_NUMBER number)
{
	switch(number)
	{
		case (HT32LED1):
			GPIO_WriteOutBits(BSP_HT32LED_GPIO,BSP_HT32LED1_GPIO_PIN,SET);
			break;
		case (HT32LED2):
			GPIO_WriteOutBits(BSP_HT32LED_GPIO,BSP_HT32LED2_GPIO_PIN,SET);
			break;
		default:
			break;
	}
}
