#include "abs_delay.h"

/********************************************************
* Function name 				:Abs_Delay_Us
* Description       :延时 
* Parameter         :
* @ms           				延时多少微秒 
* Return          		:无
**********************************************************/
void Abs_Delay_Us(uint32_t us)
{
    uint32_t i;
    
    /* SYSTICK configuration */
    SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);       // 即默认选择了外部参考时钟
    SYSTICK_SetReloadValue(SystemCoreClock / 8 / 1000000); // (CK_SYS/8/1000000) = 1us 
    SYSTICK_IntConfig(DISABLE);                         // 不开启中断
 
    /* 打开SysTick计数器 */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
    SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
 
    for( i = 0;i < us;i++ )
    {
        while( !( (SysTick->CTRL) & (1<<16) ) ); 
    }
 
    /* 关闭SysTick计数器 */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);
    /* 复位SysTick计数器 */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
}

/********************************************************
* Function name 				:Abs_Delay_Ms
* Description       :延时 
* Parameter         :
* @ms           				延时多少毫秒 
* Return          		:无
**********************************************************/
void Abs_Delay_Ms(uint32_t ms)
{
    uint32_t i;
    
    /* SYSTICK configuration */
    SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);       // 即默认选择了外部参考时钟
    SYSTICK_SetReloadValue(SystemCoreClock / 8 / 1000); // (CK_SYS/8/1000) = 1ms 
    SYSTICK_IntConfig(DISABLE);                         // 不开启中断
 
    /* 打开SysTick计数器 */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
    SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
    
    for( i = 0;i < ms;i++ )
    {
		while( !( (SysTick->CTRL) & (1<<16) ) ); 
 
    }
 
    /* 关闭SysTick计数器 */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);
    /* 复位SysTick计数器 */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
}


