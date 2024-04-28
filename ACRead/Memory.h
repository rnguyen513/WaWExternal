#pragma once
#include <Windows.h>

namespace Memory {
	class Mem {
	private:
		Mem(HANDLE hProcess);
		HANDLE hProcess;
	public:
		template <typename T> BOOL WPM(LPVOID BASE_ADDRESS, const T& value);
		template <typename T> T RPM(LPVOID BASE_ADDRESS);
	};

	DWORD GetProcessId(const wchar_t* processName);

	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
}