#ifndef _BSP_MQ7_H
#define _BSP_MQ7_H

#include "ht32f5xxxx_01.h"              // Device header

#include <stdio.h>

// 定义ADC通道和GPIO引脚
//#define MQ7_ADC_GPIO_PORT        GPIOA
//#define MQ7_ADC_GPIO_PIN         GPIO_Pin_1
#define BSP_MQ7_GPIO           	(HT_GPIOC)
#define BSP_MQ7_GPIO_PIN           (GPIO_PIN_4)
#define BSP_MQ7_ADC_CHANNEL     ADC_CH_8  // 使用 ADC 通道 8
// 定义ADC采样次数
#define MQ7_READ_TIMES           (10)

// 函数声明
void Bsp_MQ7_Init(void);                     // 初始化MQ-7模块

float Bsp_MQ7_ReadPPM(void);                 // 读取MQ-7的PPM值

//#pragma pack(push, 1)
typedef struct
{
	uint16_t raw_ppm;
	float voltage;
	float RS;
	float R0;
	float ppm;							 //一氧化碳百万分比值
}MainData_MQ7;							 //MQ-7主要数据结构体

extern MainData_MQ7	MainData_MQ;
#endif
