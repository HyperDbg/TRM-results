#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <x86intrin.h>

#define NUMBER_OF_TEST_CASES 10000

void write_into_file(int fd) {
    char buffer[16]; // Buffer to hold each line (enough for "i\n")
    for (int i = 1; i <= 1000; ++i) {
        int len = snprintf(buffer, sizeof(buffer), "%d\n", i);
        write(fd, buffer, len);
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
    // Show process ID and wait for starting stage of the measurement
    //
    printf("Start measuring from process ID: 0x%llx\n", (unsigned long long)getpid());
    printf("Press enter to start the measurement...");
    // getchar();

    for (size_t i = 0; i < NUMBER_OF_TEST_CASES; i++) {

        //
        // Open the file (O_CREAT | O_TRUNC will replace it if it exists)
        //
        int fd = open("Test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error: Couldn't open the file");
            return 1;
        }

        //
        // Start the RDTSC timer
        //
        uint64_t start = rdtsc_start();

        //
        // Write into the file
        //
        write_into_file(fd);

        //
        // Close the file descriptor
        //
        close(fd);

        //
        // Stop the RDTSC timer
        //
        uint64_t end = rdtsc_end();

        total_clks += end - start;
    }

    //
    // Calculate and print the elapsed time in CPU cycles
    //
    printf("Average time taken to write into the file (in CPU cycles): %llu\n", total_clks / NUMBER_OF_TEST_CASES);
    printf("Finished writing into the file.\n");
    // getchar();

    return 0;
}

