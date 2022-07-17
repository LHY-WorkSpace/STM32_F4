#ifndef   _SYSTEMSTATE_H_
#define   _SYSTEMSTATE_H_

#define ROM_BASE_ADDR  (0x08000000)
#define ROM_END_ADDR   (0x08060000)

#define PLACE_CODE_IN_USER_ROM  __attribute__ ((section("USER_ROM")))//放置升级代码区域


void SystemDown(void);
void SW_Reset(void);
u32 CRC32_GetValue(u32 *pBuffer, u32 BufferLength);
u32 GetROMCheckSum(u32 StartAddr,u32 EndtAddr);
#endif
