#ifndef _BSP_LD2410B_H
#define _BSP_LD2410B_H



#define BUFFER_SIZE 10  // 缓冲区大小，存储最近10次的数据

extern uint8_t targetStateBuffer[BUFFER_SIZE];  // 存储targetState的缓冲区
extern uint8_t bufferIndex;  // 缓冲区索引
extern uint8_t g_TargetState;  // 全局变量，存储Target_State

extern uint8_t bsp_ld24108_target_state_2;

const char* c_GetTargetStateString(void);
void Bsp_LD2410B_Init(void);
void Bsp_Parase_LD2410B_Data(uint8_t *data, uint8_t length);

//最大数据长度
#define BSP_LD2410B_MAX_LEN 23 				
#define BSP_LD2410B (HT_UART1)

#define BSP_LD2410B_CLK(CK) ( CKCUClock.Bit.UART1)

#define BSP_LD2410B_AFIO_GPIO 	GPIO_PC

#define BSP_LD2410B_AFIO_TX     AFIO_PIN_12  // 使用 PA4 的复用功能
#define BSP_LD2410B_AFIO_RX     AFIO_PIN_13  // 使用 PA5 的复用功能


#define BSP_LD2410B_IRQN (UART1_IRQn)

void Bsp_LD2410B_Init(void);
void Bsp_Parase_LD2410B_Data(uint8_t *data, uint8_t length);


typedef struct
{
	uint8_t Usart_Buff[BSP_LD2410B_MAX_LEN]; 	//数组定义
	uint8_t Usart_Length;					//数组长度
}ReceiveData_HILINK_2410s;					//接收数据结构体

typedef struct
{	
	uint8_t Target_State;					//目标状态
	
	uint16_t Moving_Tagret_Distance;		//运动目标距离
	uint8_t Moving_Target_Energy;			//运动目标能量
	
	uint16_t Static_Tagret_Distance;		//静止目标距离
	uint8_t Static_Target_Energy;			//静止目标能量
	
	uint16_t Detect_Dinstance;				//探测距离
} MainData_HILINK_2410s;					//LD2410B主要数据结构体

extern const char* stateString;				//存储从 `GetTargetStateString` 函数返回的状态字符串

extern MainData_HILINK_2410s	MainData_HLK_2410s;
extern ReceiveData_HILINK_2410s	ReceiveData_HLK_2410s;

#endif
