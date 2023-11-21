#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {

    //
    // Software Breakpoint
    //
    DebugBreak();

    //
    // Using malloc
    //
    // printf("Allocate memory using malloc\n");
    DebugBreak();

    int* arr1 = (int*)malloc(0x2555);
    if (arr1 == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    //
    // Using calloc
    //
    // printf("Allocate memory using calloc\n");
    DebugBreak();

    int* arr2 = (int*)calloc(5, 0x2555);
    if (arr2 == NULL) {
        fprintf(stderr, "calloc failed\n");
        free(arr1);
        return 1;
    }

    //
    // Using realloc
    //
    // printf("Allocate memory using realloc\n");
    DebugBreak();

    int* arr3 = (int*)realloc(arr2, 0x2555);
    if (arr3 == NULL) {
        fprintf(stderr, "realloc failed\n");
        free(arr1);
        free(arr2);
        return 1;
    }

    //
    // Using LocalAlloc (Windows API)
    //
    // printf("Allocate memory using LocalAlloc\n");
    DebugBreak();

    HLOCAL localMem = LocalAlloc(LPTR, 0x2555);
    if (localMem == NULL) {
        fprintf(stderr, "LocalAlloc failed\n");
        free(arr1);
        free(arr3);
        return 1;
    }

    //
    // Using GlobalAlloc (Windows API)
    //
    // printf("Allocate memory using GlobalAlloc\n");
    DebugBreak();

    HGLOBAL globalMem = GlobalAlloc(GPTR, 0x2555);
    if (globalMem == NULL) {
        fprintf(stderr, "GlobalAlloc failed\n");
        free(arr1);
        LocalFree(localMem);
        free(arr3);
        return 1;
    }

    //
    // Using VirtualAlloc (Windows API)
    //
    // printf("Allocate memory using VirtualAlloc\n");
    DebugBreak();

    LPVOID virtualMem = VirtualAlloc(NULL, 0x2555, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (virtualMem == NULL) {
        fprintf(stderr, "VirtualAlloc failed\n");
        free(arr1);
        LocalFree(localMem);
        GlobalFree(globalMem);
        free(arr3);
        return 1;
    }

    //
    // Using MapViewOfFile (Windows API)
    //
    // printf("Prepare allocation using CreateFileMapping\n");
    DebugBreak();

    HANDLE fileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x2555, NULL);
    if (fileMapping == NULL) {
        fprintf(stderr, "CreateFileMapping failed\n");
        free(arr1);
        LocalFree(localMem);
        GlobalFree(globalMem);
        VirtualFree(virtualMem, 0, MEM_RELEASE);
        free(arr3);
        return 1;
    }

    // printf("Allocate memory using MapViewOfFile\n");
    DebugBreak();

    LPVOID mappedFileMem = MapViewOfFile(fileMapping, FILE_MAP_WRITE, 0, 0, 0x2555);
    if (mappedFileMem == NULL) {
        fprintf(stderr, "MapViewOfFile failed\n");
        free(arr1);
        LocalFree(localMem);
        GlobalFree(globalMem);
        VirtualFree(virtualMem, 0, MEM_RELEASE);
        CloseHandle(fileMapping);
        free(arr3);
        return 1;
    }

    //
    // Using HeapAlloc (Windows API)
    //


    // printf("Prepare allocation using GetProcessHeap\n");
    DebugBreak();

    HANDLE heap = GetProcessHeap();

    // printf("Allocate memory using HeapAlloc\n");
    DebugBreak();

    LPVOID heapMem = HeapAlloc(heap, HEAP_ZERO_MEMORY, 0x2555);
    if (heapMem == NULL) {
        fprintf(stderr, "HeapAlloc failed\n");
        free(arr1);
        LocalFree(localMem);
        GlobalFree(globalMem);
        VirtualFree(virtualMem, 0, MEM_RELEASE);
        CloseHandle(fileMapping);
        UnmapViewOfFile(mappedFileMem);
        free(arr3);
        return 1;
    }

    //
    // Using CoTaskMemAlloc (COM Memory Allocator)
    //
    // printf("Allocate memory using CoTaskMemAlloc\n");
    DebugBreak();

    LPVOID coTaskMem = CoTaskMemAlloc(0x2555);
    if (coTaskMem == NULL) {
        fprintf(stderr, "CoTaskMemAlloc failed\n");
        free(arr1);
        LocalFree(localMem);
        GlobalFree(globalMem);
        VirtualFree(virtualMem, 0, MEM_RELEASE);
        CloseHandle(fileMapping);
        UnmapViewOfFile(mappedFileMem);
        HeapFree(heap, 0, heapMem);
        free(arr3);
        return 1;
    }

    //
    // Clean up
    //
    DebugBreak();

    free(arr1);
    LocalFree(localMem);
    GlobalFree(globalMem);
    VirtualFree(virtualMem, 0, MEM_RELEASE);
    CloseHandle(fileMapping);
    UnmapViewOfFile(mappedFileMem);
    HeapFree(heap, 0, heapMem);
    CoTaskMemFree(coTaskMem);


    return 0;
}
