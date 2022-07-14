#ifndef   _SYSTEMSTATE_H_
#define   _SYSTEMSTATE_H_

#define ROM_BASE_ADDR  (0x08000000)
#define ROM_END_ADDR   (0x08080000)

void SystemDown(void);
void SW_Reset(void);
u32 CRC32_GetValue(u32 *pBuffer, u32 BufferLength);
#endif
