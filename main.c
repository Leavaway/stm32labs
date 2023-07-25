#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void) {
	OLED_Init();
	
	OLED_ShowString(6,4,"cat");
	OLED_ShowNum(3, 7, 3,1);
	OLED_ShowChar(3,8,'.');
	OLED_ShowNum(3, 9, 14159,5);
	OLED_Clear();
	
	
	
    while(1){

		
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}


