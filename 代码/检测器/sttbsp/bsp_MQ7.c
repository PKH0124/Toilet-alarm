
#include "ht32f5xxxx_01.h"              // Device header

#include "bsp_MQ7.h"          
#include <math.h>             
#include "abs_delay.h"        
//#include "bsp_Serial.h"     
#include "bsp_debug.h"        
MainData_MQ7	MainData_MQ;  

/********************************************************
* Function name 	: Bsp_MQ7_Init
* Description       : 初始化MQ-7模块
* Parameter         : void
* Return          	: 无
**********************************************************/
void Bsp_MQ7_Init(void)
{
    // 使能 GPIOC 和相关外设时钟
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PC = 1;              // 使能 GPIOC 时钟
    CKCUClock.Bit.ADC = 1;             // 使能 ADC 时钟
    CKCUClock.Bit.AFIO = 1;            // 使能 AFIO 时钟
    CKCU_PeripClockConfig(CKCUClock, ENABLE); // 配置时钟
    
	// 设置 ADC 时钟分频为8分频
    CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV8);
	
	// 配置PA0为模拟输入功能
    AFIO_GPxConfig(GPIO_PC, BSP_MQ7_GPIO_PIN, AFIO_FUN_ADC);
	ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_SOFTWARE);															
	ADC_RegularGroupConfig(HT_ADC, ONE_SHOT_MODE, 1, 1);														
	ADC_RegularChannelConfig(HT_ADC, BSP_MQ7_ADC_CHANNEL, 0);	

    // 使能ADC
    ADC_Cmd(HT_ADC, ENABLE);
}

/********************************************************
* Function name     : Bsp_MQ7_ReadRawData
* Description       : 读取MQ7传感器的原始ADC数据
* Parameter         : void
* Return           	: MQ7传感器的原始ADC数据（uint16_t 类型）
**********************************************************/

uint16_t Bsp_MQ7_ReadRawData(void)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < MQ7_READ_TIMES; i++)
    {
        // 配置ADC通道
        ADC_RegularChannelConfig(HT_ADC, BSP_MQ7_ADC_CHANNEL, 1);

        // 启动ADC转换
        ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);
        while (!ADC_GetFlagStatus(HT_ADC, ADC_FLAG_CYCLE_EOC));  // 等待转换完成

        // 累加多次(10次)读取的ADC值
        sum += ADC_GetConversionData(HT_ADC, 0);
        Abs_Delay_Ms(5);  // 延时5ms以稳定读取
    }

    // 返回平均值
    return (uint16_t)(sum / MQ7_READ_TIMES);
}

/********************************************************
* Function name     : Bsp_MQ7_ReadPPM
* Description       : 读取MQ7传感器的PPM值
* Parameter         : void
* Return           	: MQ7传感器的PPM值（float 类型）
**********************************************************/
float Bsp_MQ7_ReadPPM(void)
{
    // 只读取一次ADC值
    uint16_t rawData = Bsp_MQ7_ReadRawData();

    // 计算电压值（假设参考电压为5V）
    float voltage = (rawData * 5.0f) / 4096.0f;
    // 计算传感器电阻RS（假设RL=1kΩ）
    float RS = (5.0f - voltage) / voltage;
    // 计算PPM值（需要校准R0）
    float R0 = 10.0f;  // 示例值，需要实际校准
    float ppm = 10.0f * powf(RS / R0, -0.6549f); // 修正后的公式


    return ppm;
}

/********************************************************
* Function name     : Bsp_Parase_MQ7_Data
* Description       : 解析MQ7传感器的数据
* Parameter         : void
* Return           	: 无
**********************************************************/

void Bsp_Parase_MQ7_Data(void)
{
	// 读取并解析MQ-7的PPM值
//	MainData_MQ.ppm = Bsp_MQ7_ReadPPM();
//	Bsp_Debug_Printf("PPM: %.2f\n", MainData_MQ.ppm = Bsp_MQ7_ReadPPM());
//	Bsp_Debug_Printf("Raw ADC: %d\n", MainData_MQ.raw_ppm);
//	Bsp_Debug_Printf("Voltage: %.3fV\n", MainData_MQ.voltage);
//	Bsp_Debug_Printf("RS: %.2fkΩ\n", MainData_MQ.RS);
//	Bsp_Debug_Printf("R0: %.2fkΩ\n", MainData_MQ.R0);
//	Bsp_Debug_Printf("PPM: %.2f\n", MainData_MQ.ppm);
}
