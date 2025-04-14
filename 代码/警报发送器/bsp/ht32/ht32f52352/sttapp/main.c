#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include <string.h>

#include "bsp_debug.h"
#include "bsp_asr.h"
#include "bsp_y100.h"
#include "bsp_alarm.h"

#include "abs_key.h"
#include "abs_lora.h"
#include "abs_ht32led.h"
#include "abs_delay.h"

#include "app_data.h"

static rt_thread_t lora_thread_id = RT_NULL;
static rt_thread_t asr_thread_id = RT_NULL;
static rt_thread_t close_thread_id = RT_NULL;
static rt_timer_t key_time_id;

uint8_t app_close_alarm_flag;

static void Close_Thread_Enter(void *param)
{
	rt_kprintf("Close_Thread_Enter	Success\n");
	rt_thread_suspend(close_thread_id);
	rt_schedule();
	while(1)
	{
		Bsp_Y100_Printf("{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"WeChat\":{\"value\":no}}}");
		Bsp_Lora_Printf("wu\\%d\\%d\\%d\\no#",abs_lota_struction.temperature,abs_lota_struction.humidity,abs_lota_struction.co);
		rt_thread_suspend(close_thread_id);
		rt_schedule();
	}
}

static void Lora_Thread_Enter(void *param)
{
	rt_kprintf("Lora_Thread_Enter	Success\n");
	while(1)
	{
		if(s_bsp_lora_rx.overflag == 1)
		{
			rt_kprintf("%s\n",s_bsp_lora_rx.buffer);
			if(strstr((char*)s_bsp_lora_rx.buffer, "lsr"))
			{				
				App_Data_Update();				
			}
			Bsp_Lora_Clear_Struct();
		}
		rt_thread_mdelay(500);
	}
}

static void Asr_Thread_Enter(void *param)
{
	while(1)
	{
		if(bsp_asr_check_flag == 1)
		{
			Bsp_Asr_On(BSP_ASR_CHEACK2);
			rt_thread_mdelay(6000);
			Bsp_Asr_Off(BSP_ASR_CHEACK2);
			if(bsp_asr_check_flag == 1 && bsp_asr_cancel_flag == 0)
			{
				Bsp_Asr_On(BSP_ASR_SUCCESS);
				Bsp_Alarm_On(BSP_ALARM_FELL);
				bsp_asr_check_flag = 0;
				bsp_asr_cancel_flag = 0;
			}
			else
			{
				bsp_asr_check_flag = 0;
				bsp_asr_cancel_flag = 0;				
			}
		}
		else
		{
			Bsp_Alarm_Off(BSP_ALARM_FELL);
			Bsp_Asr_Off(BSP_ASR_SUCCESS);
			bsp_asr_check_flag = 0;
			bsp_asr_cancel_flag = 0;
		}
		if(app_close_alarm_flag == 1)
		{
			
		}
		rt_thread_mdelay(500);
	}
}

static void Key_Time_Interrupt(void *param)
{
	Abs_Kay_Scan(&(abs_key_station));
	if(abs_key_station.state == ABS_KEY_LONGPRESS1)
	{
		bsp_asr_check_flag = 1;
	}
	else if(abs_key_station.state == ABS_KEY_LONGPRESS5)
	{
		rt_thread_resume(close_thread_id);
	}	
}



int main(void)
{

	Bsp_Ht32led_Config();
//Bsp_Debug_Config();
	Bsp_Asr_Init();
	Bsp_Key_Config();
	Bsp_Y100_Config();
	Bsp_Alarm_Config();
	Abs_Lora_Init();
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
	
	asr_thread_id = rt_thread_create("Asr_Thread_Enter",
																		Asr_Thread_Enter,
																		NULL,
																		1024, 
																		10,
																		5);
	if(asr_thread_id == RT_NULL)
	{
		rt_kprintf("printf_thread creat error");
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
	
	rt_kprintf("printf_thread creat success");
	rt_thread_startup(lora_thread_id);
	rt_thread_startup(asr_thread_id);
	rt_thread_startup(close_thread_id);
	rt_timer_start(key_time_id);
		
    while (1)
    {
				Bsp_Ht32led_On(BSP_HT32LED1);
        Bsp_Ht32led_Off(BSP_HT32LED2);
        rt_thread_mdelay(500);
        Bsp_Ht32led_Off(BSP_HT32LED1);
        Bsp_Ht32led_On(BSP_HT32LED2);
        rt_thread_mdelay(500);
    }
}
