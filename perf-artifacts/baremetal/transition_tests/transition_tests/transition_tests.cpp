#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <intrin.h>

#define NUMBER_OF_TEST_CASES 10000

void write_into_file(HANDLE hFile) {

	//
	// Buffer to hold the written data
	//
	DWORD dwBytesWritten = 0;
	char buffer[16];  // Buffer to hold each line (enough for "i\n")

	//
	// Write 1000 lines in a loop
	//
	for (int i = 1; i <= 1000; ++i) {

		//
		// Create the string "i\n"
		//
		int len = sprintf(buffer, "%d\n", i);

		//
		// Write the string to file
		//
		WriteFile(hFile, buffer, len, &dwBytesWritten, NULL);
	}
}

static inline uint64_t rdtsc_start() {
	unsigned int aux;
	return __rdtscp(&aux); // Start timestamp using RDTSCP to serialize
}

static inline uint64_t rdtsc_end() {
	unsigned int aux;
	uint64_t end = __rdtscp(&aux); // End timestamp
	_mm_lfence(); // Serialize to ensure timing is captured accurately
	return end;
}

int main() {

	uint64_t total_clks = 0;

	//
	// Set the thread to run on the 0th core
	//
	DWORD_PTR affinityMask = 1; // Binary 0001, sets affinity to core 0
	SetThreadAffinityMask(GetCurrentThread(), affinityMask);

	//
	// Show process id and wait for starting stage of the measurement
	//
	printf("start measuring from process id: 0x%llx\n", GetCurrentProcessId());
	printf("press enter to start the measurement...");
	_getch();

	for (size_t i = 0; i < NUMBER_OF_TEST_CASES; i++)
	{

		//
		// File handle
		//
		HANDLE hFile;

		//
		// Create a file (or replace if exists)
		//
		hFile = CreateFileA("Test.txt",               // Filename
			GENERIC_WRITE,            // Desired access
			0,                        // Share mode
			NULL,                     // Security attributes
			CREATE_ALWAYS,            // Creation disposition (overwrite if exists)
			FILE_ATTRIBUTE_NORMAL,    // Flags
			NULL);                    // Template file

		//
		// Check if file is created successfully
		//
		if (hFile == INVALID_HANDLE_VALUE) {
			printf("Error: Couldn't open the file.\n");
			return 1; // Error, couldn't open the file
		}

		// printf("Writing into the file...\n");

		//
		// Start the RDTSC timer
		//
		uint64_t start = rdtsc_start();

		//
		// Write into the file
		//
		write_into_file(hFile);

		//
		// Close the file handle
		//
		CloseHandle(hFile);

		//
		// Stop the RDTSC timer
		//
		uint64_t end = rdtsc_end();

		total_clks += end - start;

	}

	//
	// Calculate and print the elapsed time in CPU cycles
	//
	printf("Avrage time taken to write into the file (in CPU cycles): %llu\n", total_clks / NUMBER_OF_TEST_CASES);
	printf("Finished writing into the file.\n");
	_getch();

	return 0;
}
