#include "abs_delay.h"

static u8  fac_us=0;//us延时倍乘数

void Abs_Delay_init(void)	 
{
	SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);	//选择外部时钟  HCLK/8=6M
	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8  
}								    

/********************************************************
* Function name 				:Abs_Delay_Us
* Description       :延时 
* Parameter         :
* @ms           				延时多少微秒 
* Return          		:无
**********************************************************/
void Abs_Delay_Us(uint32_t nus)
{
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
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
	while(ms--)
	Abs_Delay_Us(1000);
}


