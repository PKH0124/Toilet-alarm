#include <stdio.h>
#include <string.h>

#include "abs_lora.h"
#include	"bsp_debug.h"
#include "abs_delay.h"


/********************************************************
* Function name 				:Abs_Lora_Wakeup
* Description       :唤醒Lora 
* Parameter         :void
* Return          		:成功返回0，失败返回1
**********************************************************/
int32_t Abs_Lora_Wakeup(void)  
{
	int32_t ret = 1;
	ret = Bsp_Lora_Send_Cmd("Lora","LoRa Start!",300);
	if(ret == 0)
	{
		Bsp_Lora_Clear_Struct();
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
	ret = Bsp_Lora_Send_Cmd("+++","a",300);
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("a","+OK",300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+E=OFF\r\n","OK",300);
	}
	if(ret == 0)
	{
		Bsp_Lora_Clear_Struct();
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
	ret = Bsp_Lora_Send_Cmd("AT+LORAPROT=NODE\r\n","OK",300);
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PROTSEL=1\r\n","OK",300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+WMODE=TRANS\r\n","OK",300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PMODE=RUN\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+SPD=10\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+CH=4700\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PWR=22\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+ADDR=62288\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+FEC=1\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+LBT=OFF\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+UARTFT=10\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+UART=115200,8,1,NONE,NFC\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+RESEND=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+FDMODE=ON\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+TXCH=4800\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+SENDOK=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+MTU=240\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+DATAMODE=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+RFTO=60\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+PFLAG=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+RELAY=0\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		ret = Bsp_Lora_Send_Cmd("AT+Z\r\n", "OK", 300);
	}
	if(ret == 0)
	{
		Bsp_Lora_Clear_Struct();
		return 0;
	}
	return 1;
	
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
	Bsp_Lora_Res();
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


