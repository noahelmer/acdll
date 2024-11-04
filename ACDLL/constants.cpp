#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);

extern Player* localPlayerPtr =*(Player**)(exeBaseAddress + 0x0017E0A8);

uintptr_t playersAddr = exeBaseAddress + 0x0018AC04;
extern EntityList* players = *(EntityList**)playersAddr;

extern int numPlayers = *(int*)(exeBaseAddress + 0x00191FD4);