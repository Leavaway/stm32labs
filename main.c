#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"
#include "stdio.h"
#include "key.h"
#include "led.h"
#include "string.h"

uint8_t Serial_TxPacket[4];
char Serial_RxPacket[100];
uint16_t RxData;
uint16_t keynum;

int main(void) {
	OLED_Init();
	LED_Init();
	Serial_Init();
	
	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");
	
	while (1)
	{
		
		Delay_ms(100000);	
	}
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
	static uint8_t status = 0;
	RxData = USART_ReceiveData(USART1);
	static uint8_t i = 0;
	switch(status){
		case(0):
			if(RxData == '@'){
				status = 1;
			}
			break;
		case(1):
			if(RxData == '\r'){
				status = 2;
			}else{
				Serial_RxPacket[i] = RxData;
				i++;
			}
			break;
		case(2):
			if(RxData == '\n'){
				//Serial_RxPacket[i] = '\n';
				i = 0;
				status = 0;
				OLED_ShowString(4, 1, "                ");
				OLED_ShowString(4, 1, Serial_RxPacket);
				
				if (strcmp(Serial_RxPacket, "LED_ON") == 0)
				{
					LED1_ON();
					Serial_SendString("LED_ON_OK\r\n");
					OLED_ShowString(2, 1, "                ");
					OLED_ShowString(2, 1, "LED_ON_OK");
				}
				else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)
				{
					LED1_OFF();
					Serial_SendString("LED_OFF_OK\r\n");
					OLED_ShowString(2, 1, "                ");
					OLED_ShowString(2, 1, "LED_OFF_OK");
				}
				else
				{
					Serial_SendString("ERROR_COMMAND\r\n");
					OLED_ShowString(2, 1, "                ");
					OLED_ShowString(2, 1, "ERROR_COMMAND");
				}
			}
			break;
	}
	
	
}




