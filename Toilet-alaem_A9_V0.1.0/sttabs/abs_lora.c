#include <stdio.h>
#include <string.h>

#include "abs_lora.h"
#include	"bsp_debug.h"
#include "abs_delay.h"

/*缓存LORA_USART收到的数据*/
static LORA_USART	s_lora_rx;

/********************************************************
* Function name 				:Abs_Lora_Clear_Struct
* Description       :清楚LORA_USART的数据 
* Parameter         :void
* Return          		:无
**********************************************************/ 
void Abs_Lora_Clear_Struct(void)
{
	memset(s_lora_rx.buffer,0,s_lora_rx.length);
	s_lora_rx.length=0;
}

/********************************************************
* Function name 				:Abs_Lora_Send_Cmd
* Description       :发送AT指令并等待回复 
* Parameter         :
*@cmd															发送的指令
*@reply													收到的回复
*@wait														等待回复的时间
* Return          		:成功返回1，失败返回0
**********************************************************/ 
int32_t Abs_Lora_Send_Cmd(char* cmd, char* reply, uint32_t wait)
{
	Abs_Lora_Clear_Struct();
	Bsp_Debug_Printf("[Abs_Lora_Send_Cmd] %s\r\n", cmd);
	Bsp_Lora_SendArray(cmd, strlen(cmd));

	Abs_Delay_Ms(wait);

	if (strcmp(reply, "") == 0)
	{
		return 1;
	}
	if (s_lora_rx.length != 0)
	{
		s_lora_rx.buffer[s_lora_rx.length] = '\0';
		if (strstr((char*)s_lora_rx.buffer, reply))
		{
			Bsp_Debug_Printf("return:%s\r\n", s_lora_rx.buffer);
			return 0;
		}
		else
		{
			Bsp_Debug_Printf("return:%s\r\n", s_lora_rx.buffer);
			return 1;
		}  
	}  
	return 1;
}

/********************************************************
* Function name 				:Abs_Lora_Wakeup
* Description       :唤醒Lora 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/
int32_t Abs_Lora_Wakeup(void)  
{
	int32_t ret = 1;
	ret = Abs_Lora_Send_Cmd("Lora","LoRa Start!",300);
	if(ret == 0)
	{
		Abs_Lora_Clear_Struct();
		return 0;
	}
	return 1;
}

/********************************************************
* Function name 				:Abs_Lora_EnterAT
* Description       :进入AT指令模式 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/ 
int32_t Abs_Lora_EnterAT(void)  
{
	int32_t ret = 1;
	ret = Abs_Lora_Send_Cmd("+++","a",300);
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("a","+OK",300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+E=OFF\r\n","OK",300);
	}
	if(ret == 0)
	{
		Abs_Lora_Clear_Struct();
		return 0;
	}
	return 1;
}

/********************************************************
* Function name 				:Abs_Lora_SetAT
* Description       :配置Lora为不组网的主从的WU模式 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/ 
int32_t Abs_Lora_SetAT(void)
{
	int32_t ret = 1;
	ret = Abs_Lora_Send_Cmd("AT+LORAPROT=NODE\r\n","OK",300);
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+PROTSEL=1\r\n","OK",300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+WMODE=MS\r\n","OK",300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+TMODE=1\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+PMODE=WU\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+WTM=2500\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+SPD=10\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+CH=4700\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+PWR=22\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+ADDR=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+FEC=1\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+LBT=OFF\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+UARTFT=10\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+UART=115200,8,1,NONE,NFC\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Abs_Lora_Send_Cmd("AT+Z\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		Abs_Lora_Clear_Struct();
		return 0;
	}
	return 1;
	
}

/********************************************************
* Function name 				:Abs_Lora_Res
* Description       :Lora模块复位 
* Parameter         :void
* Return          		:无
**********************************************************/
void Abs_Lora_Res(void)
{
	GPIO_WriteOutBits(BSP_LORA_GPIO,BSP_LORA_GPIO_RES,RESET);
	Abs_Delay_Ms(20);
	GPIO_WriteOutBits(BSP_LORA_GPIO,BSP_LORA_GPIO_RES,SET);
}

/********************************************************
* Function name 				:Abs_Lora_Init
* Description       :Lora初始化 
* Parameter         :void
* Return          		:无
**********************************************************/
void Abs_Lora_Init(void)
{
	int32_t ret = 1;
	Bsp_Lora_Usart_Config();
	Bsp_Lora_Res_Config();
	Abs_Lora_Res();
	ret = Abs_Lora_Wakeup();
	if(ret == 0)
	{
		ret = Abs_Lora_EnterAT();
	}
	if(ret == 0)
	{
		Abs_Lora_SetAT();
	}
}

/********************************************************
* Function name 				:ABS_LORA_IRQHANDLER
* Description       :Lora宏定义后的中断函数 
* Parameter         :void
* Return          		:无
**********************************************************/ 
void ABS_LORA_IRQHANDLER(void)
{
	uint8_t data;

	if( USART_GetFlagStatus(BSP_LORA, USART_FLAG_RXDR ) )         //接收中断
	{
		data = USART_ReceiveData(BSP_LORA);                         //读取接收到的数据
		s_lora_rx.buffer[s_lora_rx.length] = data;
		//Bsp_Debug_Sendbyte(s_lora_rx.buffer[s_lora_rx.length]);      //把收到的数据发送回电脑	
		s_lora_rx.length++;
	}
}
