#include "bsp_alarm.h"


/********************************************************
* Function name 				:Bsp_Ht32led_Config
* Description       :初始化Ht32led的gpio 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Alarm_Config(void)
{
 CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
 BSP_ALARM_CLK(CK)    = 1; 
 CKCU_PeripClockConfig(CKCUClock, ENABLE);

 //GPIO_SetOutBits         (BSP_ALARM_GPIO, BSP_ALARM_GPIO_FELL_PIN); // 初始高电平
 GPIO_ClearOutBits        (BSP_ALARM_GPIO, BSP_ALARM_GPIO_FELL_PIN); // 初始低电平
 GPIO_DirectionConfig    (BSP_ALARM_GPIO, BSP_ALARM_GPIO_FELL_PIN, GPIO_DIR_OUT); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 GPIO_PullResistorConfig (BSP_ALARM_GPIO, BSP_ALARM_GPIO_FELL_PIN, GPIO_PR_DISABLE); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
 GPIO_DriveConfig        (BSP_ALARM_GPIO, BSP_ALARM_GPIO_FELL_PIN, GPIO_DV_4MA); 	//输出电流大小 4,8,12,16

	//GPIO_SetOutBits         (BSP_ALARM_GPIO, BSP_ALARM_GPIO_CO_PIN); // 初始高电平
 GPIO_ClearOutBits        (BSP_ALARM_GPIO, BSP_ALARM_GPIO_CO_PIN); // 初始低电平
 GPIO_DirectionConfig    (BSP_ALARM_GPIO, BSP_ALARM_GPIO_CO_PIN, GPIO_DIR_OUT); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 GPIO_PullResistorConfig (BSP_ALARM_GPIO, BSP_ALARM_GPIO_CO_PIN, GPIO_PR_DISABLE); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
 GPIO_DriveConfig        (BSP_ALARM_GPIO, BSP_ALARM_GPIO_CO_PIN, GPIO_DV_4MA); 	//输出电流大小 4,8,12,16

}

/********************************************************
* Function name 				:Bsp_Ht32led_On
* Description       :开灯 
* Parameter         :
* @number           选择开哪个灯 
* Return          		:无
**********************************************************/
void Bsp_Alarm_On(enum BSP_ALARM_NUMBER number)
{
	switch(number)
	{
		case (BSP_ALARM_FELL):
			GPIO_WriteOutBits(BSP_ALARM_GPIO,BSP_ALARM_GPIO_FELL_PIN,SET);
			break;
		case (BSP_ALARM_CO):
			GPIO_WriteOutBits(BSP_ALARM_GPIO,BSP_ALARM_GPIO_CO_PIN,SET);
			break;
		default:
			break;
	}
}

/********************************************************
* Function name 				:Bsp_Ht32led_Off
* Description       :关灯 
* Parameter         :
* @number           选择关哪个灯 
* Return          		:无
**********************************************************/
void Bsp_Alarm_Off(enum BSP_ALARM_NUMBER number)
{
	switch(number)
	{
		case (BSP_ALARM_FELL):
			GPIO_WriteOutBits(BSP_ALARM_GPIO,BSP_ALARM_GPIO_FELL_PIN,RESET);
			break;
		case (BSP_ALARM_CO):
			GPIO_WriteOutBits(BSP_ALARM_GPIO,BSP_ALARM_GPIO_CO_PIN,RESET);
			break;
		default:
			break;
	}
}
