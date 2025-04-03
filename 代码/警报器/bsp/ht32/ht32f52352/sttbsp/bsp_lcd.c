#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include "bsp_lcd.h"
#include "bsp_debug.h"
#include "abs_ht32led.h"

u8 bsp_lcd_temperature_waveform = 0,bsp_lcd_humi_waveform = 0,bsp_lcd_co_waveform = 0;

/********************************************************
* Function name 				:Bsp_Debug_Config
* Description       :???Debug?usart0 
* Parameter         :? 
* Return          		:?
**********************************************************/
void Bsp_Lcd_Config(void)
{
  USART_InitTypeDef USART_InitStruct; 
  
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  BSP_LCD_CLK(CK)   = 1;
  CKCUClock.Bit.AFIO     = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
		
  AFIO_GPxConfig(BSP_LCD_AFIO, BSP_LCD_AFIO_TX, AFIO_MODE_6); // ??????  AFIO_FUN_USART_UART
  AFIO_GPxConfig(BSP_LCD_AFIO, BSP_LCD_AFIO_RX, AFIO_MODE_6);  
 
      
  USART_InitStruct.USART_BaudRate = 115200;  // ???
  USART_InitStruct.USART_WordLength = USART_WORDLENGTH_8B; // ????
  USART_InitStruct.USART_StopBits = USART_STOPBITS_1; // ???
  USART_InitStruct.USART_Parity = USART_PARITY_NO; // ???
  USART_InitStruct.USART_Mode = USART_MODE_NORMAL; // ??
  USART_Init(BSP_LCD, &USART_InitStruct); 
		
	
  USART_IntConfig(BSP_LCD, USART_INT_RXDR ,ENABLE); // ??????????
  //USART_IntConfig(BSP_DEBUG, USART_INT_TXDE ,ENABLE); // ??????????
  
		USART_RxCmd(BSP_LCD, ENABLE); // ??USART????? 
  USART_TxCmd(BSP_LCD, ENABLE);
		
		NVIC_EnableIRQ(BSP_LCD_IRQN); // ?????
 
}

/********************************************************
* Function name 				:Bsp_Debug_Sendbyte
* Description       :Debug?????? 
* Parameter         :
* @Data													?????
* Return          		:?
**********************************************************/ 
void Bsp_Lcd_Sendbyte(uint8_t Data)
{
	USART_SendData(BSP_LCD, Data);
	// ???????????
	while (USART_GetFlagStatus(BSP_LCD, USART_FLAG_TXDE) == RESET);		
}

/********************************************************
* Function name 				:Bsp_Debug_SendArray
* Description       :Debug???? 
* Parameter         :
* @array												?????
*	@num														???????
* Return          		:?
**********************************************************/ 
void Bsp_Lcd_SendArray(uint8_t *array,u8 num)
{
	u8 i;
	for( i = 0;i < num;i++)
	{
		Bsp_Lcd_Sendbyte(*array);
		array++;
	}
}

/********************************************************
* Function name 				:Bsp_Debug_SendStr
* Description       :Debug????? 
* Parameter         :
* @str														??????
* Return          		:?
**********************************************************/ 
void Bsp_Lcd_SendStr(char *str)
{
	uint8_t i;
	for(i = 0;str[i] != '\0';i++)
	{
		Bsp_Lcd_Sendbyte(str[i]);
	}
}


/********************************************************
* Function name 				:Debug_Printf
* Description       :Debug???? 
* Parameter         :
* @fmt														?c???printf??
* Return          		:?
**********************************************************/ 
void Bsp_Lcd_Printf(char* fmt,...) 
{  
	u16 i,j; 
	uint8_t Debug_Tx_Buf[BSP_LCD_MAX_LEN];
	va_list ap; 
	va_start(ap,fmt); 
	vsprintf((char*)Debug_Tx_Buf,fmt,ap); 
	va_end(ap);
	i=strlen((const char*)Debug_Tx_Buf);		
	for(j=0;j<i;j++)							
	{
	 while(USART_GetFlagStatus(BSP_LCD,USART_FLAG_TXC)==RESET); 
		USART_SendData(BSP_LCD,Debug_Tx_Buf[j]);  
	} 
}

/********************************************************
* Function name 				:Debug_Printf
* Description       :Debug???? 
* Parameter         :
* @fmt														?c???printf??
* Return          		:?
**********************************************************/ 
void BSP_LCD_IRQHANDLER(void)
{
	 uint8_t data;
	
  if( USART_GetFlagStatus(BSP_LCD, USART_FLAG_RXDR ) )         //????
	{
		data = USART_ReceiveData(BSP_LCD);                         //????????
		if(data == 0x01)
		{
			bsp_lcd_temperature_waveform = 1;
		}
		if(data == 0x02)
		{
			bsp_lcd_humi_waveform = 1;
		}
		if(data == 0x03)
		{
			bsp_lcd_co_waveform = 1;
		}
		rt_kprintf("%c",data);
			
	}
}
