#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"
#include "stdio.h"



int main(void) {
	OLED_Init();

	Serial_Init();
	
	Serial_SendData(0x42);
	uint8_t arr[] = {0x41,0x42,0x43};
	Serial_SendArray(arr, 3);
	Serial_SendString("Helloworld\r\n");
	int16_t i = 16/10;
	Serial_SendNum(12345,5);
	printf("num=%d\r\n",777);
    while(1){

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

int fputc(int ch, FILE *f){
	Serial_SendData(ch);
}


