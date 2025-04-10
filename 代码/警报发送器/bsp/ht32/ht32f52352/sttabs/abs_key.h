#ifndef __ABS_KEY_H__
#define __ABS_KEY_H__
 
#include "ht32.h"
#include "bsp_key.h"

enum ABS_KEY_STATE{
	ABS_KEY_NOTPRESSED,//没按下
	ABS_KEY_PRESSED,//按下
	ABS_KEY_LONGPRESS1,//按1s
	ABS_KEY_LONGPRESS5,//按5s
};

typedef struct{
  enum ABS_KEY_STATE state;		//该电机起点限位开关的状态,等于3为按下，等于0为未按下
	uint16_t cnt;					//该按键1的计时
	uint8_t bit;				//该按键1运行时的状态
}ABS_KEY_STATE;

extern ABS_KEY_STATE abs_key_station;

void Abs_Kay_Scan(ABS_KEY_STATE *struction);

#endif


