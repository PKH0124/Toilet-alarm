#include "bsp_rtc.h"

u8 Day_Per_Month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint8_t Bsp_Rtc_Second_Flag = 0;
BSP_RTC_TIME Bsp_Rtc_CurTime;

void Bsp_Rtc_Init() 
{	
  //使能备份域时钟 等待可以被操作
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.BKP        = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
  if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
  {
    while (1);
  }

  NVIC_EnableIRQ(RTC_IRQn);
	
	//读取备份域寄存器 判断RTC是否已经配置
	if (PWRCU_ReadBackupRegister((PWRCU_BAKREG_Enum) PWRCU_BAKREG_0) != 0xAA55AA55)
	{
	// RTC 配置
	Bsp_Rtc_Configuration();	  

	//设置时间
	Bsp_Rtc_CurTime.year   = 2024;
	Bsp_Rtc_CurTime.month  = 4;
	Bsp_Rtc_CurTime.day    = 29;
	Bsp_Rtc_CurTime.hour   = 18;
	Bsp_Rtc_CurTime.minute = 0;
	Bsp_Rtc_CurTime.second = 0;
		
	Bsp_Rtc_Adjust(&Bsp_Rtc_CurTime);
	//使能 RTC 
	RTC_Cmd(ENABLE);

	PWRCU_WriteBackupRegister((PWRCU_BAKREG_Enum) PWRCU_BAKREG_0, 0xAA55AA55);
	}
 
}


//判断是否是闰年
bool Bsp_Rtc_IsLeapYear(u32 year)
{
  if (((year % 4 == 0) && (year % 100 != 0) ) || (year % 400 == 0) )
    return TRUE;
  else
    return FALSE;
}


//调节时间
u8 Bsp_Rtc_Adjust(BSP_RTC_TIME* AdjustTime)
{
  u32 i, temp, secsum = 0;

  temp = AdjustTime->year - 1;
  for (i = 0; i < (AdjustTime->year - 2014); i++)
  {
    if (Bsp_Rtc_IsLeapYear(temp--) == TRUE)
    {
      secsum += (366 * 86400);
    }
    else
    {
      secsum += (365 * 86400);
    }
  }

  temp = 1;
  for (i = 0; i < (AdjustTime->month - 1); i++)
  {
    if (temp == 2)
    {
      if (Bsp_Rtc_IsLeapYear(AdjustTime->year) == TRUE)
        secsum += (29 * 86400);
      else
        secsum += (28 * 86400);
    }
    else
    {
      secsum += (Day_Per_Month[temp] * 86400);
    }
    temp++;
  }

  secsum += ((AdjustTime->day - 1) * 86400);
  secsum += (AdjustTime->hour * 3600 );
  secsum += (AdjustTime->minute * 60);
  secsum += (AdjustTime->second);

  PWRCU_WriteBackupRegister((PWRCU_BAKREG_Enum) PWRCU_BAKREG_1, secsum);
  if (PWRCU_ReadBackupRegister((PWRCU_BAKREG_Enum) PWRCU_BAKREG_1) != secsum)
  {
    return 0;
  }

  return 1;
}


//计算当前时间
u8 Bsp_Rtc_Get(BSP_RTC_TIME* CurrentTime)
{
  u32 i, secsum = 0, temp = 0;

  secsum = PWRCU_ReadBackupRegister((PWRCU_BAKREG_Enum) PWRCU_BAKREG_1);
  secsum += RTC_GetCounter();

  temp = 0;
  while (secsum >= (365 * 86400))
  {
    if (Bsp_Rtc_IsLeapYear(2014 + temp))
    {
      if (secsum >= (366 * 86400))
      {
        temp++;
        secsum -= (366 * 86400);
      }
      else
      {
        break;
      }
    }
    else
    {
      temp++;
      secsum -= (365 * 86400);
    }
  }
  CurrentTime->year = 2014 + temp;

  for (i = 1; i <= 12; i++)
  {
    if (secsum >= (Day_Per_Month[i] * 86400))
    {
      if (i == 2)  // February
      {
        if (Bsp_Rtc_IsLeapYear(CurrentTime->year))
        {
          if (secsum >= (29 * 86400))
            secsum -= (29 * 86400);
          else
            break;
        }
        else
        {
          secsum -= (28 * 86400);
        }
      }
      else
      {
        secsum -= (Day_Per_Month[i] * 86400);
      }
    }
    else
    {
      break;
    }
  }
  CurrentTime->month = i;

  CurrentTime->day = secsum / 86400 + 1;
  secsum -= ((CurrentTime->day - 1) * 86400);

  CurrentTime->hour = secsum / 3600;
  CurrentTime->minute = (secsum % 3600) / 60;
  CurrentTime->second = (secsum % 3600) % 60;

  return 1;
}


void Bsp_Rtc_Configuration(void)
{
  
	PWRCU_DeInit();
	//配置外部32.768k振荡器
	RTC_LSESMConfig(RTC_LSESM_NORMAL);
	RTC_LSECmd(ENABLE);
	while (CKCU_GetClockReadyStatus(CKCU_FLAG_LSERDY) == RESET);
	RTC_ClockSourceConfig(RTC_SRC_LSE);


	RTC_IntConfig(RTC_INT_CSEC, ENABLE);
	RTC_SetPrescaler(RTC_RPRE_32768);

															
	RTC_CMPCLRCmd(ENABLE);
}

//RTC中断
void RTC_IRQHandler(void)
{
  u8 bFlags;

  bFlags = RTC_GetFlagStatus();
  if (bFlags & 0x1)
  {
    //1s更新标志位
    Bsp_Rtc_Second_Flag = 1;
  }

}




