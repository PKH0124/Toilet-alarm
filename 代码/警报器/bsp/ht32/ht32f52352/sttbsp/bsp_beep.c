#include "bsp_beep.h"


/********************************************************
* Function name 				:Bsp_Ht32led_Config
* Description       :初始化Ht32led的gpio 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Beep_Config(void)
{
 CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
 BSP_BEEP_CLK(CK)    = 1; 
 CKCU_PeripClockConfig(CKCUClock, ENABLE);

 //GPIO_SetOutBits         (BSP_BEEP_GPIO, BSP_BEEP1_GPIO_PIN); // 初始高电平
 GPIO_ClearOutBits        (BSP_BEEP_GPIO, BSP_BEEP1_GPIO_PIN); // 初始低电平
 GPIO_DirectionConfig    (BSP_BEEP_GPIO, BSP_BEEP1_GPIO_PIN, GPIO_DIR_OUT); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 GPIO_PullResistorConfig (BSP_BEEP_GPIO, BSP_BEEP1_GPIO_PIN, GPIO_PR_DISABLE); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
 GPIO_DriveConfig        (BSP_BEEP_GPIO, BSP_BEEP1_GPIO_PIN, GPIO_DV_4MA); 	//输出电流大小 4,8,12,16

}

/********************************************************
* Function name 				:Bsp_Ht32led_On
* Description       :开灯 
* Parameter         :
* @number           选择开哪个灯 
* Return          		:无
**********************************************************/
void Bsp_Beep_On(void)
{
	GPIO_WriteOutBits(BSP_BEEP_GPIO,BSP_BEEP1_GPIO_PIN,SET);
}

/********************************************************
* Function name 				:Bsp_Ht32led_Off
* Description       :关灯 
* Parameter         :
* @number           选择关哪个灯 
* Return          		:无
**********************************************************/
void Bsp_Beep_Off(void)
{
	GPIO_WriteOutBits(BSP_BEEP_GPIO,BSP_BEEP1_GPIO_PIN,RESET);
}
