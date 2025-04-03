#include "ht32f5xxxx_01.h"              // Device header  
#include "bsp_debug.h"        

#include "bsp_bftm0.h"
#include "bsp_LD2410B.h"
 
void Bsp_Bftm0_Config(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.BFTM0      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
 
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_SetCompare(HT_BFTM0, BFTM0_TIMER_BASE); 
 
  BFTM_ClearFlag(HT_BFTM0); // 清除中断标志位     
  BFTM_IntConfig(HT_BFTM0, ENABLE); // 开启 BFTM interrupt
  NVIC_EnableIRQ(BFTM0_IRQn);   
 
  BFTM_EnaCmd(HT_BFTM0, ENABLE); // 开启基础定时器BFTM
}


