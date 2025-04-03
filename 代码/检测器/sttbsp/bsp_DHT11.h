#ifndef _BSP_DHT11_H
#define _BSP_DHT11_H

#include "ht32f5xxxx_01.h"
#include "abs_Delay.h"
#include <stdio.h>

//  引脚高低宏定义定义
#define DHT11_HIGH()             GPIO_SetOutBits(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN)  // 设置高电平
#define DHT11_LOW()              GPIO_ClearOutBits(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN) // 设置低电平

//  引脚读取定义
#define DHT11_READ()             GPIO_ReadInBit(BSP_DHT11_GPIO, BSP_DHT11_GPIO_PIN)   // 读取引脚状态

// DHT11引脚定义
#define BSP_DHT11_GPIO           (HT_GPIOC)       // 使用GPIOC端口
#define BSP_DHT11_GPIO_PIN       (GPIO_PIN_0)     // 使用PC0引脚

// 函数声明
uint8_t Bsp_DHT11_Init(void);                     // 初始化DHT11传感器
uint8_t Bsp_DHT11_Read_Data(uint8_t *temp, uint8_t *humi);  // 读取温湿度数据
void Bsp_Parase_DHT11_Data(void);                 // 解析DHT11数据

//DHT11数据结构体
typedef struct
{
    uint8_t temperture;  // 温度值（单位：℃）
    uint8_t humidity;    // 湿度值（单位：%）
} MainData_DHT11;

extern MainData_DHT11 MainData_DHT;  // 声明全局变量


#endif
