#include <stdio.h>
#include <string.h>

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include "abs_lora.h"
#include	"bsp_debug.h"
#include "abs_delay.h"


ABS_LORA_STRUCT abs_lota_struction;

/********************************************************
* Function name 				:Abs_Lora_Wakeup
* Description       :唤醒Lora 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/
int32_t Abs_Lora_Wakeup(void)  
{
	int32_t ret = 1;
	ret = Bsp_Lora_Send_Cmd("Lora","LoRa Start!",300);
	if(ret == 0)
	{
		Bsp_Lora_Clear_Struct();
		return 0;
	}
	return 1;
}

/********************************************************
* Function name 				:Abs_Lora_EnterAT
* Description       :进入AT指令模式 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/ 
int32_t Abs_Lora_EnterAT(void)  
{
	int32_t ret = 1;
	ret = Bsp_Lora_Send_Cmd("+++","a",300);
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("a","+OK",300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+E=OFF\r\n","OK",300);
	}
	if(ret == 0)
	{
		Bsp_Lora_Clear_Struct();
		return 0;
	}
	return 1;
}

/********************************************************
* Function name 				:Abs_Lora_SetAT
* Description       :配置Lora为不组网的主从的WU模式 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/ 
/********************************************************
* Function name 				:Abs_Lora_SetAT
* Description       :配置Lora为不组网的主从的WU模式 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/ 
int32_t Abs_Lora_SetAT(void)
{
	int32_t ret = 1;
	ret = Bsp_Lora_Send_Cmd("AT+LORAPROT=NODE\r\n","OK",300);
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PROTSEL=1\r\n","OK",300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+WMODE=TRANS\r\n","OK",300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PMODE=RUN\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+SPD=10\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+CH=4800\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PWR=22\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+ADDR=62288\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+FEC=1\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+LBT=OFF\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+UARTFT=10\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+UART=115200,8,1,NONE,NFC\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+RESEND=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+FDMODE=ON\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+TXCH=4700\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+SENDOK=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+MTU=240\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+DATAMODE=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+RFTO=60\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PFLAG=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+RELAY=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+Z\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		Bsp_Lora_Clear_Struct();
		return 0;
	}
	return 1;
	
}

/********************************************************
* Function name 				:Abs_Lora_Init
* Description       :Lora初始化 
* Parameter         :void
* Return          		:无
**********************************************************/
void Abs_Lora_Init(void)
{
	int32_t ret = 1;
	Bsp_Lora_Usart_Config();
	Bsp_Lora_Res_Config();
	Bsp_Lora_Res();
	ret = Abs_Lora_Wakeup();
	if(ret == 0)
	{
		ret = Abs_Lora_EnterAT();
	}
	if(ret == 0)
	{
		Abs_Lora_SetAT();
	}
}

void Abs_Lora_Getdata(BSP_LORA_USART struction)
{
	/****温度****/
	char s_abs_lora_temperature[10];
	char *temperature_start = strstr(s_bsp_lora_rx.buffer, "lsr\\") + 4;
	char *temperature_end = strchr(temperature_start, '\\');
	size_t temperature_length = temperature_end - temperature_start;
	strncpy(s_abs_lora_temperature, temperature_start, temperature_length); 
	s_abs_lora_temperature[temperature_length] = '\0';
	abs_lota_struction.temperature = atoi(s_abs_lora_temperature);
	
	
	/****湿度****/
	char s_abs_lora_humidity[10];
	char *humidity_start = strstr(temperature_end, "\\") + 1;
	char *humidity_end = strchr(humidity_start, '\\');
	size_t humidity_length = humidity_end - humidity_start;
	strncpy(s_abs_lora_humidity, humidity_start, humidity_length); 
	s_abs_lora_humidity[humidity_length] = '\0'; 
	abs_lota_struction.humidity = atoi(s_abs_lora_humidity);
	
	/****co****/
	char s_abs_lora_co[10];
	char *co_start = strstr(humidity_end, "\\") + 1;
	char *co_end = strchr(co_start, '\\');
	size_t co_length = co_end - co_start;
	strncpy(s_abs_lora_co, co_start, co_length); 
	s_abs_lora_co[co_length] = '\0'; 
	abs_lota_struction.co = atoi(s_abs_lora_co);
	
	/****雷达****/
	char *radar_start = strstr(co_end, "\\") + 1;
	char *radar_end = strchr(radar_start, '#');
	size_t radar_length = radar_end - radar_start;
	strncpy(abs_lota_struction.radar, radar_start, radar_length); 
	abs_lota_struction.radar[radar_length] = '\0'; 	
	
//	rt_kprintf("%d,%d,%d,%s\n",abs_lota_struction.temperature,abs_lota_struction.humidity,abs_lota_struction.co,abs_lota_struction.radar);
	
}


