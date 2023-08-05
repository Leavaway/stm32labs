#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"
#include "stdio.h"
#include "stdarg.h"

uint16_t RxData;

void Serial_Printf(char *format, ...){
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}


int main(void) {
	OLED_Init();

	Serial_Init();
	
	Serial_SendData(0x42);
	uint8_t arr[] = {0x41,0x42,0x43};
	Serial_SendArray(arr, 3);
	Serial_SendString("Helloworld\r\n");
	int16_t i = 16/10;
	Serial_SendNum(12345,5);
	//printf("num=%d\r\n",777);
	
	char String[100];
	sprintf(String, "Num=%d\r\n", 888);
	Serial_SendString(String);
	
	Serial_Printf("Num=%d\r\n", 999);
    while(1){
		/*
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)){
			RxData = USART_ReceiveData(USART1);
			OLED_ShowHexNum(1,1,RxData,2);
		}
		*/
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

/*
int fputc(int ch, FILE *f){
	Serial_SendData(ch);
}
*/

void USART1_IRQHandler(void){
	OLED_ShowString(2,1,"Receive");
	RxData = USART_ReceiveData(USART1);
	Serial_SendData(RxData);
	OLED_ShowHexNum(1,1,RxData,2);
}


