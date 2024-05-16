//ACRead.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "extra.h"
#include "Memory.h"
#include "offests.h"
#include <cstdlib>
//#include <GLFW/glfw3.h>

using namespace extra;

HBRUSH brush;
HDC hdc;

int main()
{
    std::cout << "Staring client...\n";

    Sleep(1000);


    DWORD pid;                                                                  //get pid
    HWND targetWindow = FindWindowW(NULL, L"Call of Duty®");
    GetWindowThreadProcessId(targetWindow, &pid);

    std::cout << pid << std::endl;



    uintptr_t base_address;                                                     //get base address
    base_address = Memory::GetModuleBaseAddress(pid, L"CoDWaW.exe");
    std::cout << base_address << std::endl;
    HANDLE openProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);


    Memory::Mem memoryController(openProc);

    int points;                                                                 //playervars
    viewMatrix mtx;


    ////initialize glfw
    //GLFWwindow* window;

    //if (!glfwInit()) return -1;

    ////glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    //glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    //window = glfwCreateWindow(800,600, "ClearSSSSSSight", NULL, NULL);
    //if (!window) {
    //    glfwTerminate();
    //    return -1;
    //}

    //glfwMakeContextCurrent(window);

    RECT windowPos;

    while (!GetAsyncKeyState(VK_END)) {

        //overlay window stuff
        GetWindowRect(targetWindow, &windowPos);
        //glfwSetWindowPos(window, windowPos.left, windowPos.top);
        int height = windowPos.bottom - windowPos.top;
        int width = windowPos.right - windowPos.left;
        //glfwSetWindowSize(window, width, height);

        //glfwSetWindowOpacity(window, 0.5f);

        //glClear(GL_COLOR_BUFFER_BIT);


        points = memoryController.RPM<int>(base_address + OFFSET_POINTS);

        std::cout << "reading address: " << std::hex << "0x" << (base_address + OFFSET_POINTS);
        std::cout << ", points: "<< std::dec << points << std::endl;

        mtx = memoryController.RPM<viewMatrix>(VWMATRIX);

        int zombieCount = 0;
        for (int i = 0; i < 24; i++) {
            ent zombie = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(base_address + OFFSET_ENTITY_LIST + 0x88 * i));
            if (zombie.health > 0 && zombie.health < 50000 && zombie.health != 8304) {
                zombieCount++;
                std::cout << "zombie " << i << " health: " << zombie.health << ", position: "
                    << zombie.pos.toString() << std::endl;

                Vector2 zombieScreen;
                WorldToScreen(zombie.pos, zombieScreen, mtx.matrix, width, height);

                ////draw esp line
                //glLineWidth(2);
                //glBegin(GL_LINES);
                //glColor3f(1.0f, 1.0f, 1.0f);
                //glVertex2f(0, -1.0f);
                //glVertex2f(zombieScreen.x/width, zombieScreen.y/height);
                //glEnd();
            }
        }

        std::cout << "there are " << zombieCount << " zombies" << std::endl;


        ////actually render
        //glfwSwapBuffers(window);
        //glfwPollEvents();

        //Sleep(1);
        system("cls");
    }

    //glfwTerminate();
    return 0;
}