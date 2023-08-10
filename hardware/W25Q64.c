#include "stm32f10x.h"                  // Device header
#include "MySPI.h" 
#include "W25Q64_Ins.h" 

void W25Q64_Init(void){
	MySPI_Init();
	
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID){
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	MySPI_Stop();
}

void W25Q64_WriteEnable(void){
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_WaitBusy(void){
	uint32_t Timeout = 100000;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	while(MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01){
		if(!(Timeout--)){
			break;
		}
	}
	MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t Addr, uint8_t *DataArray, uint16_t Count){
	W25Q64_WaitBusy();
	W25Q64_WriteEnable();
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Addr >> 16);
	MySPI_SwapByte(Addr >> 8);
	MySPI_SwapByte(Addr);
	for(i=0;i<Count;i++){
		MySPI_SwapByte(*(DataArray+i));
	}
	MySPI_Stop();
}

void W25Q64_SectorErase(uint32_t Addr)
{
	W25Q64_WaitBusy();
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Addr>> 16);
	MySPI_SwapByte(Addr >> 8);
	MySPI_SwapByte(Addr);
	MySPI_Stop();	
}

void W25Q64_ReadData(uint32_t Addr, uint8_t *DataArray, uint32_t Count){
	W25Q64_WaitBusy();
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Addr >> 16);
	MySPI_SwapByte(Addr >> 8);
	MySPI_SwapByte(Addr);
	for(i=0;i<Count;i++){
		*(DataArray+i) = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}
