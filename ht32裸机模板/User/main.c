#include "ht32.h"
#include "ht32_board.h"
#include "bsp_debug.h"
#include "abs_lora.h"
#include "abs_ht32led.h"
#include "abs_delay.h"

int main()
{	
	Bsp_Ht32led_Config();
	Bsp_Debug_Config();
	Abs_Lora_Init();
	while(1)
	{
		
	}	
}

