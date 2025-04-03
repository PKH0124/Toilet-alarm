#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include <string.h>

#include "bsp_beep.h"
#include "bsp_led.h"
#include "bsp_rtc.h"

#include "abs_lcd.h"
#include "abs_lora.h"
#include "abs_ht32led.h"

#include "app_data.h"



char s_app_data_temperature[10];
char s_app_data_humidity[10];
char s_app_data_co[10];
char s_app_data_radar[10];
char s_app_data_network[10];
char s_app_data_battery[10];

int app_lcd_temperature[24];
int app_lcd_humi[24];
int app_lcd_co[24];
	
u8 app_flash_temperature_change_flag;
u8 app_flash_humi_change_flag;
u8 app_flash_co_change_flag;	

void App_Data_update(void)
{
	uint8_t me_flag;//»¥³â×÷ÓÃ
	if(strcmp((char*)s_app_data_temperature, (char*)s_abs_lora_temperature) != 0)
	{
		strcpy(s_app_data_temperature, s_abs_lora_temperature); 
		int temperature_temp = Abs_Lcd_Temperature(s_app_data_temperature);
		app_lcd_temperature[Bsp_Rtc_CurTime.hour] = temperature_temp*3+60;
		app_flash_temperature_change_flag = 1;
	}
	
	if(strcmp((char*)s_app_data_humidity, (char*)s_abs_lora_humidity) != 0)
	{
		strcpy(s_app_data_humidity, s_abs_lora_humidity);
		int humi_temp = Abs_Lcd_Humidity(s_app_data_humidity);
		app_lcd_humi[Bsp_Rtc_CurTime.hour] = humi_temp*1.5;
		app_flash_humi_change_flag = 1;
	}
	
	if(strcmp((char*)s_app_data_co, (char*)s_abs_lora_co) != 0)
	{
		strcpy(s_app_data_co, s_abs_lora_co); 
		int co_temp = Abs_Lcd_Co(s_app_data_co);
		app_lcd_co[Bsp_Rtc_CurTime.hour] = co_temp/0.6;
		app_flash_co_change_flag = 1;
		if(co_temp >= 200)
		{
			Abs_Lcd_Switch(COHIGH);
			Bsp_Led_On();
			Bsp_Beep_On();
			me_flag = 1;
		}
		else
		{
			Abs_Lcd_Switch(MAIN);
			Bsp_Led_Off();
			Bsp_Beep_Off();
		}
	}
	
	if(strcmp((char*)s_app_data_radar, (char*)s_abs_lora_radar) != 0)
	{
		
		strcpy(s_app_data_radar, s_abs_lora_radar); 
		if(strcmp((char*)s_app_data_radar, "yes") == 0)
		{
//			rt_kprintf("%s,%s\n",s_app_data_radar,s_abs_lora_radar);
			Bsp_Led_On();
			Bsp_Beep_On();
			Abs_Lcd_Switch(ALARM);
			
		}
		else if(me_flag != 1)
		{
			Bsp_Led_Off();
			Bsp_Beep_Off();
			Abs_Lcd_Switch(MAIN);
		}
	}
	
	if(strcmp((char*)s_app_data_network, (char*)s_abs_lora_network) != 0)
	{
		strcpy(s_app_data_network, s_abs_lora_network); 
		Abs_Lcd_Network(s_app_data_network);
	}
	
	if(strcmp((char*)s_app_data_battery, (char*)s_abs_lora_battery) != 0)
	{
		strcpy(s_app_data_battery, s_abs_lora_battery); 
		Abs_Lcd_Battery(s_app_data_battery);
	}
	
	if(bsp_lcd_temperature_waveform == 1)//*3+60
	{
		Bsp_Lcd_Printf("addt s0.id,0,360\xff\xff\xff");
		rt_thread_mdelay(200);
		char bsp_lcd_temperature_send[15];
		u8 i,flag;
		for(flag = 0,i = Bsp_Rtc_CurTime.hour;;i--)
		{
			
			if(i < 0 || i>23)
			{			
				i = 23;					
			}
//			rt_kprintf("%d",i);
			if(i == Bsp_Rtc_CurTime.hour)
			{
				flag++;
				if(flag == 2)
				{
					flag = 0;
					break;
				}
			}
			sprintf(bsp_lcd_temperature_send,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],
			app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],
			app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i],app_lcd_temperature[i]);
			Bsp_Lcd_Printf("%s",bsp_lcd_temperature_send);
			
		}
		rt_thread_mdelay(100);
		Bsp_Lcd_Printf("\x01\xff\xff\xff");
		bsp_lcd_temperature_waveform = 0;
	}
	
	if(bsp_lcd_humi_waveform == 1)//*1,5
	{
		Bsp_Lcd_Printf("addt s0.id,0,360\xff\xff\xff");
		rt_thread_mdelay(200);
		char bsp_lcd_humi_send[15];
		u8 i,flag;
		for(flag = 0,i = Bsp_Rtc_CurTime.hour;;i--)
		{
			
			if(i < 0 || i>23)
			{			
				i = 23;					
			}
//			rt_kprintf("%d",i);
			if(i == Bsp_Rtc_CurTime.hour)
			{
				flag++;
				if(flag == 2)
				{
					flag = 0;
					break;
				}
			}
			sprintf(bsp_lcd_humi_send,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],
			app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],
			app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i],app_lcd_humi[i]);
			Bsp_Lcd_Printf("%s",bsp_lcd_humi_send);
			
		}
		rt_thread_mdelay(100);
		Bsp_Lcd_Printf("\x01\xff\xff\xff");
		bsp_lcd_humi_waveform = 0;
	}
	
	if(bsp_lcd_co_waveform == 1)//*1,5
	{
		Bsp_Lcd_Printf("addt s0.id,0,360\xff\xff\xff");
		rt_thread_mdelay(200);
		char bsp_lcd_co_send[15];
		u8 i,flag;
		for(flag = 0,i = Bsp_Rtc_CurTime.hour;;i--)
		{
			
			if(i < 0 || i>23)
			{			
				i = 23;					
			}
			rt_kprintf("%d",i);
			if(i == Bsp_Rtc_CurTime.hour)
			{
				flag++;
				if(flag == 2)
				{
					flag = 0;
					break;
				}
			}
			sprintf(bsp_lcd_co_send,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],
			app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],
			app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],app_lcd_co[i],app_lcd_co[i]);
			Bsp_Lcd_Printf("%s",bsp_lcd_co_send);
			
		}
		rt_thread_mdelay(100);
		Bsp_Lcd_Printf("\x01\xff\xff\xff");
		bsp_lcd_co_waveform = 0;
	}
	
}


