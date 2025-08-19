#pragma once
#include "TlHelp32.h"
#include "utility"
#include "vector"
#include "pch.h"

class ProcessUtil
{
public:
	/*
	get ProcessID By Process Title:
	Params:
	1. lpWindowName: The title of process window
	2. lpClassName:  The Class of process window(default NULL)
	Return: if not exists return 0, otherwise return real process ID.
	*/
	static DWORD GetProcessIDByTitle(LPCSTR lpWindowName, LPCSTR lpClassName = nullptr);

	/*
	Get the module infomation in a process.
	Return a pair info of process, the 1st entry is base address and the second is the size of module.
	*/
	static std::pair<QWORD, QWORD> GetModule(DWORD processId, char* moduleName);

	/*
	Read value from specific address of process handle
	*/
	template<typename T>
	static T Read(HANDLE pHandle, QWORD address) {
		T _read = 0;
		ReadProcessMemory(pHandle, (LPVOID)address, &_read, sizeof(T), NULL);
		return _read;
	}

	/*
	Write value T to address in process handle
	*/
	template<typename T>
	static BOOL Write(HANDLE pHandle, QWORD address, T value) {
		return WriteProcessMemory(pHandle, (LPVOID)address, &value, sizeof(T), NULL);
	}

	/*
	Get the result address from multiple level pointers.
	*/
	static QWORD ReadMultiLevelPointer(HANDLE pHandle, QWORD base, std::vector<QWORD> offsets);
};