#pragma once
#include <cstdint>
#include <Windows.h>
#include "genCode.h"

extern HMODULE hModule;
extern uintptr_t exeBaseAddress;

extern Player* localPlayerPtr;
extern EntityList* players;
extern int numPlayers;