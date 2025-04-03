#include "ht32.h"
#include "ht32f5xxxx_01.h"              // Device header
#include "ht32_board.h"

#include "bsp_debug.h"
#include "bsp_LD2410B.h"
#include "bsp_MQ7.h"
#include "bsp_DHT11.h"
#include "bsp_bftm0.h"

#include "abs_lora.h"
#include "abs_ht32led.h"
#include "abs_delay.h"

#include "app_data.h"

//#include "abs_lcd.h"

char c_stateString[3];

int main()
{	
	SystemInit();
	Bsp_Ht32led_Config();
	Abs_Delay_init();

	Bsp_Debug_Config();
	Bsp_LD2410B_Init();
	Bsp_MQ7_Init();
	Bsp_DHT11_Init();
	Bsp_Bftm0_Config();
	Bsp_Ht32led_On(BSP_HT32LED1);
	
	Abs_Lora_Init();
	while(1)
	{		
		App_Data_collect();
		Bsp_Debug_Printf("%x,%d\n",MainData_HLK_2410s.Target_State,bsp_ld24108_target_state_2);
	}
}

void BFTM0_IRQHandler(void)
{
	static uint8_t num = 0;
  if(BFTM_GetFlagStatus(HT_BFTM0) == SET)
  {
      BFTM_ClearFlag(HT_BFTM0); // 清除中断标志位 	
			num++;
			
			if(num == 10)
			{
				bsp_ld24108_target_state_2 = 0;
				num = 0;
			}      
  }
}
