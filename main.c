#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "timer.h"

int16_t num;

int main(void) {
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1,1,"Num:");
	OLED_ShowString(2,1,"Cnt:");
	//OLED_Clear();
	
    while(1){
		OLED_ShowNum(1,5,num,5);
		OLED_ShowNum(2,5,Timer_GetCounter(),5);
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}


