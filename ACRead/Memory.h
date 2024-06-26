#pragma once
#include <Windows.h>

namespace Memory {
	class Mem {
	private:
		HANDLE hProcess;
	public:
		DWORD pid;
		uintptr_t base_address;
		HWND hwnd;

		Mem(LPCWSTR windowName, LPCWSTR moduleName);

		template <typename T> BOOL WPM(int BASE_ADDRESS, const T& buffer) {
			SIZE_T bytez;
			BOOL result = WriteProcessMemory(this->hProcess, (LPCVOID)BASE_ADDRESS, buffer, sizeof(buffer), &bytez);

			return result && (bytez == sizeof(buffer));
		}

		template <typename T> T RPM(int BASE_ADDRESS) {
			T result;
			SIZE_T bytez;
			BOOL success = ReadProcessMemory(this->hProcess, (LPCVOID)BASE_ADDRESS, &result, sizeof(T), &bytez);

			return result;
		}
	};

	DWORD GetProcessId(const wchar_t* processName);
	uintptr_t GetModuleBaseAddress(DWORD dwPid, const wchar_t* moduleName);
}