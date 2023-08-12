#include "stm32f10x.h"                  // Device header
#include <time.h>

uint16_t MyRTC_Time[] = {2023,1,1,23,59,55};

void MyRTC_SetTime(void);

void MyRTC_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if(BKP_ReadBackupRegister(BKP_DR1)==0x1111){
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		return;
	}
	
	RCC_LSEConfig(RCC_LSE_ON);
	
	while(!RCC_GetFlagStatus(RCC_FLAG_LSERDY));
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	
	RTC_SetPrescaler(32768 - 1);
	RTC_WaitForLastTask();
	
	RTC_SetCounter(1672588795);
	RTC_WaitForLastTask();
	
	BKP_WriteBackupRegister(BKP_DR1,0x1111);
	
	
}

void MyRTC_SetTime(void){
	time_t time_cnt;
	struct tm time_date;
	
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_mon = MyRTC_Time[1]-1;
	time_date.tm_sec = MyRTC_Time[5];
	time_date.tm_year = MyRTC_Time[0]-1900;
}

void MyRTC_ReadTime(void){
	time_t time_cnt = RTC_GetCounter();
	struct tm time_date = *localtime(&time_cnt);
	
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[1] = time_date.tm_mon+1;
	MyRTC_Time[5] = time_date.tm_sec;
	MyRTC_Time[0] = time_date.tm_year+1900;
}
