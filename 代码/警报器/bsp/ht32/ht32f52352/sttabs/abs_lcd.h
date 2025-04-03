#ifndef __ABS_LCD_H__
#define __ABS_LCD_H__

#include "bsp_lcd.h"

extern char s_abs_lcd_temperature[10];
extern char s_abs_lcd_humidity[10];
extern char s_abs_lcd_co[10];
extern char s_abs_lcd_network[10];
extern char s_abs_lcd_battery[10];

enum ABS_LCD_STATE{
	START,
	MAIN,
	ALARM,
	COHIGH
}; 

void Abs_Lcd_Init(void);
void Abs_Lcd_Switch(enum ABS_LCD_STATE state);
int Abs_Lcd_Temperature(char value[]);
int Abs_Lcd_Humidity(char value[]);
int Abs_Lcd_Co(char value[]);
void Abs_Lcd_Network(char value[]);
void Abs_Lcd_Battery(char value[]);
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 #endif
