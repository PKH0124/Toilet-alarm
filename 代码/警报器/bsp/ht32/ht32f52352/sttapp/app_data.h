#ifndef __APP_DATA_H__
#define __APP_DATA_H__

void App_Data_update(void);

extern int app_lcd_temperature[24];
extern int app_lcd_humi[24];
extern int app_lcd_co[24];

extern u8 app_flash_temperature_change_flag;
extern u8 app_flash_humi_change_flag;
extern u8 app_flash_co_change_flag;	



#endif
