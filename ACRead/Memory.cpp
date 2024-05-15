#include "Memory.h"
#include <Windows.h>
#include <TlHelp32.h>

namespace Memory {

	Mem::Mem(HANDLE hProcess) : hProcess(hProcess) {};

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

    // Function to get the base address of the process by its PID
    //uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
    //    uintptr_t modBaseAddr = 0;
    //    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    //    if (hSnap != INVALID_HANDLE_VALUE) {
    //        MODULEENTRY32 modEntry;
    //        modEntry.dwSize = sizeof(modEntry);
    //        if (Module32First(hSnap, &modEntry)) {
    //            do {
    //                if (!_wcsicmp(modEntry.szModule, modName)) {
    //                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
    //                    break;
    //                }
    //            } while (Module32Next(hSnap, &modEntry));
    //        }
    //    }
    //    CloseHandle(hSnap);
    //    return modBaseAddr;
    //}

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