#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int16_t num;

int main(void) {
	OLED_Init();
	CountSensor_Init();
	
	OLED_ShowString(1,1,"Num");
	
    while(1){
		num += Get_Count();
		OLED_ShowSignedNum(1,5,num,5);
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}


