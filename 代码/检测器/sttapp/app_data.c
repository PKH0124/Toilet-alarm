#include "app_data.h"
#include "bsp_DHT11.h"  
#include "bsp_MQ7.h"  
#include "bsp_debug.h"
#include "bsp_LD2410B.h"

#include <stdio.h>    
#include <string.h>


typedef struct APP_DATA_STRUCT{
	uint8_t temp;
	uint8_t humi;
	uint16_t ppm;
	char radar[3];
	
}APP_DATA_STRUCT;

APP_DATA_STRUCT app_data_now,app_data_last;

void App_Data_collect(void)
{
	Bsp_DHT11_Read_Data(&(app_data_now.temp),&(app_data_now.humi));
	app_data_now.ppm = (uint16_t)Bsp_MQ7_ReadPPM();
	if(bsp_ld24108_target_state_2 >= 50)
	{
		app_data_now.radar[0]='y';
		app_data_now.radar[1]='e';
		app_data_now.radar[2]='s';			
	}
	else
	{
		app_data_now.radar[0]='n';
		app_data_now.radar[1]='o';
		app_data_now.radar[2]='\0';
	}
	if(app_data_now.temp != app_data_last.temp || app_data_now.humi != app_data_last.humi || app_data_now.ppm - app_data_last.ppm > 2 || app_data_now.ppm - app_data_last.ppm < -2|| memcmp(app_data_now.radar, app_data_last.radar, 3))  
	{
		
		app_data_last.temp = app_data_now.temp ; 
		app_data_last.humi = app_data_now.humi ; 
		app_data_last.ppm = app_data_now.ppm;
		sprintf(app_data_last.radar,"%s",app_data_now.radar);
		
		Bsp_Debug_Printf("lsr\\%d\\%d\\%d\\%s#\n",app_data_now.temp,app_data_now.humi,app_data_now.ppm,app_data_now.radar);
	}
	
}
