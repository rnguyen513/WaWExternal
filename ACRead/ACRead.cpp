#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "util.h"
#include "Memory.h"
#include "offests.h"
#include <cstdlib>
//#include <GLFW/glfw3.h>

using namespace util;

HBRUSH brush;
HPEN pen;
HDC hdc;

int main()
{
    std::cout << "Staring client...\n";

    Sleep(1000);


    Memory::Mem memoryController(L"Call of Duty®", L"CoDWaW.exe");          //all in one memory manager

    std::cout << "base address: " << memoryController.base_address << std::endl;
    std::cout << "press B to toggle boxes, L to toggle lines" << std::endl;
    std::cout << "press END to stop" << std::endl;

    //player variables
    int points;
    viewMatrix mtx;



    //draw boxes/lines?
    bool drawboxes = true;
    bool drawlines = true;


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
    hdc = GetDC(memoryController.hwnd);

    while (!GetAsyncKeyState(VK_END)) {

        //overlay window stuff
        GetWindowRect(memoryController.hwnd, &windowPos);
        //glfwSetWindowPos(window, windowPos.left, windowPos.top);
        int height = windowPos.bottom - windowPos.top;
        int width = windowPos.right - windowPos.left;
        //glfwSetWindowSize(window, width, height);
        //glfwSetWindowOpacity(window, 0.5f);


        //CLEAR FRAME BEFORE RERENDER
        //glClear(GL_COLOR_BUFFER_BIT);




        //gdi init
        DeleteObject(hdc);
        hdc = GetDC(memoryController.hwnd);

        points = memoryController.RPM<int>(memoryController.base_address + OFFSET_POINTS);
        mtx = memoryController.RPM<viewMatrix>(VWMATRIX);

        if (GetAsyncKeyState('L') & 0x8000) drawlines ^= true;
        if (GetAsyncKeyState('B') & 0x8000) drawboxes ^= true;
        DrawZombies(memoryController, mtx, width, height, pen, brush, hdc, drawlines, drawboxes);

    }

    //glfwTerminate();

    ReleaseDC(memoryController.hwnd, hdc);
    return 0;
}