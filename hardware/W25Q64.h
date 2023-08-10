#ifndef _W25Q64_H
#define _W25Q64_H

void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q64_PageProgram(uint32_t Addr, uint8_t *DataArray, uint16_t Count);
void W25Q64_SectorErase(uint32_t Addr);
void W25Q64_ReadData(uint32_t Addr, uint8_t *DataArray, uint32_t Count);


#endif
