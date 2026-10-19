#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main(void) {
    // Get the current user's ID
    uid_t user_id = geteuid();

    // Find the username connected to the ID
    struct passwd *user = getpwuid(user_id);

    // Check if the username was found
    if (user == NULL) {
        fprintf(stderr, "Error: Could not find username.\n");
        return 1;
    }

    // Display the modified output
    printf("You are: %s\n", user->pw_name);

    return 0;
}
