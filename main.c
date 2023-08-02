#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "key.h"
#include "encoder.h"
#include "ad.h"

int16_t i,j,k,l;
float v;
uint8_t KeyNum;
int8_t speed;


int main(void) {
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD0;");
	OLED_ShowString(2,1,"AD1;");
	OLED_ShowString(3,1,"AD2;");
	OLED_ShowString(4,1,"AD3;");
	
    while(1){
		i = AD_GetValue(ADC_Channel_0);
		j = AD_GetValue(ADC_Channel_1);
		k = AD_GetValue(ADC_Channel_2);
		l = AD_GetValue(ADC_Channel_3);
		OLED_ShowNum(1,5,i,4);
		OLED_ShowNum(2,5,j,4);
		OLED_ShowNum(3,5,k,4);
		OLED_ShowNum(4,5,l,4);
		
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


