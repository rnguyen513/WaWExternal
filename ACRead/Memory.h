#pragma once
#include <Windows.h>

namespace Memory {
	class Mem {
	private:
		HANDLE hProcess;
	public:
		Mem(HANDLE hProcess);
		template <typename T> BOOL WPM(int BASE_ADDRESS, const T& buffer);
		template <typename T> T RPM(int BASE_ADDRESS);
	};

	DWORD GetProcessId(const wchar_t* processName);

	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
}