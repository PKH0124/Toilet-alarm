#ifndef _BSP_MQ7_H
#define _BSP_MQ7_H

#include "ht32f5xxxx_01.h"              // Device header

#include <stdio.h>

// ����ADCͨ����GPIO����
//#define MQ7_ADC_GPIO_PORT        GPIOA
//#define MQ7_ADC_GPIO_PIN         GPIO_Pin_1
#define BSP_MQ7_GPIO           	(HT_GPIOC)
#define BSP_MQ7_GPIO_PIN           (GPIO_PIN_4)
#define BSP_MQ7_ADC_CHANNEL     ADC_CH_8  // ʹ�� ADC ͨ�� 8
// ����ADC��������
#define MQ7_READ_TIMES           (10)

// ��������
void Bsp_MQ7_Init(void);                     // ��ʼ��MQ-7ģ��

float Bsp_MQ7_ReadPPM(void);                 // ��ȡMQ-7��PPMֵ

//#pragma pack(push, 1)
typedef struct
{
	uint16_t raw_ppm;
	float voltage;
	float RS;
	float R0;
	float ppm;							 //һ����̼����ֱ�ֵ
}MainData_MQ7;							 //MQ-7��Ҫ���ݽṹ��

extern MainData_MQ7	MainData_MQ;
#endif
