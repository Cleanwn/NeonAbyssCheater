#pragma once
class ProcessUtils
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
	static T ReadMem(HANDLE pHandle, QWORD address);

	/*
	Write value T to address in process handle
	*/
	template<typename T>
	static BOOL Write(HANDLE pHandle, QWORD address, T value);

	/*
	Get the result address from multiple level pointers.
	*/
	static QWORD ReadMultiLevelPointer(HANDLE pHandle, QWORD base, std::vector<QWORD> offsets);
};

