// AccessMeasurements.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

#ifndef PAGE_SIZE
	#define PAGE_SIZE 0x1000
#endif // !PAGE_SIZE


int main()
{

	PVOID TargetMem = malloc(PAGE_SIZE * 10);

    printf("Press enter to continue...\n");

	_getch();

	UINT32 SampleTests = 1000;
	UINT32 SumOfExecTime = 0;

	for (size_t i = 0; i < SampleTests; i++)
	{
		DWORD64 StartTime =	__rdtsc();
		*(((CHAR*)(UINT64)TargetMem + i)) = i;
		DWORD64 EndTime = __rdtsc();

		DWORD64 TargetTime = EndTime - StartTime;
		SumOfExecTime += TargetTime;
		printf("Sample %d, took %d cycles\n", i, TargetTime);
	}

	printf("\n");
	printf("It took %d cycles to run %d accesses (On average %d cycles)", SumOfExecTime, SampleTests, SumOfExecTime / SampleTests);

	_getch();
}
