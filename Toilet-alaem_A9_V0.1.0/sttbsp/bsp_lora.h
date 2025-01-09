#ifndef __BSP_LORA_H__
#define __BSP_LORA_H__
 
#include "ht32.h"

#define BSP_LORA_MAX_LEN (200)/*最大缓存长度*/

#define BSP_LORA (HT_USART0)

#define BSP_LORA_CLK(CK) (CKCUClock.Bit.USART0)

#define BSP_LORA_AFIO 	(GPIO_PA)
#define BSP_LORA_AFIO_TX	(AFIO_PIN_2)
#define BSP_LORA_AFIO_RX	(AFIO_PIN_3)

#define BSP_LORA_GPIO 	(HT_GPIOC)
#define	BSP_LORA_GPIO_RES	(GPIO_PIN_8)

#define BSP_LORA_IRQHANDLER (USART0_IRQHandler)/*接收中断函数*/
#define BSP_LORA_IRQN (USART0_IRQn)

/*lora中断缓存结构体*/
typedef struct BSP_LORA_USART {
    char buffer[BSP_LORA_MAX_LEN];
    int length;
}BSP_LORA_USART;

void Bsp_Lora_Res_Config(void);
void Bsp_Lora_Res(void);
void Bsp_Lora_Usart_Config(void);
void Bsp_Lora_Sendbyte(char Data);
void Bsp_Lora_SendArray(char array[],uint8_t num);
void Bsp_Lora_SendStr(char *str);
void Bsp_Lora_Printf(char* fmt,...);
void Bsp_Lora_Clear_Struct(void);
int32_t Bsp_Lora_Send_Cmd(char* cmd, char* reply, uint32_t wait);


#endif
