# TRM-results

This repository contains different results for the TRM (The Reversing Machine) paper.

## The compiled version of code (Compilation)

This directory contains compilations of example codes using different compilers and architecture (x86, x64).

The compilers are listed below:

| Compiler              | Architecture |
|-----------------------|--------------|
| Intel oneAPI C++      | x86/x64      |
| LLVM-clang            | x86/x64      |
| Microsoft MSVC        | x86/x64      |
| PellesC               | x64          |
| TDM-GCC               | x86/x64      |
| TinyCC                | x86/x64      |

## Different forms of memory allocations (DifferentUserMemoryAllocations)

This directory contains code that uses different functions/methods for allocating memory.

| Function Name      | Category               |
|--------------------|------------------------|
| `malloc`           | Standard C Library     |
| `calloc`           | Standard C Library     |
| `realloc`          | Standard C Library     |
| `LocalAlloc`       | Windows API            |
| `GlobalAlloc`      | Windows API            |
| `VirtualAlloc`     | Windows API            |
| `MapViewOfFile`    | Windows API            |
| `HeapAlloc`        | Windows API            |
| `CoTaskMemAlloc`   | COM Memory Allocator   |


## Malware evasion techniques (In-memory)

This directory contains different implementations of malware evasion techniques (Using an obfuscated version of [mimikatz](https://github.com/gentilkiwi/mimikatz)).

| Technique                          | Detail Ref.                            |
|------------------------------------|----------------------------------------|
| APC Code Injection                 | ***                                    |
| Early bird APC Code Injection      | (CreateProcessA -> WriteProcessMemory -> QueueUserAPC -> ResumeThread) |
| Process Injection                  | (OpenProcess -> VirtualAllocEx -> WriteProcessMemory -> CreateRemoteThread, NtCreateThreadEx, or RtlCreateUserThread) |
| Load PE From Resource              | (FindResource -> SizeofResource -> LoadResource -> VirtualAlloc) |
| Reflective DLL Injection           | ***                                    |
| Module Stomping                    | ***                                    |
| Process Hollowing                  | ***                                    |
| Process Doppelgänging              | ***                                    |
| Transacted Hollowing               | ***                                    |
| Process Herpaderping               | ***                                    |
| Process Ghosting                   | ***                                    |
| Phantom DLL Hollowing              | ***                                    |
| Custom XOR Encoder/Decoder         | Custom Encoder/Decoder                 |
| Process Reimaging                  | ***                                    |
| Module Execution Through Fibers    | (ConvertThreadToFiber -> VirtualAlloc -> CreateFiber) |
| Module Execution Through Thread Pool | (CreateEvent -> VirtualAlloc -> CreateThreadpoolWait -> SetThreadpoolWait) |
| Window Hooking                     | (LoadLibraryA -> GetProcAddress -> SetWindowsHookEx) |
| Map View of Section                | (NtCreateSection -> NtMapViewOfSection -> RtlCreateUserThread) |

***: Discussed comprehensively in the paper. 

## Longest Common Memory Address Pattern (LCMAP)

The implementation of the proposed Longest Common Memory Address Pattern (LCMAP) algorithm, discussed in the paper.

```plaintext
function findLCMAP(P, P', tau)
    input:
        P   // First memory address pattern
        P'  // Second memory address pattern
        tau // Memory alignment threshold
    output:
        Result // LCMAP of the input patterns

    m, n <- len(P), len(P')           // Sizes of the input patterns
    D <- zeros(m, n)                        // Initialize m x n zero matrix

    for i from 1 to m do
        for j from 1 to n do
            if near(P[i-1], P'[j-1], tau) then
                D[i, j] <- D[i-1, j-1] + 1  // Signature matched
            else
                D[i, j] <- 0                // Signature not matched

    L <- max(D)                             // Length of the LCMAP
    I <- min{i | D[i, j] = L}               // Tail address of the LCMAP
    Result <- [P[I-L+1], ..., P[I]]         // The LCMAP
    return Result
```

## Reconstruction of `nt!_EPROCESS` (StructureReconstruction)

This directory contains an example of a reconstructed kernel-mode structure (`nt!_EPROCESS`) along with the actual structure retrieved from the Microsoft public symbol server.

## Sequence Interpreter (sequence-interpreter)

This directory contains the source of the memory access sequence interpreter (based on logs gathered from TRM).
