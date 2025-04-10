#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include "bsp_asr.h"
#include "bsp_debug.h"

uint8_t bsp_asr_check_flag,bsp_asr_cancel_flag;

/********************************************************
* Function name 				:Bsp_Ht32led_Config
* Description       :初始化Ht32led的gpio 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Asr_Gpio_Config(void)
{
//IO输出
 CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
 BSP_ASR_CLK(CK)    = 1; 
 CKCU_PeripClockConfig(CKCUClock, ENABLE);

 //GPIO_SetOutBits         (BSP_ASR_GPIO, BSP_ASR_GPIO_CO_PIN); // 初始高电平
 GPIO_ClearOutBits        (BSP_ASR_GPIO, BSP_ASR_GPIO_CO_PIN); // 初始低电平
 GPIO_DirectionConfig    (BSP_ASR_GPIO, BSP_ASR_GPIO_CO_PIN, GPIO_DIR_OUT); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 GPIO_PullResistorConfig (BSP_ASR_GPIO, BSP_ASR_GPIO_CO_PIN, GPIO_PR_DISABLE); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
 GPIO_DriveConfig        (BSP_ASR_GPIO, BSP_ASR_GPIO_CO_PIN, GPIO_DV_4MA); 	//输出电流大小 4,8,12,16

	//GPIO_SetOutBits         (BSP_ASR_GPIO, BSP_ASR_GPIO_SUCCESS_PIN); // 初始高电平
 GPIO_ClearOutBits        (BSP_ASR_GPIO, BSP_ASR_GPIO_SUCCESS_PIN); // 初始低电平
 GPIO_DirectionConfig    (BSP_ASR_GPIO, BSP_ASR_GPIO_SUCCESS_PIN, GPIO_DIR_OUT); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 GPIO_PullResistorConfig (BSP_ASR_GPIO, BSP_ASR_GPIO_SUCCESS_PIN, GPIO_PR_DISABLE); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
 GPIO_DriveConfig        (BSP_ASR_GPIO, BSP_ASR_GPIO_SUCCESS_PIN, GPIO_DV_4MA); 	//输出电流大小 4,8,12,16
 
 //GPIO_SetOutBits         (BSP_ASR_GPIO, BSP_ASR_GPIO_SUCCESS_PIN); // 初始高电平
 GPIO_ClearOutBits        (BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK2_PIN); // 初始低电平
 GPIO_DirectionConfig    (BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK2_PIN, GPIO_DIR_OUT); 	// 输入输出方向 @arg GPIO_DIR_IN  @arg GPIO_DIR_OUT
 GPIO_PullResistorConfig (BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK2_PIN, GPIO_PR_DISABLE); 	//上拉下拉电阻 @arg GPIO_PR_UP @arg GPIO_PR_DOWN @arg GPIO_PR_DISABLE
 GPIO_DriveConfig        (BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK2_PIN, GPIO_DV_4MA); 	//输出电流大小 4,8,12,16
}

void Bsp_Asr_Exit_Config(void)
{
  EXTI_InitTypeDef EXTI_InitStruct = {0};
	
	//使能PC端口的时钟
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	BSP_ASR_CLK(CK)         = 1;
	CKCUClock.Bit.AFIO       = 1;
	CKCUClock.Bit.EXTI       = 1;//串口
	CKCU_PeripClockConfig(CKCUClock, ENABLE);

	//配置端口功能为GPIO
	AFIO_GPxConfig(BSP_ASR_AFIO, BSP_ASR_GPIO_CHECK_PIN, AFIO_FUN_GPIO);//按键触发外部中断
	AFIO_GPxConfig(BSP_ASR_AFIO, BSP_ASR_GPIO_CANCEL_PIN, AFIO_FUN_GPIO);

	//配置IO口为输入模式                                                     
	GPIO_DirectionConfig(BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK_PIN, GPIO_DIR_IN);
	GPIO_DirectionConfig(BSP_ASR_GPIO, BSP_ASR_GPIO_CANCEL_PIN, GPIO_DIR_IN);

	//使能输入
	GPIO_InputConfig(BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK_PIN,ENABLE);
	GPIO_InputConfig(BSP_ASR_GPIO, BSP_ASR_GPIO_CANCEL_PIN,ENABLE);

	//配置上拉电阻
	GPIO_PullResistorConfig(BSP_ASR_GPIO, BSP_ASR_GPIO_CHECK_PIN,GPIO_PR_DOWN);
	GPIO_PullResistorConfig(BSP_ASR_GPIO, BSP_ASR_GPIO_CANCEL_PIN,GPIO_PR_DOWN);//到这里都是跟按键部分的函数是类似的
	

    //中断源配置
    AFIO_EXTISourceConfig(BSP_ASR_AFIO_CHECK_CH,BSP_ASR_AFIO_ESS);//外部中断初始化
		AFIO_EXTISourceConfig(BSP_ASR_AFIO_CANCEL_CH,BSP_ASR_AFIO_ESS);

    //中断方式配置
    EXTI_InitStruct.EXTI_Channel = BSP_ASR_CHECK_EXTI_CHANNEL;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;//禁用去抖
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;//下降沿触发
    EXTI_Init(&EXTI_InitStruct);
		
		EXTI_InitStruct.EXTI_Channel = BSP_ASR_CANCEL_EXTI_CHANNEL;//中断的通道
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;//禁用去抖
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;//下降沿触发
    EXTI_Init(&EXTI_InitStruct);

    //使能中断源
    EXTI_IntConfig(BSP_ASR_CHECK_EXTI_CHANNEL, ENABLE);
		EXTI_IntConfig(BSP_ASR_CANCEL_EXTI_CHANNEL, ENABLE);
	
		//使能中断
		NVIC_EnableIRQ(BSP_ASR_EXTI_IRQN);//exit 4-15共用一个中断向量
 
}

/********************************************************
* Function name 				:Bsp_Ht32led_On
* Description       :开灯 
* Parameter         :
* @number           选择开哪个灯 
* Return          		:无
**********************************************************/
void Bsp_Asr_On(enum BSP_ASR_FUNTION number)
{
	switch(number)
	{
		case (BSP_ASR_CO):
			GPIO_WriteOutBits(BSP_ASR_GPIO,BSP_ASR_GPIO_CO_PIN,SET);
			break;
		case (BSP_ASR_SUCCESS):
			GPIO_WriteOutBits(BSP_ASR_GPIO,BSP_ASR_GPIO_SUCCESS_PIN,SET);
			break;
		case (BSP_ASR_CHEACK2):
			GPIO_WriteOutBits(BSP_ASR_GPIO,BSP_ASR_GPIO_CHECK2_PIN,SET);
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
void Bsp_Asr_Off(enum BSP_ASR_FUNTION number)
{
	switch(number)
	{
		case (BSP_ASR_CHEACK2):
			GPIO_WriteOutBits(BSP_ASR_GPIO,BSP_ASR_GPIO_CHECK2_PIN,RESET);
			break;
		case (BSP_ASR_CO):
			GPIO_WriteOutBits(BSP_ASR_GPIO,BSP_ASR_GPIO_CO_PIN,RESET);
			break;
		case (BSP_ASR_SUCCESS):
			GPIO_WriteOutBits(BSP_ASR_GPIO,BSP_ASR_GPIO_SUCCESS_PIN,RESET);
			break;
		default:
			break;
	}
}

void Bsp_Asr_Init(void)
{
	Bsp_Asr_Gpio_Config();
	Bsp_Asr_Exit_Config();
}

//exit 4-15中断函数
void BSP_ASR_EXTI_IRQHANDLER(void)
{
  if(EXTI_GetEdgeFlag(BSP_ASR_CHECK_EXTI_CHANNEL))
  {
    EXTI_ClearEdgeFlag(BSP_ASR_CHECK_EXTI_CHANNEL);
    bsp_asr_check_flag = 1;
		bsp_asr_cancel_flag = 0;
		rt_kprintf("111");
  }
  if(EXTI_GetEdgeFlag(BSP_ASR_CANCEL_EXTI_CHANNEL))
  {
    EXTI_ClearEdgeFlag(BSP_ASR_CANCEL_EXTI_CHANNEL);
		bsp_asr_cancel_flag = 1;
  }
}
