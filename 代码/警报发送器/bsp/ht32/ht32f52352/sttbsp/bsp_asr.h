#ifndef __BSP_ASR_H__
#define __BSP_ASR_H__
 
#include "ht32.h"

#define BSP_ASR_CLK(CK)		(CKCUClock.Bit.PB)/*时钟*/

#define BSP_ASR_GPIO 	(HT_GPIOB)/*GPIO*/
#define BSP_ASR_GPIO_CHECK2_PIN	(GPIO_PIN_4)/*3秒后发送警报*/
#define BSP_ASR_GPIO_CO_PIN	(GPIO_PIN_5)/*co浓度异常*/
#define BSP_ASR_GPIO_CHECK_PIN	(GPIO_PIN_6)/*3秒后发送警报*/
#define BSP_ASR_GPIO_CANCEL_PIN	(GPIO_PIN_7)/*取消警报*/
#define BSP_ASR_GPIO_SUCCESS_PIN	(GPIO_PIN_8)/*发送成功提示*/

#define BSP_ASR_AFIO 	(GPIO_PB)/*GPIO*/
#define BSP_ASR_AFIO_ESS 	(AFIO_ESS_PB)/*GPIO*/
#define BSP_ASR_AFIO_CHECK_CH	(AFIO_EXTI_CH_6)
#define BSP_ASR_AFIO_CANCEL_CH	(AFIO_EXTI_CH_7)
#define BSP_ASR_CHECK_EXTI_CHANNEL	(EXTI_CHANNEL_6)
#define BSP_ASR_CANCEL_EXTI_CHANNEL	(EXTI_CHANNEL_7)

#define BSP_ASR_EXTI_IRQN (EXTI4_15_IRQn)
#define BSP_ASR_EXTI_IRQHANDLER (EXTI4_15_IRQHandler)

/*枚举灯的编号*/
enum BSP_ASR_FUNTION{
	BSP_ASR_CHEACK2,
	BSP_ASR_CO,
	BSP_ASR_SUCCESS,
};

extern uint8_t bsp_asr_check_flag,bsp_asr_cancel_flag;

void Bsp_Asr_Config(void);

void Bsp_Asr_Init(void);
void Bsp_Asr_On(enum BSP_ASR_FUNTION number);
void Bsp_Asr_Off(enum BSP_ASR_FUNTION number);

#endif
