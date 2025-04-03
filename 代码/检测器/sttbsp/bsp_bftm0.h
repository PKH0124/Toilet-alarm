#ifndef __BSP__BFTM0_H__
#define __BSP__BFTM0_H__

#include "ht32.h"

#define BFTM0_TIMER_BASE            ((long long)SystemCoreClock ) // SystemCoreClock/1000 == 1ms £¬ SystemCoreClock /1000000 == 1us

void Bsp_Bftm0_Config(void);


#endif
