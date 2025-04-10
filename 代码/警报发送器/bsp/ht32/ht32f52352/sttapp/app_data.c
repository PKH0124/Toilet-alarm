#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include <string.h>

#include "bsp_asr.h"

#include "abs_lora.h"
#include "abs_ht32led.h"
#include "abs_y100.h"
#include "bsp_alarm.h"

#include "app_data.h"

ABS_LORA_STRUCT app_data_struction = {0};


int app_lcd_temperature[24];
int app_lcd_humi[24];
int app_lcd_co[24];
	
u8 app_flash_temperature_change_flag;
u8 app_flash_humi_change_flag;
u8 app_flash_co_change_flag;	




void App_Data_Update(void)
{
	uint8_t mutex_flag = 0;
	Abs_Lora_Getdata(s_bsp_lora_rx);
	Bsp_Lora_Printf("wu\\%d\\%d\\%d\\%s#",abs_lota_struction.temperature,abs_lota_struction.humidity,abs_lota_struction.co,abs_lota_struction.radar);
	if(app_data_struction.temperature != abs_lota_struction.temperature)
	{
		app_data_struction.temperature = abs_lota_struction.temperature;
		Bsp_Y100_Printf("{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temperature\":{\"value\":%d}}}",app_data_struction.temperature);
	}	
	if(app_data_struction.humidity != abs_lota_struction.humidity)
	{
		app_data_struction.humidity = abs_lota_struction.humidity;
		Bsp_Y100_Printf("{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"humidity\":{\"value\":%d}}}",app_data_struction.humidity);
	}
	if(strcmp((char*)app_data_struction.radar, (char*)abs_lota_struction.radar) != 0)
	{
		strcpy(app_data_struction.radar, abs_lota_struction.radar);
		Bsp_Y100_Printf("{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"WeChat\":{\"value\":%s}}}",app_data_struction.radar);
		if(strcmp((char*)app_data_struction.radar, "yes") == 0)
		{
			bsp_asr_check_flag = 1;
			mutex_flag = 1;
		}
	}
	if(app_data_struction.co != abs_lota_struction.co)
	{
		app_data_struction.co = abs_lota_struction.co;
		Bsp_Y100_Printf("{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"co\":{\"value\":%d}}}",app_data_struction.co);
		//rt_kprintf("mutex:%d",mutex_flag);
		if(abs_lota_struction.co >= 200 && mutex_flag == 0)
		{
			Bsp_Asr_On(BSP_ASR_CO);
			Bsp_Alarm_On(BSP_ALARM_FELL);
		}
		else
		{
			Bsp_Asr_Off(BSP_ASR_CO);
			Bsp_Alarm_Off(BSP_ALARM_FELL);
		}
	}
	mutex_flag = 0;
}


