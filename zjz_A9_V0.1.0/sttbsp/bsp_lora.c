#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "bsp_lora.h"
#include "abs_ht32led.h"

/********************************************************
* Function name 				:Bsp_Lora_Res_Config
* Description       :初始化Lora复位的gpio 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Lora_Res_Config(void)
{
 CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
 CKCUClock.Bit.PC    = 1; 
 CKCU_PeripClockConfig(CKCUClock, ENABLE);

 GPIO_SetOutBits         (BSP_LORA_GPIO, BSP_LORA_GPIO_RES); 
 //GPIO_ClearOutBits        (BSP_LORA_GPIO, BSP_LORA_GPIO_RES); 
 GPIO_DirectionConfig    (BSP_LORA_GPIO, BSP_LORA_GPIO_RES, GPIO_DIR_OUT); 
 GPIO_PullResistorConfig (BSP_LORA_GPIO, BSP_LORA_GPIO_RES, GPIO_PR_DISABLE); 
 GPIO_DriveConfig        (BSP_LORA_GPIO, BSP_LORA_GPIO_RES, GPIO_DV_8MA);
}

/********************************************************
* Function name 				:Bsp_Lora_Config
* Description       :初始化Lora的usart0 
* Parameter         :无 
* Return          		:无
**********************************************************/
void Bsp_Lora_Usart_Config(void)
{
  USART_InitTypeDef USART_InitStruct; 
  
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  BSP_LORA_CLK(CK)   = 1;
  CKCUClock.Bit.AFIO     = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
		
  AFIO_GPxConfig(BSP_LORA_AFIO, BSP_LORA_AFIO_TX, AFIO_MODE_6); // 开启复用功能  AFIO_FUN_USART_UART
  AFIO_GPxConfig(BSP_LORA_AFIO, BSP_LORA_AFIO_RX, AFIO_MODE_6);   
      
		  USART_InitStruct.USART_BaudRate = 115200;  // 波特率
  USART_InitStruct.USART_WordLength = USART_WORDLENGTH_8B; // 字节长度
  USART_InitStruct.USART_StopBits = USART_STOPBITS_1; // 停止位
  USART_InitStruct.USART_Parity = USART_PARITY_NO; // 校验位
  USART_InitStruct.USART_Mode = USART_MODE_NORMAL; // 模式
  USART_Init(BSP_LORA, &USART_InitStruct); 
		
	
  USART_IntConfig(BSP_LORA, USART_INT_RXDR ,ENABLE); // 接收数据就绪中断使能
  //USART_IntConfig(BSP_Lora, USART_INT_TXDE ,ENABLE); // 发送数据就绪中断使能
  
		USART_RxCmd(BSP_LORA, ENABLE); // 使能USART接收、发送 
  USART_TxCmd(BSP_LORA, ENABLE);
		
		NVIC_EnableIRQ(BSP_LORA_IRQN); // 初始化中断
 
}

/********************************************************
* Function name 				:Bsp_Lora_Sendbyte
* Description       :Lora发送一个字节 
* Parameter         :
* @Data													发送的字节
* Return          		:无
**********************************************************/ 
void Bsp_Lora_Sendbyte(char Data)
{
	USART_SendData(BSP_LORA, Data);
	// 等待发送数据寄存器清空
	while (USART_GetFlagStatus(BSP_LORA, USART_FLAG_TXDE) == RESET);		
}

/********************************************************
* Function name 				:Bsp_Lora_SendArray
* Description       :Lora发送数组 
* Parameter         :
* @array												发送的数组
*	@num														发送的数组长度
* Return          		:无
**********************************************************/ 
void Bsp_Lora_SendArray(char array[],uint8_t num)
{
	u8 i;
	for( i = 0;i < num;i++)
	{
		Bsp_Lora_Sendbyte(*array);
		array++;
	}
}

/********************************************************
* Function name 				:Bsp_Lora_SendStr
* Description       :Lora发送字符串 
* Parameter         :
* @str														发送的字符串
* Return          		:无
**********************************************************/ 
void Bsp_Lora_SendStr(char *str)
{
	uint8_t i;
	for(i = 0;str[i] != '\0';i++)
	{
		Bsp_Lora_Sendbyte(str[i]);
	}
}


/********************************************************
* Function name 				:Bsp_Lora_Printf
* Description       :Lora的重定向 
* Parameter         :
* @fmt														与c语言的printf一样
* Return          		:无
**********************************************************/ 
void Bsp_Lora_Printf(char* fmt,...) 
{  
	uint8_t lora_tx_buf[BSP_LORA_MAX_LEN];
	u16 i,j;
	va_list ap; 
	va_start(ap,fmt); 
	vsprintf((char*)lora_tx_buf,fmt,ap); 
	va_end(ap);
	i=strlen((const char*)lora_tx_buf);		
	for(j=0;j<i;j++)							
	{
	 while(USART_GetFlagStatus(BSP_LORA,USART_FLAG_TXC)==RESET); 
		USART_SendData(BSP_LORA,lora_tx_buf[j]);  
	} 
}


