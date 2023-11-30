#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// Define a structure to store user information
struct UserInfo {
    char name[50];
    char family[50];
    int age;
    char address[100];
    char email[50];
};

int main() {
    int numberOfPersons = 5;

    // Allocate memory for an array of structures using malloc
    struct UserInfo* users = (struct UserInfo*)malloc(numberOfPersons * sizeof(struct UserInfo));

    // Check if memory allocation was successful
    if (users == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1; // Return an error code
    }

	memset(users, 0, numberOfPersons * sizeof(struct UserInfo));
    
    printf("address of the target buffer: %llx | size : %x\n", users, numberOfPersons * sizeof(struct UserInfo));

    Sleep(10000);

    // DebugBreak();

    // Get user information for each person
    int i = 0;
    for (i = 0; i < numberOfPersons; ++i) {
        printf("\nEnter information for person %d:\n", i + 1);

        printf("Enter name: ");
        scanf("%s", users[i].name);

        printf("Enter family: ");
        scanf("%s", users[i].family);

        printf("Enter age: ");
        scanf("%d", &users[i].age);

        printf("Enter address: ");
        scanf("%s", users[i].address);

        printf("Enter email: ");
        scanf("%s", users[i].email);
    }

    // Display the entered information for each person
    printf("\nUser Information for %d Persons:\n", numberOfPersons);
    for (i = 0; i < numberOfPersons; ++i) {
        printf("\nPerson %d:\n", i + 1);
        printf("Name: %s\n", users[i].name);
        printf("Family: %s\n", users[i].family);
        printf("Age: %d\n", users[i].age);
        printf("Address: %s\n", users[i].address);
        printf("Email: %s\n", users[i].email);
    }

    // Free the allocated memory
    free(users);

    return 0; // Return success
}

