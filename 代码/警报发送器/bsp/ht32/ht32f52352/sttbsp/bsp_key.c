#include "bsp_key.h"


/********************************************************
* Function name 				:Bsp_Ht32led_Config
* Description       :初始化Ht32led的gpio 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Key_Config(void)
{
 CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
 BSP_KEY_CLK(CK)    = 1; 
 CKCUClock.Bit.AFIO = 1;
 CKCU_PeripClockConfig(CKCUClock, ENABLE);
 
 GPIO_DirectionConfig    (BSP_KEY_GPIO, BSP_KEY_GPIO_PIN, GPIO_DIR_IN); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 
 GPIO_InputConfig					(BSP_KEY_GPIO, BSP_KEY_GPIO_PIN, ENABLE);
 
 GPIO_PullResistorConfig (BSP_KEY_GPIO, BSP_KEY_GPIO_PIN, GPIO_PR_UP); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
}

/********************************************************
* Function name 				:GPIO_ReadInBit
* Description       :开灯 
* Parameter         :
* @number           选择开哪个灯 
* Return          		:无
**********************************************************/
uint8_t Bsp_Key_Read(void)
{
	uint8_t data = GPIO_ReadInBit(BSP_KEY_GPIO,BSP_KEY_GPIO_PIN);;
	return	data;
}


