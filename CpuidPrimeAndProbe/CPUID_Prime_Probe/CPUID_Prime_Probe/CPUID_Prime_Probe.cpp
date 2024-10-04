#include <stdio.h>
#include <stdint.h>
#include <windows.h>  // For Windows threading and memory alignment
#include <malloc.h>   // For _aligned_malloc and _aligned_free
#include <intrin.h>   // For _aligned_malloc and _aligned_free

#define CACHE_LINE_SIZE 64
#define LLC_SIZE (10 * 1024 * 1024)  // Assuming 20 MB for the LLC (adjust based on your CPU)
#define REPEATS 1000  // Number of iterations to repeat the entire test

// Global variables for the timing thread
volatile uint64_t counter = 0;  // The counter incremented by the timing thread
volatile int stop_counter = 0;  // Flag to stop the timing thread

// Function to run CPUID (MSVC inline assembly version)
void run_cpuid() {
    int info[4];
    __cpuid(info, 0);  // CPUID function with EAX=0
}

// Memory fence to ensure serialization of instructions
inline void mfence() {
    _ReadWriteBarrier();  // MSVC equivalent of memory barrier
}

// Function to prime the cache by accessing memory and ensure it is not optimized out
void prime_cache(uint8_t* array, int size) {
    for (int i = 0; i < size; i += CACHE_LINE_SIZE) {
        _ReadWriteBarrier();  // Memory barrier
        volatile uint8_t temp = array[i];  // Force the access to happen
        (void)temp;  // Prevent unused variable warning
    }
}

// Timing thread function: continuously increments the counter until stopped
DWORD WINAPI timing_thread(LPVOID lpParam) {

    while (TRUE == TRUE) {
        while (!stop_counter) {
            counter++;
        }
    }
    return 0;
}

// Function to measure access times for each element in the array using timing threads
void probe_cache_with_timing(uint8_t* array, int size, int use_cpuid, FILE* fp) {
    HANDLE thread;
    DWORD threadId;
    int num_cache_lines = size / CACHE_LINE_SIZE;

    // Start the timing thread
    counter = 0;
    stop_counter = 0;
    thread = CreateThread(NULL, 0, timing_thread, NULL, 0, &threadId);
    if (thread == NULL) {
        perror("Failed to create timing thread");
        return;
    }

    // Prime the cache
    prime_cache(array, size);

    // Optionally run CPUID to cause cache eviction
    if (use_cpuid) {
        for (int i = 0; i < 2; i++) {
            run_cpuid();
        }
    }

    // Measure the access time for each cache line
    for (int i = 0; i < num_cache_lines; i++) {
        // Reset the counter before measuring access time
        counter = 0;
        mfence();  // Ensure all instructions before are completed
        volatile uint8_t temp = array[i * CACHE_LINE_SIZE];  // Access array (critical section)
        mfence();  // Ensure the memory access is completed

        // wait until the other thread starts to run
		while (counter == 0) {
			// Do nothing
		}

        stop_counter = 1;  // Stop the timing thread right after access

        // Log the counter value after stopping the timer
        if (i == num_cache_lines - 1) {

            fprintf(fp, "%llu", counter);  // No trailing comma on the last element
        }
        else {
            fprintf(fp, "%llu, ", counter);  // Trailing comma for other elements
        }

        stop_counter = 0;  // Reset the stop flag for the next iteration
    }

    // Signal the timing thread to stop
    stop_counter = 1;
    // WaitForSingleObject(thread, INFINITE);  // Wait for the timing thread to finish
    // CloseHandle(thread);

    fprintf(fp, "\n");
}

int main() {
    // Allocate aligned memory for cache priming (aligned to cache line size)
    uint8_t* array = (uint8_t*)_aligned_malloc(LLC_SIZE, CACHE_LINE_SIZE);
    if (array == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Open the file to write timing results
    FILE* fp = fopen("timing_results.csv", "w");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Repeat the entire test REPEATS times
    for (int repeat = 0; repeat < REPEATS; repeat++) {
        // Measure timing without CPUID (baseline)
        prime_cache(array, LLC_SIZE);  // Prime the cache
        probe_cache_with_timing(array, LLC_SIZE, 0, fp);  // Measure time without CPUID

        // Measure timing with CPUID (after eviction)
        prime_cache(array, LLC_SIZE);  // Prime the cache
        probe_cache_with_timing(array, LLC_SIZE, 1, fp);  // Measure time with CPUID
    }

    // Close the file and free memory
    fclose(fp);
    _aligned_free(array);

    return 0;
}
