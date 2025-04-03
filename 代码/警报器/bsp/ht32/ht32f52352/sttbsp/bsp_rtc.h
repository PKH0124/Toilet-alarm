#ifndef __BSP_RTC_H__
#define __BSP_RTC_H__
 
#include "ht32.h"


typedef struct
{
  u32 year;
  u32 month;
  u32 day;
  u32 hour;
  u32 minute;
  u32 second;
}BSP_RTC_TIME;

extern uint8_t Bsp_Rtc_Second_Flag;

extern BSP_RTC_TIME Bsp_Rtc_DateTime, Bsp_Rtc_CurTime;

void Bsp_Rtc_Configuration(void);
u8 Bsp_Rtc_Get(BSP_RTC_TIME* CurrentTime);
u8 Bsp_Rtc_Adjust(BSP_RTC_TIME* AdjustTime);

void Bsp_Rtc_Init(void);

#endif
