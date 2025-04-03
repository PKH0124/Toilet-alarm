#include "abs_lcd.h"
#include <stdio.h>
#include <string.h>

enum ABS_LCD_STATE abs_lcd_station;

void Abs_Lcd_Init(void)
{
	Bsp_Lcd_Config();
}

void Abs_Lcd_Switch(enum ABS_LCD_STATE state)
{
	switch(state)
	{
		case (START):
		{
			Bsp_Lcd_Printf("page start\xff\xff\xff");
			break;
		}
		case (MAIN):
		{
			Bsp_Lcd_Printf("page main\xff\xff\xff");
			
			break;
		}
		case (ALARM):
		{
			Bsp_Lcd_Printf("page alarm\xff\xff\xff");
			break;
		}
		case (COHIGH):
		{
			Bsp_Lcd_Printf("page cohigh\xff\xff\xff");
			break;
		}
		default:
		{
			break;
		}
	}
}

int Abs_Lcd_Temperature(char value[])
{
	int temperature_temp;
	Bsp_Lcd_Printf("main.t4.txt=\"%s℃\r\"\xff\xff\xff",value);
	temperature_temp = atoi(value);
	return temperature_temp;
}

int Abs_Lcd_Humidity(char value[])
{
	int humi_temp;
	Bsp_Lcd_Printf("main.t5.txt=\"%s%%\"\xff\xff\xff",value);
	humi_temp = atoi(value);
	return humi_temp;
}

int Abs_Lcd_Co(char value[])
{
	int co_temp;
	Bsp_Lcd_Printf("main.t3.txt=\"%sppm\"\xff\xff\xff",value);
	co_temp = atoi(value);
	return co_temp;
}

void Abs_Lcd_Network(char value[])
{	
	if(strcmp(value,"yes") == 0)
	{
		Bsp_Lcd_Printf("main.t6.txt=\"网络已连接  \"\xff\xff\xff",value);
		Bsp_Lcd_Printf("main.t6.pco=00000\xff\xff\xff");
	}
	if(strcmp(value,"no") == 0)
	{
		Bsp_Lcd_Printf("main.t6.txt=\"网络未连接 \"\xff\xff\xff",value);
		Bsp_Lcd_Printf("main.t6.pco=51200\xff\xff\xff");
	}
}

void Abs_Lcd_Battery(char value[])
{
	int battery_temp;
	Bsp_Lcd_Printf("main.t7.txt=\"%s%%\"\xff\xff\xff",value);
	Bsp_Lcd_Printf("main.j0.val=%s\xff\xff\xff",value);
	battery_temp = atoi(value);
	if(battery_temp <= 20)
	{
		Bsp_Lcd_Printf("main.t7.pco=51200\xff\xff\xff");
		Bsp_Lcd_Printf("main.j0.pco=51200\xff\xff\xff");
	}
	else
	{
		Bsp_Lcd_Printf("main.t7.pco=00000\xff\xff\xff");
		Bsp_Lcd_Printf("main.j0.pco=2032\xff\xff\xff");
	}
}
