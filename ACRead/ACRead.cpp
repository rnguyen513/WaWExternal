// ACRead.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "extra.h"
#include "Memory.h"
#include "offests.h"
#include <cstdlib>

using namespace extra;

int main()
{
    std::cout << "Staring client...\n";

    Sleep(1000);

    //Dog myDawg("dawggie", 14);
    //cout << myDawg.getName() << myDawg.getAge();
    //cout << myDawg.getName() << " " << myDawg.getAge() << endl;



    //get pid
    DWORD pid;
    HWND targetWindow = FindWindowW(NULL, L"Call of Duty®");
    GetWindowThreadProcessId(targetWindow, &pid);

    std::cout << pid << std::endl;



    ////get base address
    uintptr_t base_address;
    base_address = Memory::GetModuleBaseAddress(pid, L"CoDWaW.exe");

    std::cout << base_address << std::endl;

    HANDLE openProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    Memory::Mem memoryController(openProc);

    //INT8 health;
    //INT8 ammo;
    int points;

    viewMatrix mtx;

    while (!GetAsyncKeyState(VK_ESCAPE)) {

        //health = memoryController.RPM<INT8>((OFFSET_PLAYERBASEADDRESS+PLAYER_HEALTH_OFFSET));

        //cout << "player health: " << health;

        points = memoryController.RPM<int>(base_address + OFFSET_POINTS);

        std::cout << "reading address: " << std::hex << "0x" << (base_address + OFFSET_POINTS);
        std::cout << ", points: "<< std::dec << points << std::endl;

        //entlist contains pointers to actual zombies
        //zombie1 = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(base_address + OFFSET_ENTITY_LIST));

        int zombieCount = 0;
        for (int i = 0; i < 24; i++) {
            ent zombie = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(base_address + OFFSET_ENTITY_LIST + 0x88 * i));
            if (zombie.health > 0 && zombie.health < 50000 && zombie.health != 8304) {
                zombieCount++;
                std::cout << "zombie " << i << " health: " << zombie.health << ", position: "
                    << zombie.pos.toString() << std::endl;
            }
        }

        std::cout << "there are " << zombieCount << " zombies" << std::endl;

        mtx = memoryController.RPM<viewMatrix>(VWMATRIX);

        std::cout << mtx.matrix[0].x << ", " << mtx.matrix[2].z << std::endl;

        Sleep(1000);
        system("cls");
    }
}