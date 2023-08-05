#include "stm32f10x.h"                  // Device header



void Serial_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//&SPI_CR2->RXNEIE = 1;
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendData(uint8_t Byte){
	USART_SendData(USART1, Byte);
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}

void Serial_SendArray(uint8_t *Array,uint16_t Length){
	uint16_t i;
	for(i=0;i<Length;i++){
		Serial_SendData(*(Array+i));
	}
}

void Serial_SendString(char *String){
	uint16_t i;
	for(i=0;*(String+i)!=0;i++){
		Serial_SendData(*(String+i));
	}
}

uint32_t Get_TenPow(int16_t i){
	uint32_t res = 1;
	while(i>0){
		res = res * 10;
		i--;
	}
	return res;
}

void Serial_SendNum(uint32_t num, int16_t len){
	int16_t i;
	for(i=len-1;i>=0;i--){
		Serial_SendData((num/Get_TenPow(i))+0x30);
		num = num % Get_TenPow(i);
	}
}

void Serial_SendPacket(uint8_t *packet){
	Serial_SendData(0xFF);
	Serial_SendArray(packet,4);
	Serial_SendData(0xFE);
}



