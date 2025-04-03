#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"


#include <string.h>


#include "bsp_debug.h"
#include "bsp_beep.h"
#include "bsp_led.h"
#include "bsp_rtc.h"

#include "abs_lcd.h"
#include "abs_key.h"
#include "abs_lora.h"
#include "abs_ht32led.h"
#include "abs_delay.h"

#include "app_data.h"

#include "easyflash.h"


static rt_thread_t lora_thread_id = RT_NULL;
static rt_thread_t lcd_thread_id = RT_NULL;
static rt_thread_t flash_thread_id = RT_NULL;
static rt_timer_t key_time_id;


static void Lora_Thread_Enter(void *param)
{
	rt_kprintf("Lora_Thread_Enter	Success\n");
	while(1)
	{
		if(s_bsp_lora_rx.overflag == 1)
		{
			if(strstr((char*)s_bsp_lora_rx.buffer, "wu"))
			{
				Abs_Lora_Getdata(s_bsp_lora_rx);
				rt_kprintf("%s,%s,%s,%s,%s\n",s_abs_lora_temperature,s_abs_lora_humidity,s_abs_lora_co,s_abs_lora_network,s_abs_lora_battery);
			}
			Bsp_Lora_Clear_Struct();
		}
		rt_thread_mdelay(500);
	}
}


static void Lcd_Thread_Enter(void *param)
{
	rt_kprintf("Lcd_Thread_Enter Success\n");
	while(1)
	{
		App_Data_update();
		rt_thread_mdelay(500);
	}
}

static void Flash_Thread_Enter(void *param)
{
	rt_kprintf("Flash_Thread_Enter Success\n");
	if(easyflash_init() == EF_NO_ERR)                         // 初始化成功
  {
    ef_get_env_blob("app_lcd_temperature", app_lcd_temperature, 96, NULL);  // 读出reboot_time的值
		ef_get_env_blob("app_lcd_humi", app_lcd_humi, 96, NULL);  // 读出reboot_time的值
		ef_get_env_blob("app_lcd_co", app_lcd_co, 96, NULL);  // 读出reboot_time的值		
  }
	while(1)
	{
		if(app_flash_temperature_change_flag == 1)
		{
			ef_set_env_blob("app_lcd_temperature",app_lcd_temperature,96);
		}
		if(app_flash_humi_change_flag == 1)
		{
			ef_set_env_blob("app_lcd_humi",app_lcd_humi,96);
		}
		if(app_flash_co_change_flag == 1)
		{
			ef_set_env_blob("app_lcd_co",app_lcd_co,96);
		}
		
		rt_thread_mdelay(500);
	}
}

static void Key_Time_Interrupt(void *param)
{
	Abs_Kay_Scan(&(abs_key_station));
	if(abs_key_station.state == ABS_KEY_LONGPRESS1)
	{
		Abs_Lcd_Switch(MAIN);
		Bsp_Beep_Off();
		Bsp_Led_Off();
	}	
}


int main(void)
{

  if(easyflash_init() == EF_NO_ERR)  		// 初始化成功
  {
//    ef_get_env_blob("RTC_TIME", &Bsp_Rtc_CurTime, 8, NULL);  // 读出reboot_time的值
  }

	Bsp_Ht32led_Config();
	rt_thread_mdelay(500);
	Abs_Lcd_Init();
	Bsp_Debug_Config();
	Abs_Lora_Init();
	Bsp_Beep_Config();
	Bsp_Led_Config();
	Bsp_Key_Config();
	Bsp_Rtc_Init();
	Abs_Lcd_Switch(MAIN);
			
  
  flash_thread_id = rt_thread_create("Flash_Thread_Enter",
																		Flash_Thread_Enter,
																		NULL,
																		1024, 
																		9,
																		5);
	if(flash_thread_id == RT_NULL)
	{
		rt_kprintf("flash_thread creat error\n");
		return -1;
	}
	rt_thread_startup(flash_thread_id);
	
	lora_thread_id = rt_thread_create("Lora_Thread_Enter",
																			Lora_Thread_Enter,
																			NULL,
																			3072, 
																			10,
																			5);	
	if(lora_thread_id == RT_NULL)
	{
		rt_kprintf("lora_thread creat error\n");
		return -1;
	}
	
	lcd_thread_id = rt_thread_create("Lcd_Thread_Enter",
																		Lcd_Thread_Enter,
																		NULL,
																		2048, 
																		10,
																		50);
	if(lcd_thread_id == RT_NULL)
	{
		rt_kprintf("lcd_thread creat error\n");
		return -1;
	}
	
	key_time_id = rt_timer_create("Key_Time_Interrupt", Key_Time_Interrupt,
																 RT_NULL, 20,
																 RT_TIMER_FLAG_PERIODIC);
  if (key_time_id == RT_NULL)
	{
		rt_kprintf("rt_timer_create creat error\n");
		return -1;
	}
	
	rt_kprintf("thread creat success\n");
	rt_thread_startup(lora_thread_id);
	rt_thread_startup(lcd_thread_id);
	rt_timer_start(key_time_id);
	while (1)
	{
			Bsp_Ht32led_On(BSP_HT32LED1);
			Bsp_Ht32led_Off(BSP_HT32LED2);
			rt_thread_mdelay(500);
			Bsp_Ht32led_Off(BSP_HT32LED1);
			Bsp_Ht32led_On(BSP_HT32LED2);
			rt_thread_mdelay(500);
			Bsp_Rtc_Get(&Bsp_Rtc_CurTime);
			//rt_kprintf("%d-%d-%d %d:%d:%d\n",Bsp_Rtc_CurTime.year,Bsp_Rtc_CurTime.month,Bsp_Rtc_CurTime.day,Bsp_Rtc_CurTime.hour,Bsp_Rtc_CurTime.minute,Bsp_Rtc_CurTime.second);
	}
}
