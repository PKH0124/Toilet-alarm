#include "ht32f5xxxx_01.h"              // 设备头文件
#include <stdio.h>

#include "abs_delay.h"
#include "bsp_debug.h"
#include "bsp_LD2410B.h"

// 定义全局变量
MainData_HILINK_2410s MainData_HLK_2410s;  // LD2410B 主要数据结构体
ReceiveData_HILINK_2410s ReceiveData_HLK_2410s = {0};  // 接收数据缓冲区

uint8_t targetStateBuffer[BUFFER_SIZE] = {0};  // 初始化缓冲区为0
uint8_t bufferIndex = 0;                       // 初始化索引
uint8_t g_TargetState = 0;                     // 初始化目标状态

uint8_t bsp_ld24108_target_state_2;



/********************************************************
* Function name     : Bsp_LD2410B_Init
* Description       : 初始化LD2410B
* Parameter         : void
* Return            : 无
**********************************************************/
void Bsp_LD2410B_Init(void)
{
    USART_InitTypeDef USART_InitStruct;
    
    // 使能 GPIOA 和 UART1 的时钟
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    BSP_LD2410B_CLK(CK) = 1;       // 使能 UART1 时钟
	CKCUClock.Bit.AFIO     = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    AFIO_GPxConfig(BSP_LD2410B_AFIO_GPIO, BSP_LD2410B_AFIO_TX, AFIO_MODE_6);  // 配置 PA4 为 UART1 的 TX 功能
    AFIO_GPxConfig(BSP_LD2410B_AFIO_GPIO, BSP_LD2410B_AFIO_RX, AFIO_MODE_6);  // 配置 PA5 为 UART1 的 RX 功能

    // 配置 UART1
    USART_InitStruct.USART_BaudRate = 256000;  // 波特率 256000
    USART_InitStruct.USART_WordLength = USART_WORDLENGTH_8B;  // 8 位数据位
    USART_InitStruct.USART_StopBits = USART_STOPBITS_1;  // 1 位停止位
    USART_InitStruct.USART_Parity = USART_PARITY_NO;  // 无校验位
    USART_InitStruct.USART_Mode = USART_MODE_NORMAL;  // 使能发送和接收
    USART_Init(BSP_LD2410B, &USART_InitStruct);

    // 使能 UART1 接收中断
    USART_IntConfig(BSP_LD2410B, USART_INT_RXDR, ENABLE);
	//USART_IntConfig(BSP_LD2410B, USART_INT_TXDE ,ENABLE); // 发送数据就绪中断使能
	
    // 使能 UART1 发送和接收
    USART_RxCmd(BSP_LD2410B, ENABLE);
	USART_TxCmd(BSP_LD2410B, ENABLE);
		
    NVIC_EnableIRQ(BSP_LD2410B_IRQN);  // 使能 UART1 中断		
}

/********************************************************
* Function name     : UART1_IRQHandler
* Description       : UART1 中断服务函数，用于接收数据
* Parameter         : void
* Return            : 无
**********************************************************/
void UART1_IRQHandler(void)
{
    if (USART_GetFlagStatus(BSP_LD2410B, USART_FLAG_RXDR) == SET)  // 检查接收标志
    {
        uint8_t RxData = USART_ReceiveData(BSP_LD2410B);  // 读取接收到的数据
//        Bsp_Debug_Sendbyte(RxData);
//        Abs_Delay_Ms(2000);								//回显主要数据
        // 将数据存储到缓冲区
        if (ReceiveData_HLK_2410s.Usart_Length < BSP_LD2410B_MAX_LEN)
        {
//			USART_SendData(HT_UART1,'1');
            ReceiveData_HLK_2410s.Usart_Buff[ReceiveData_HLK_2410s.Usart_Length++] = RxData;
        }

        // 如果接收到完整的数据包，可以在这里处理数据
        if (ReceiveData_HLK_2410s.Usart_Length >= BSP_LD2410B_MAX_LEN)
        {
            Bsp_Parase_LD2410B_Data(ReceiveData_HLK_2410s.Usart_Buff, ReceiveData_HLK_2410s.Usart_Length);
            ReceiveData_HLK_2410s.Usart_Length = 0;  // 清空缓冲区
        }
    }
}

/********************************************************
* Function name     : Bsp_Parase_LD2410B_Data
* Description       : 解析 LD2410B 数据
* Parameter         :
*   @data           : 接收到的数据
*   @length         : 数据长度
* Return            : 无
**********************************************************/
void Bsp_Parase_LD2410B_Data(uint8_t *data, uint8_t length)
{
    // 检查数据包头
    if (length >= BSP_LD2410B_MAX_LEN &&
        data[0] == 0xF4 && data[1] == 0xF3 &&
        data[2] == 0xF2 && data[3] == 0xF1)  // 雷达数据包头判断
    {
        // 解析数据
        MainData_HLK_2410s.Target_State = data[8];
        MainData_HLK_2410s.Moving_Tagret_Distance = data[9];
        MainData_HLK_2410s.Moving_Target_Energy = data[11];
        MainData_HLK_2410s.Static_Tagret_Distance = data[12];
        MainData_HLK_2410s.Static_Target_Energy = data[14];
        MainData_HLK_2410s.Detect_Dinstance = data[15];
			
			if(MainData_HLK_2410s.Target_State == 2)
			{
				 bsp_ld24108_target_state_2++;
			}

        // 打印解析结果
//        Bsp_Debug_Printf("Target_State:%x\r\n", MainData_HLK_2410s.Target_State);
//        Bsp_Debug_Printf("Moving_Tagret_Distance:%d\r\n", MainData_HLK_2410s.Moving_Tagret_Distance);
//        Bsp_Debug_Printf("Moving_Target_Energy:%d\r\n", MainData_HLK_2410s.Moving_Target_Energy);
//        Bsp_Debug_Printf("Static_Tagret_Distance:%d\r\n", MainData_HLK_2410s.Static_Tagret_Distance);
//        Bsp_Debug_Printf("Static_Target_Energy:%d\r\n", MainData_HLK_2410s.Static_Target_Energy);
//        Bsp_Debug_Printf("Detect_Dinstance:%d\r\n", MainData_HLK_2410s.Detect_Dinstance);

    }
}
/********************************************************
* Function name     : c_GetTargetStateString
* Description       : 根据目标状态值返回对应的状态字符串
* Parameter			
*   @targetState    : 目标状态值（uint8_t 类型）
* Return           	
	@Yes			: 目标静止 
	@No				: 目标运动或多目标
**********************************************************/
const char* c_GetTargetStateString(void)
{
    // 统计缓冲区中目标状态为2（静止）的次数
    uint8_t count = 0;
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (targetStateBuffer[i] == 2)
        {
            count++;
        }
    }

    // 根据统计结果判断目标状态
    if (count >= BUFFER_SIZE * 0.9)  // 如果90%以上的数据是静止状态
    {
        return "Yes";  // 目标静止
    }
    else
    {
        return "No";   // 目标运动或多目标
    }
}
