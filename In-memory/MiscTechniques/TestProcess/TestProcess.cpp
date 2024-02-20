#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile;
    DWORD dwBytesWritten;
    const char* data = "Hello TRM!";
    const char* filename = "c:\\users\\sina\\desktop\\test-process.txt";

    // Create the file
    hFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to create file. Error code: %d\n", GetLastError());
        return 1;
    }

    // Write to the file
    if (!WriteFile(hFile, data, strlen(data), &dwBytesWritten, NULL)) {
        printf("Failed to write to file. Error code: %d\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }

    // Close the file handle
    CloseHandle(hFile);

    printf("Data written to file successfully!\n");
    return 0;
}
