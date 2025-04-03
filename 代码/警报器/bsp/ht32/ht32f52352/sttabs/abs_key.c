#include "abs_key.h"

ABS_KEY_STATE abs_key_station;

void Abs_Kay_Scan(ABS_KEY_STATE *struction)
{
	switch (struction->bit)
	{
			case 0:         
					/*未按下*/
					if (Bsp_Key_Read() == 0 && struction->state == ABS_KEY_NOTPRESSED) 
					{
							struction->bit++;
					}
					break;
			case 1:    
					/*前消抖*/
					if (Bsp_Key_Read() == 0)
					{
							struction->bit++;
					}
					break;
			case 2:         
					/*按住*/
					if (Bsp_Key_Read() == 0)
					{
						struction->cnt++;
						struction->state = ABS_KEY_PRESSED;
					}
					else
					{
						if (struction->cnt > 3 &&  struction->cnt < 250)   //
						{
								struction->state = ABS_KEY_LONGPRESS1;
						}
						else if (struction->cnt > 250)     //长按5S    
						{
								struction->state = ABS_KEY_LONGPRESS5;
						}            
						else
						{
								struction->state = ABS_KEY_NOTPRESSED;
						}
						struction->bit++;       //消除后抖							
					}
					break;
			case 3:    
					/*结束清除*/
					struction->state = 0;
					struction->bit = 0;
					struction->cnt = 0;
					break;
	} 
}
