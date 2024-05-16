// ACRead.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "extra.h"
#include "Memory.h"
#include "offests.h"
#include <cstdlib>
#include <GLFW/glfw3.h>

using namespace extra;

int main()
{
    std::cout << "Staring client...\n";

    Sleep(1000);




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

    int points;
    viewMatrix mtx;
    viewMatrix_t mtx2;


    //initialize glfw

    GLFWwindow* window;

    if (!glfwInit()) return -1;

    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    window = glfwCreateWindow(800,600, "Clear Sight", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    RECT windowPos;

    while (!GetAsyncKeyState(VK_ESCAPE)) {

        //overlay window stuff
        GetWindowRect(targetWindow, &windowPos);
        glfwSetWindowPos(window, windowPos.left+3, windowPos.top+25);
        //glfwSetWindowOpacity(window, 0.5f);

        glClear(GL_COLOR_BUFFER_BIT);


        points = memoryController.RPM<int>(base_address + OFFSET_POINTS);

        std::cout << "reading address: " << std::hex << "0x" << (base_address + OFFSET_POINTS);
        std::cout << ", points: "<< std::dec << points << std::endl;

        //entlist contains pointers to actual zombies
        //zombie1 = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(base_address + OFFSET_ENTITY_LIST));

        mtx = memoryController.RPM<viewMatrix>(VWMATRIX);
        mtx2 = memoryController.RPM<viewMatrix_t>(VWMATRIX);

        int zombieCount = 0;
        for (int i = 0; i < 24; i++) {
            ent zombie = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(base_address + OFFSET_ENTITY_LIST + 0x88 * i));
            if (zombie.health > 0 && zombie.health < 50000 && zombie.health != 8304) {
                zombieCount++;
                std::cout << "zombie " << i << " health: " << zombie.health << ", position: "
                    << zombie.pos.toString() << std::endl;

                Vector3 zombieWTS = WorldToScreen(zombie.pos, mtx);

                std::cout << "ZOMBIE REGULAR VEC3: " << zombie.pos.toString() << std::endl;
                std::cout << "ZOMBIEWTS: " << zombieWTS.toString() << std::endl;

                Vector2 zombieWTS2 = WTS(zombie.pos, mtx2);
                std::cout << "NEW WTS: " << zombieWTS2.x << ", " << zombieWTS2.y << std::endl;

                if (zombieWTS.z < 0.01f) continue;

                //draw esp line
                glLineWidth(2);
                glBegin(GL_LINES);
                glColor3f(1.0f, 0.0f, 1.0f);
                //glVertex2f(0, -0.95f);
                //glVertex2f(0.5f, 0.5f);
                glVertex3f(0.0f, -0.95f, 0);
                //glVertex3f(0.5f, 0.5f, -0.8f);
                glVertex3f(zombieWTS.x/800-0.5, zombieWTS.y/600-0.5, 0);
                //glVertex2f(zombieWTS2.x / 800, zombieWTS2.y / 600);
                glEnd();
            }
        }

        std::cout << "there are " << zombieCount << " zombies" << std::endl;

        //mtx = memoryController.RPM<viewMatrix>(VWMATRIX);

        //std::cout << mtx.matrix[0] << ", " << mtx.matrix[1] << std::endl;



        ent zombie1 = memoryController.RPM<ent>(memoryController.RPM<uintptr_t>(base_address + OFFSET_ENTITY_LIST));

        std::cout << "ZOMBIE1 world to screen: " << WorldToScreen(zombie1.pos, mtx).toString() << std::endl;

        //glLineWidth(2);
        //glBegin(GL_LINES);
        //glColor3f(0, 1.0f, 0);
        //glVertex2f(0, 0);
        //glVertex2f(0, 0.5f);
        //glEnd();


        //actually render
        glfwSwapBuffers(window);
        glfwPollEvents();

        //Sleep(1);
        system("cls");
    }

    glfwTerminate();
    return 0;
}