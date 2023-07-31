#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "key.h"

int16_t i;
float angle;
uint8_t KeyNum;
int8_t speed;


void Motor_Speed(int8_t speed){
	if(speed>=0){
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_Set_Compare(speed);
		OLED_ShowString(1,1,"Speed is posi");
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		PWM_Set_Compare(-speed);
		OLED_ShowString(1,1,"Speed is nega");
	}
	
}

int main(void) {
	OLED_Init();
	PWM_Init();
	Motor_Speed(0);
    while(1){
		KeyNum = KEY_GetNum();
		if(KeyNum == 1){
			speed+=20;
			if(speed>100){
				speed = -100;
			}
			Motor_Speed(speed);
			
		}
		OLED_ShowSignedNum(2,3,speed,3);
	}; // Add infinite loop at the end to keep the microcontroller running

    return 0;
}



