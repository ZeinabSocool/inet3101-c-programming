#include <stdio.h>
#include "calendar.h"

int main(void) {
    int choice;

    // Keep showing the menu until the user wants to exit.
    while (1) {
        printf("\n===== MY CALENDAR MANAGER =====\n");
        printf("1. Add an event\n");
        printf("2. View all events\n");
        printf("3. Search for an event\n");
        printf("4. Update an event\n");
        printf("5. Delete an event\n");
        printf("6. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please enter a valid number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            continue;
        }

        // Clear the leftover newline before reading text.
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        switch (choice) {
            case 1:
                add_event();
                break;

            case 2:
                view_events();
                break;

            case 3:
                search_event();
                break;

            case 4:
                update_event();
                break;

            case 5:
                delete_event();
                break;

            case 6:
                printf("Thanks for using my calendar!\n");
                return 0;

            default:
                printf("Please choose a number from 1 to 6.\n");
        }
    }
}
