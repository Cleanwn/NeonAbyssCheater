#include "pch.h"
#include "ProcessUtil.h"
#include "TlHelp32.h"
#include "utility"
#include "vector"

DWORD ProcessUtil::GetProcessIDByTitle(LPCSTR lpWindowName, LPCSTR lpClassName)
{
	HWND w = FindWindowA(lpClassName, lpWindowName);
	if (w == nullptr) return 0;
	else {
		DWORD processId = 0;
		GetWindowThreadProcessId(w, &processId);
		return processId;
	}
}

std::pair<QWORD, QWORD> ProcessUtil::GetModule(DWORD processId, char* moduleName)
{
	HANDLE mod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);
	do {
		if (!strcmp(mEntry.szModule, moduleName))
		{
			return { (QWORD)mEntry.hModule, mEntry.modBaseSize };
		}
	} while (Module32Next(mod, &mEntry));
	return { 0, 0 };
}


QWORD ProcessUtil::ReadMultiLevelPointer(HANDLE pHandle, QWORD base, std::vector<QWORD> offsets)
{
	int len = offsets.size();
	for (int i = 0; i < len; i++) {
		if (i < len - 1) base = Read<QWORD>(pHandle, base + offsets[i]);
		else base = base + offsets[i];
	}
	return base;
}
