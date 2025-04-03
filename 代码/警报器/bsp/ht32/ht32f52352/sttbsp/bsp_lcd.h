#ifndef __BSP_LCD_H__
#define __BSP_LCD_H__
 
#include "ht32.h"

#define BSP_LCD_MAX_LEN (200)/*??????*/

#define BSP_LCD (HT_UART1)

#define BSP_LCD_CLK(CK) (CKCUClock.Bit.UART1)

#define BSP_LCD_AFIO 	(GPIO_PC)
#define BSP_LCD_AFIO_TX	(AFIO_PIN_12)
#define BSP_LCD_AFIO_RX	(AFIO_PIN_13)

#define BSP_LCD_IRQN (UART1_IRQn)
#define BSP_LCD_IRQHANDLER (UART1_IRQHandler)/*??????*/

extern u8 bsp_lcd_temperature_waveform,bsp_lcd_humi_waveform,bsp_lcd_co_waveform;

void Bsp_Lcd_Config(void);
void Bsp_Lcd_Sendbyte(uint8_t Data);
void Bsp_Lcd_SendArray(uint8_t *array,u8 num);
void Bsp_Lcd_SendStr(char *str);
void Bsp_Lcd_Printf(char* fmt,...);

 



#endif
