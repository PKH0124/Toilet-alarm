#include "ht32f5xxxx_01.h"              // Device header


#include "bsp_DHT11.h"             
#include "abs_delay.h"             
#include "bsp_debug.h"             

//全局变量
uint8_t temp, humi;                
uint8_t buf[64];                   
MainData_DHT11 MainData_DHT;       

/********************************************************
* Function name     : Bsp_DHT11_Set_Mode
* Description       : 设置DHT11引脚的工作模式
* Parameter			
*   @mode           : 引脚模式（0-输入模式，1-输出模式）
* Return           	: 无
**********************************************************/
void Bsp_DHT11_Set_Mode(uint8_t mode)
{
    if (mode == 1)
    {
        // 输出模式
        GPIO_DirectionConfig(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN, GPIO_DIR_OUT);  // 设置为输出模式
        GPIO_InputConfig(HT_GPIOC, GPIO_PIN_0,DISABLE);  // 禁用输入
	}
    else
    {
        // 输入模式
        GPIO_DirectionConfig(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN, GPIO_DIR_IN);  // 设置为输入模式
        GPIO_InputConfig(HT_GPIOC, GPIO_PIN_0,ENABLE); // 使能输入
    }
}

/********************************************************
* Function name     : Bsp_DHT11_Reset
* Description       : 复位DHT11传感器
* Parameter         : voids
* Return           	: 无
**********************************************************/
void Bsp_DHT11_Reset(void)
{
    Bsp_DHT11_Set_Mode(1);  // 设置为输出模式
    DHT11_LOW();        // 拉低引脚
    Abs_Delay_Ms(20);   // 保持低电平20ms（DHT11复位要求）
    DHT11_HIGH();       // 拉高引脚
    Abs_Delay_Us(30);   // 保持高电平30us（等待DHT11响应）
}

/********************************************************
* Function name     : Bsp_DHT11_Check
* Description       : 检测DHT11传感器是否存在
* Parameter         : void
* Return           	: 0-存在，1-不存在
**********************************************************/
uint8_t Bsp_DHT11_Check(void) {
    uint8_t retry = 0;
    Bsp_DHT11_Set_Mode(0);  // 切换输入模式（含上拉）

    // 增加更宽松的超时时间（DHT11响应需80us）
    while (DHT11_READ() && retry < 100) 
    {
        retry++;
        Abs_Delay_Us(1);
    }
    if (retry >= 100) 
    {
        return 1;
    }

    retry = 0;
    while (!DHT11_READ() && retry < 100) 
    {
        retry++;
        Abs_Delay_Us(1);
    }
    if (retry >= 100) 
    {
        return 1;
    }
    return 0;
}

/********************************************************
* Function name     : Bsp_DHT11_Read_Bit
* Description       : 读取DHT11的一个位
* Parameter         : void
* Return           	: 读取到的位（0或1）
**********************************************************/
uint8_t Bsp_DHT11_Read_Bit(void)
{
    uint8_t retry = 0;  // 超时计数器

    // 等待低电平结束（起始信号）
    while (DHT11_READ() && retry < 100)
    {
        retry++;
        Abs_Delay_Us(1);
    }

    retry = 0;

    // 等待高电平结束（数据位开始）
    while (!DHT11_READ() && retry < 100)
    {
        retry++;
        Abs_Delay_Us(1);
    }

    Abs_Delay_Us(40);  // 等待40us后采样

    // 判断高电平持续时间以确定数据位
    if (DHT11_READ()) 
    {
        return 1;  // 高电平持续时间长，表示'1'
    }
    else 
    {
        return 0;  // 高电平持续时间短，表示'0'
    }
}

/********************************************************
* Function name		: Bsp_DHT11_Read_Byte
* Description       : 读取DHT11的一个字节
* Parameter         : void
* Return           	: 读取到的字节
**********************************************************/
uint8_t Bsp_DHT11_Read_Byte(void)
{
    uint8_t i, data = 0;

    // 读取8个位组成一个字节
    for (i = 0; i < 8; i++)
    {
        data <<= 1;          // 左移一位
        data |= Bsp_DHT11_Read_Bit();  // 读取当前位
    }

    return data;
}

/********************************************************
* Function name     : Bsp_DHT11_Read_Data
* Description       : 读取DHT11的温湿度数据
* Parameter			
*   @temp           : 温度值（范围：0~50℃）
*   @humi           : 湿度值（范围：20%~90%）
* Return           	: 0-成功，1-失败
**********************************************************/
uint8_t Bsp_DHT11_Read_Data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];  // 存储读取的5个字节数据
    uint8_t i;

    Bsp_DHT11_Reset();  // 复位DHT11

    if (Bsp_DHT11_Check() == 0)  // 检测DHT11是否存在
    {
        // 读取40位数据（5字节）
        for (i = 0; i < 5; i++)  
        {
            buf[i] = Bsp_DHT11_Read_Byte();
        }
        
        // 校验数据（前4字节和等于第5字节）
        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            *humi = buf[0];  // 湿度整数部分
            *temp = buf[2];  // 温度整数部分
        }
        else 
        {
            return 1;  // 校验失败
        }
    }	
    else
    {
        return 1;  // 读取失败
    }
    return 0;  // 读取成功
}

/********************************************************
* Function name     : Bsp_Parase_DHT11_Data
* Description       : 解析DHT11的温湿度数据
* Parameter         : void
* Return           	: 无
**********************************************************/
void Bsp_Parase_DHT11_Data(void)
{   
    if (Bsp_DHT11_Read_Data(&temp, &humi) == 0)  // 读取温湿度数据
    {
        // 将读取的数据存入全局结构体
        MainData_DHT.temperture = temp;
        MainData_DHT.humidity = humi;
    }
    else
    {
		
    }
    
}

/********************************************************
* Function name     : Bsp_DHT11_Init
* Description       : 初始化DHT11传感器
* Parameter         : void
* Return           	: 返回Bsp_DHT11_Check()结果
**********************************************************/
uint8_t Bsp_DHT11_Init(void)
{
    // 配置GPIOC时钟
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PC = 1;    // 使能GPIOC时钟
    CKCUClock.Bit.AFIO = 1;  // 使能AFIO时钟
    CKCUClock.Bit.PB         = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);


	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_15, GPIO_DIR_OUT);
	GPIO_ClearOutBits(HT_GPIOB, GPIO_PIN_15);

    // 配置PC0为GPIO功能
    AFIO_GPxConfig(GPIO_PC, BSP_DHT11_GPIO_PIN, AFIO_FUN_GPIO);
   
    // 初始设置为输入模式
    GPIO_DirectionConfig(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN, GPIO_DIR_IN);
    
    GPIO_InputConfig(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN,ENABLE);

    Bsp_DHT11_Reset();  // 复位DHT11

    return Bsp_DHT11_Check();  // 返回检测结果
}
