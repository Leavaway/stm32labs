#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "encoder.h"
#include "timer.h"

int16_t i;
float angle;
uint8_t KeyNum;
int8_t speed;


int main(void) {
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	
	OLED_ShowString(1,1,"speed:");
	
    while(1){
		OLED_ShowSignedNum(1,7,speed,5);
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		speed = Encoder_Get();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

