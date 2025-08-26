#include <stdint.h>

uint64_t rdtscp() {
    unsigned int aux;
    uint32_t lo, hi;

    // Assembly instruction for RDTSCP
    __asm__ volatile("rdtscp" : "=a" (lo), "=d" (hi) : : "%rcx");

    return ((uint64_t)hi << 32) | lo;
}
