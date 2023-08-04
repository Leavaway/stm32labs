#ifndef _SERIAL_H
#define _SERIAL_H


void Serial_Init(void);
void Serial_SendData(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNum(uint32_t num, int16_t len);

#endif

	