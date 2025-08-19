#include "pch.h"
#include "ProcessUtils.h"

DWORD ProcessUtils::GetProcessIDByTitle(LPCSTR lpWindowName, LPCSTR lpClassName)
{
	HWND w = FindWindowA(lpClassName, lpWindowName);
	if (w == nullptr) return 0;
	else {
		DWORD processId = 0;
		GetWindowThreadProcessId(w, &processId);
		return processId;
	}
}

std::pair<QWORD, QWORD> ProcessUtils::GetModule(DWORD processId, char* moduleName)
{
	return std::pair<QWORD, QWORD>();
}
