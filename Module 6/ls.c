#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Display files in long format automatically
    int result = system("ls -l");

    // Check if the command worked
    if (result == -1) {
        printf("Error: Could not list files.\n");
        return 1;
    }

    return 0;
}

