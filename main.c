#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "encoder.h"
#include "ad.h"


int main(void) {
	OLED_Init();
	AD_Init();

	
    while(1){
		OLED_ShowNum(1,5,AD_val[0],4);
		OLED_ShowNum(1,5,AD_val[1],4);
		Delay_ms(100);
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}

/*
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		speed = Encoder_Get();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/




