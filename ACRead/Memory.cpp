#include "Memory.h"
#include <Windows.h>
#include <TlHelp32.h>

namespace Memory {

	Mem::Mem(HANDLE hProcess) : hProcess(hProcess) {};

	template <typename T> BOOL Mem::WPM(LPVOID BASE_ADDRESS, const T& value) {
		SIZE_T bytez;
		BOOL result = WriteProcessMemory(this->hProcess, BASE_ADDRESS, value, sizeof(value), &bytez);

		return result && (bytez == sizeof(buffer));
	}

	template <typename T> T Mem::RPM(LPVOID BASE_ADDRESS) {
		T result;
		SIZE_T bytez;
		BOOL result = ReadProcessMemory(this->hProcess, BASE_ADDRESS, &result, sizeof(T), &bytez);

		return result;
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

    // Function to get the base address of the process by its PID
    uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);
            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!_wcsicmp(modEntry.szModule, modName)) {
                        modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
        CloseHandle(hSnap);
        return modBaseAddr;
    }
}