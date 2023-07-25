#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "infrared.h"

int main(void) {
	OLED_Init();
	INFRARED_Init();
	
	OLED_ShowString(1,1,"Count:");
	
	
    while(1){
		OLED_ShowNum(1,7,Get_Count(),5);
		
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}


