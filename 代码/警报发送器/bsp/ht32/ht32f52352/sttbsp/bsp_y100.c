#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include "bsp_y100.h"
#include "bsp_debug.h"
#include "abs_ht32led.h"


/********************************************************
* Function name 				:Bsp_Debug_Config
* Description       :???Debug?usart0 
* Parameter         :? 
* Return          		:?
**********************************************************/
void Bsp_Y100_Config(void)
{
  USART_InitTypeDef USART_InitStruct; 
  
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  BSP_Y100_CLK(CK)   = 1;
  CKCUClock.Bit.AFIO     = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
		
  AFIO_GPxConfig(BSP_Y100_AFIO, BSP_Y100_AFIO_TX, AFIO_MODE_6); // ??????  AFIO_FUN_USART_UART
  AFIO_GPxConfig(BSP_Y100_AFIO, BSP_Y100_AFIO_RX, AFIO_MODE_6);  
 
  USART_InitStruct.USART_BaudRate = 115200;  // ???
  USART_InitStruct.USART_WordLength = USART_WORDLENGTH_8B; // ????
  USART_InitStruct.USART_StopBits = USART_STOPBITS_1; // ???
  USART_InitStruct.USART_Parity = USART_PARITY_NO; // ???
  USART_InitStruct.USART_Mode = USART_MODE_NORMAL; // ??
  USART_Init(BSP_Y100, &USART_InitStruct); 
		
	
  USART_IntConfig(BSP_Y100, USART_INT_RXDR ,ENABLE); // ??????????
  //USART_IntConfig(BSP_DEBUG, USART_INT_TXDE ,ENABLE); // ??????????
  
	USART_RxCmd(BSP_Y100, ENABLE); // ??USART????? 
  USART_TxCmd(BSP_Y100, ENABLE);
		
	NVIC_EnableIRQ(BSP_Y100_IRQN); // ?????
 
}

/********************************************************
* Function name 				:Bsp_Debug_Sendbyte
* Description       :Debug?????? 
* Parameter         :
* @Data													?????
* Return          		:?
**********************************************************/ 
void Bsp_Y100_Sendbyte(uint8_t Data)
{
	USART_SendData(BSP_Y100, Data);
	// ???????????
	while (USART_GetFlagStatus(BSP_Y100, USART_FLAG_TXDE) == RESET);		
}

/********************************************************
* Function name 				:Bsp_Debug_SendArray
* Description       :Debug???? 
* Parameter         :
* @array												?????
*	@num														???????
* Return          		:?
**********************************************************/ 
void Bsp_Y100_SendArray(uint8_t *array,u8 num)
{
	u8 i;
	for( i = 0;i < num;i++)
	{
		Bsp_Y100_Sendbyte(*array);
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
void Bsp_Y100_SendStr(char *str)
{
	uint8_t i;
	for(i = 0;str[i] != '\0';i++)
	{
		Bsp_Y100_Sendbyte(str[i]);
	}
}


/********************************************************
* Function name 				:Debug_Printf
* Description       :Debug???? 
* Parameter         :
* @fmt														?c???printf??
* Return          		:?
**********************************************************/ 
void Bsp_Y100_Printf(char* fmt,...) 
{  
	u16 i,j; 
	uint8_t Debug_Tx_Buf[BSP_Y100_MAX_LEN];
	va_list ap; 
	va_start(ap,fmt); 
	vsprintf((char*)Debug_Tx_Buf,fmt,ap); 
	va_end(ap);
	i=strlen((const char*)Debug_Tx_Buf);		
	for(j=0;j<i;j++)							
	{
	 while(USART_GetFlagStatus(BSP_Y100,USART_FLAG_TXC)==RESET); 
		USART_SendData(BSP_Y100,Debug_Tx_Buf[j]);  
	} 
}

/********************************************************
* Function name 				:Debug_Printf
* Description       :Debug???? 
* Parameter         :
* @fmt														?c???printf??
* Return          		:?
**********************************************************/ 
void BSP_Y100_IRQHANDLER(void)
{
	 uint8_t data;
	
  if( USART_GetFlagStatus(BSP_Y100, USART_FLAG_RXDR ) )         //????
	{
		data = USART_ReceiveData(BSP_Y100);                         //????????
			
	}
}
