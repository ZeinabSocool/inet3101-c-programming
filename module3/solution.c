#include <stdio.h>
#include <string.h>

#define NUM_FLIGHTS 4
#define NUM_SEATS 128

struct Seat
{
    int seat_id;
    int assigned;
    char last_name[50];
    char first_name[50];
};

int flight_numbers[NUM_FLIGHTS] = {101, 102, 201, 202};

struct Seat seats[NUM_FLIGHTS][NUM_SEATS];


/* Set all seats to unassigned */
void initialize_seats()
{
    int i;
    int j;

    for (i = 0; i < NUM_FLIGHTS; i++)
    {
        for (j = 0; j < NUM_SEATS; j++)
        {
            seats[i][j].seat_id = j + 1;
            seats[i][j].assigned = 0;
            seats[i][j].first_name[0] = '\0';
            seats[i][j].last_name[0] = '\0';
        }
    }
}


/* Find the flight number */
int find_flight(int number)
{
    int i;

    for (i = 0; i < NUM_FLIGHTS; i++)
    {
        if (flight_numbers[i] == number)
        {
            return i;
        }
    }

    return -1;
}


/* Show number of empty seats */
void show_empty_seats_number(int flight)
{
    int i;
    int empty = 0;

    for (i = 0; i < NUM_SEATS; i++)
    {
        if (seats[flight][i].assigned == 0)
        {
            empty++;
        }
    }

    printf("\nThere are %d empty seats.\n", empty);
}


/* Show list of empty seats */
void show_empty_seats(int flight)
{
    int i;

    printf("\nEmpty seats:\n");

    for (i = 0; i < NUM_SEATS; i++)
    {
        if (seats[flight][i].assigned == 0)
        {
            printf("%d ", seats[flight][i].seat_id);
        }
    }

    printf("\n");
}


/* Assign a customer to a seat */
void assign_customer(int flight)
{
    int seat;
    char first[50];
    char last[50];

    printf("\nEnter seat number (1-128, or 0 to cancel): ");
    scanf("%d", &seat);

    if (seat == 0)
    {
        printf("Assignment cancelled.\n");
        return;
    }

    if (seat < 1 || seat > 128)
    {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[flight][seat - 1].assigned == 1)
    {
        printf("That seat is already assigned.\n");
        return;
    }

    printf("Enter first name (or CANCEL): ");
    scanf("%49s", first);

    if (strcmp(first, "CANCEL") == 0)
    {
        printf("Assignment cancelled.\n");
        return;
    }

    printf("Enter last name (or CANCEL): ");
    scanf("%49s", last);

    if (strcmp(last, "CANCEL") == 0)
    {
        printf("Assignment cancelled.\n");
        return;
    }

    strcpy(seats[flight][seat - 1].first_name, first);
    strcpy(seats[flight][seat - 1].last_name, last);

    seats[flight][seat - 1].assigned = 1;

    printf("Customer assigned to seat %d.\n", seat);
}


/* Delete a seat assignment */
void delete_assignment(int flight)
{
    int seat;

    printf("\nEnter seat number (1-128, or 0 to cancel): ");
    scanf("%d", &seat);

    if (seat == 0)
    {
        printf("Delete cancelled.\n");
        return;
    }

    if (seat < 1 || seat > 128)
    {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[flight][seat - 1].assigned == 0)
    {
        printf("That seat is already empty.\n");
        return;
    }

    seats[flight][seat - 1].assigned = 0;
    seats[flight][seat - 1].first_name[0] = '\0';
    seats[flight][seat - 1].last_name[0] = '\0';

    printf("Seat assignment deleted.\n");
}


/* Show assigned seats alphabetically by last name */
void alphabetical_list(int flight)
{
    int i;
    int j;
    int count = 0;

    struct Seat list[NUM_SEATS];
    struct Seat temp;

    /* Put assigned seats into a separate list */
    for (i = 0; i < NUM_SEATS; i++)
    {
        if (seats[flight][i].assigned == 1)
        {
            list[count] = seats[flight][i];
            count++;
        }
    }

    if (count == 0)
    {
        printf("\nThere are no assigned seats.\n");
        return;
    }

    /* Sort the list by last name */
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(list[i].last_name, list[j].last_name) > 0)
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    printf("\nAlphabetical list of seats:\n");

    for (i = 0; i < count; i++)
    {
        printf("Seat %d - %s %s\n",
               list[i].seat_id,
               list[i].first_name,
               list[i].last_name);
    }
}


/* Third level menu */
void third_menu(int flight)
{
    char choice;

    do
    {
        printf("\n===== THIRD LEVEL MENU =====\n");
        printf("a. Show number of empty seats\n");
        printf("b. Show list of empty seats\n");
        printf("c. Show alphabetical list of seats\n");
        printf("d. Assign a customer to a seat assignment\n");
        printf("e. Delete a seat assignment\n");
        printf("f. Return to Main menu\n");
        printf("Enter your choice: ");

        scanf(" %c", &choice);

        switch (choice)
        {
            case 'a':
                show_empty_seats_number(flight);
                break;

            case 'b':
                show_empty_seats(flight);
                break;

            case 'c':
                alphabetical_list(flight);
                break;

            case 'd':
                assign_customer(flight);
                break;

            case 'e':
                delete_assignment(flight);
                break;

            case 'f':
                printf("Returning to Main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 'f');
}


/* Second level menu */
void second_menu(int first_flight, int last_flight)
{
    char choice;
    int number;
    int flight;

    do
    {
        printf("\n===== SECOND LEVEL MENU =====\n");
        printf("a. Flight Number\n");
        printf("b. Back to Main\n");
        printf("Enter your choice: ");

        scanf(" %c", &choice);

        if (choice == 'a')
        {
            printf("\nAvailable flight numbers: ");

            for (int i = first_flight; i <= last_flight; i++)
            {
                printf("%d ", flight_numbers[i]);
            }

            printf("\nEnter flight number: ");
            scanf("%d", &number);

            flight = find_flight(number);

            if (flight >= first_flight && flight <= last_flight)
            {
                third_menu(flight);
            }
            else
            {
                printf("Invalid flight number.\n");
            }
        }
        else if (choice != 'b')
        {
            printf("Invalid choice.\n");
        }

    } while (choice != 'b');
}


/* Main function */
int main()
{
    char choice;

    initialize_seats();

    do
    {
        printf("\n===== COLOSSUS AIRLINES =====\n");
        printf("a. Outbound Flight\n");
        printf("b. Inbound Flight\n");
        printf("c. Quit\n");
        printf("Enter your choice: ");

        scanf(" %c", &choice);

        if (choice == 'a')
        {
            /* Flights 101 and 102 are outbound */
            second_menu(0, 1);
        }
        else if (choice == 'b')
        {
            /* Flights 201 and 202 are inbound */
            second_menu(2, 3);
        }
        else if (choice == 'c')
        {
            printf("Program ended.\n");
        }
        else
        {
            printf("Invalid choice.\n");
        }

    } while (choice != 'c');

    return 0;
}