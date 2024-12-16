#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "bsp_debug.h"
#include "abs_ht32led.h"

/********************************************************
* Function name 				:Bsp_Debug_Config
* Description       :初始化Debug的usart0 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Debug_Config(void)
{
  USART_InitTypeDef USART_InitStruct; 
  
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  BSP_DEBUG_CLK(CK)   = 1;
  CKCUClock.Bit.AFIO     = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
		
  AFIO_GPxConfig(BSP_DEBUG_AFIO, BSP_DEBUG_AFIO_TX, AFIO_MODE_6); // 开启复用功能  AFIO_FUN_USART_UART
  AFIO_GPxConfig(BSP_DEBUG_AFIO, BSP_DEBUG_AFIO_RX, AFIO_MODE_6);  
 
      
  USART_InitStruct.USART_BaudRate = 115200;  // 波特率
  USART_InitStruct.USART_WordLength = USART_WORDLENGTH_8B; // 字节长度
  USART_InitStruct.USART_StopBits = USART_STOPBITS_1; // 停止位
  USART_InitStruct.USART_Parity = USART_PARITY_NO; // 校验位
  USART_InitStruct.USART_Mode = USART_MODE_NORMAL; // 模式
  USART_Init(BSP_DEBUG, &USART_InitStruct); 
		
	
  USART_IntConfig(BSP_DEBUG, USART_INT_RXDR ,ENABLE); // 接收数据就绪中断使能
  //USART_IntConfig(BSP_DEBUG, USART_INT_TXDE ,ENABLE); // 发送数据就绪中断使能
  
		USART_RxCmd(BSP_DEBUG, ENABLE); // 使能USART接收、发送 
  USART_TxCmd(BSP_DEBUG, ENABLE);
		
		NVIC_EnableIRQ(BSP_DEBUG_IRQN); // 初始化中断
 
}

/********************************************************
* Function name 				:Bsp_Debug_Sendbyte
* Description       :Debug发送一个字节 
* Parameter         :
* @Data													发送的字节
* Return          		:无
**********************************************************/ 
void Bsp_Debug_Sendbyte(uint8_t Data)
{
	USART_SendData(BSP_DEBUG, Data);
	// 等待发送数据寄存器清空
	while (USART_GetFlagStatus(BSP_DEBUG, USART_FLAG_TXDE) == RESET);		
}

/********************************************************
* Function name 				:Bsp_Debug_SendArray
* Description       :Debug发送数组 
* Parameter         :
* @array												发送的数组
*	@num														发送的数组长度
* Return          		:无
**********************************************************/ 
void Bsp_Debug_SendArray(uint8_t *array,u8 num)
{
	u8 i;
	for( i = 0;i < num;i++)
	{
		Bsp_Debug_Sendbyte(*array);
		array++;
	}
}

/********************************************************
* Function name 				:Bsp_Debug_SendStr
* Description       :Debug发送字符串 
* Parameter         :
* @str														发送的字符串
* Return          		:无
**********************************************************/ 
void Bsp_Debug_SendStr(char *str)
{
	uint8_t i;
	for(i = 0;str[i] != '\0';i++)
	{
		Bsp_Debug_Sendbyte(str[i]);
	}
}


/********************************************************
* Function name 				:Debug_Printf
* Description       :Debug的重定向 
* Parameter         :
* @fmt														与c语言的printf一样
* Return          		:无
**********************************************************/ 
void Bsp_Debug_Printf(char* fmt,...) 
{  
	u16 i,j; 
	uint8_t Debug_Tx_Buf[BSP_DEBUG_MAX_LEN];
	va_list ap; 
	va_start(ap,fmt); 
	vsprintf((char*)Debug_Tx_Buf,fmt,ap); 
	va_end(ap);
	i=strlen((const char*)Debug_Tx_Buf);		
	for(j=0;j<i;j++)							
	{
	 while(USART_GetFlagStatus(BSP_DEBUG,USART_FLAG_TXC)==RESET); 
		USART_SendData(BSP_DEBUG,Debug_Tx_Buf[j]);  
	} 
}

/********************************************************
* Function name 				:Debug_Printf
* Description       :Debug的重定向 
* Parameter         :
* @fmt														与c语言的printf一样
* Return          		:无
**********************************************************/ 
void BSP_DEBUG_IRQHANDLER(void)
{
	 uint8_t data;
	
  if( USART_GetFlagStatus(BSP_DEBUG, USART_FLAG_RXDR ) )         //接收中断
	{
		data = USART_ReceiveData(BSP_DEBUG);                         //读取接收到的数据
		USART_SendData(BSP_DEBUG, data);                                 //把收到的数据发送回电脑		
	}
}
