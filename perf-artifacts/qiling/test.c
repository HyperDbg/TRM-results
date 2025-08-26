#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Open the file (create or replace if exists)
    int file = open("Test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Check if the file is opened successfully
    if (file < 0) {
        perror("Error opening file");
        return 1; // Error, couldn't open the file
    }

    // Buffer to hold the line string
    char buffer[20];

    // Write 1000 lines in a loop
    for (int i = 1; i <= 1000; ++i) {
        // Format the string "i\n" into the buffer
        int len = snprintf(buffer, sizeof(buffer), "%d\n", i);

        // Write the string to the file
        if (write(file, buffer, len) < 0) {
            perror("Error writing to file");
            close(file);
            return 1; // Error, couldn't write to the file
        }
    }

    // Close the file descriptor
    close(file);

    return 0;
}

