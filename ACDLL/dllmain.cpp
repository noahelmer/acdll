// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <Windows.h>
#include "constants.h"
#include "genCode.h"
#include "esp.h"


void hook() {
    while (true) {
       ESP::aimbot();
       Sleep(150);
    }
}

void console() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    std::cout << "Console created" << std::endl;
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "exit") {
            break;
        }
        if (input == "up") {
            localPlayerPtr->position.y += 5;
        }
        if (input == "down") {
            localPlayerPtr->position.y -= 5;
        }
        if (input == "aimup") {
            localPlayerPtr->pitch += 5;
        }
        if (input == "aimdown") {
            localPlayerPtr->pitch -= 5;
        }
        if (input == "speedup") {
            localPlayerPtr->velocity.y += 5;
        }
        if (input == "speeddown") {
            localPlayerPtr->velocity.y -= 5;
        }
        if (input == "amount") {
            std::cout << "Number of players " << numPlayers << std::endl;
        }
        if (input == "ent") {
            for (int i = 1; i < numPlayers + 1; i++) {
                if (players->players[i] == nullptr || players->players[i]->vtable == nullptr) {
                    break;
                }
                std::cout << "Entity: " << i << ", " << players->players[i]<< std::endl;
                std::cout << "Pos: " << players->players[i]->position.x << " " << players->players[i]->position.y << " " << players->players[i]->position.z << std::endl;
                std::cout << "Player Health: " << players->players[i]->health << std::endl;
                std::cout << "Player Primary Ammo: " << players->players[i]->primaryammo << std::endl;
                std::cout << "Player Secondary Ammo: " << players->players[i]->secondaryammo << std::endl;
                std::cout << "\n" << std::endl;
            }

        }
    }
    FreeConsole();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, nullptr, 0, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

