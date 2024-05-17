#include "Memory.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

namespace Memory {

	//Mem::Mem(HANDLE hProcess) : hProcess(hProcess) {};

    Mem::Mem(LPCWSTR windowName, LPCWSTR moduleName) {

        HWND targetWindow = FindWindowW(NULL, windowName);                      //pid stuff
        GetWindowThreadProcessId(targetWindow, &this->pid);
        this->hwnd = targetWindow;
        std::cout << "pid: " << pid << std::endl;

        HANDLE openProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);          //open handle to process using pid
        this->hProcess = openProc;

        this->base_address = Memory::GetModuleBaseAddress(pid, moduleName);     //base address
        //std::cout << "base_address: " << base_address << std::endl;
    }

    // Utility function to find the process ID by the game's executable name
    DWORD GetProcessId(const wchar_t* processName) {
        PROCESSENTRY32 processInfo;
        processInfo.dwSize = sizeof(processInfo);

        HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (processesSnapshot == INVALID_HANDLE_VALUE) {
            return 0;
        }

        Process32First(processesSnapshot, &processInfo);
        if (!wcscmp(processName, processInfo.szExeFile)) {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }

        while (Process32Next(processesSnapshot, &processInfo)) {
            if (!wcscmp(processName, processInfo.szExeFile)) {
                CloseHandle(processesSnapshot);
                return processInfo.th32ProcessID;
            }
        }

        CloseHandle(processesSnapshot);

        return 0;
    }

    uintptr_t GetModuleBaseAddress(DWORD dwPid, const wchar_t* moduleName) {
        uintptr_t dwBase = 0;
        do {
            HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwPid);
            if (hSnapshot == INVALID_HANDLE_VALUE) { continue; }
            MODULEENTRY32 ModuleEntry32;
            ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
            if (Module32First(hSnapshot, &ModuleEntry32)) {
                do {
                    if (!_wcsicmp(ModuleEntry32.szModule, moduleName)) {
                        dwBase = (DWORD)ModuleEntry32.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnapshot, &ModuleEntry32));
            }
            CloseHandle(hSnapshot);
        } while (!dwBase);
        return dwBase;
    }
}