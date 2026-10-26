#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gdbm.h>
#include "calendar.h"

#define DATABASE "calendar.db"

// This helps me get text from the user without extra spaces or newlines.
static void get_text(const char *message, char *text, int size) {
    printf("%s", message);

    if (fgets(text, size, stdin) == NULL) {
        text[0] = '\0';
        return;
    }

    int length = (int)strlen(text);

    if (length > 0 && text[length - 1] == '\n') {
        text[length - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
}

// This makes sure the user enters a number.
static int get_number(const char *message) {
    char input[40];
    int number;
    char extra;

    get_text(message, input, sizeof(input));

    if (sscanf(input, "%d %c", &number, &extra) != 1) {
        return -1;
    }

    return number;
}

// I use this to open the database whenever I need it.
static GDBM_FILE open_database(void) {
    GDBM_FILE db = gdbm_open(
        DATABASE, 0, GDBM_WRCREAT, 0644, NULL
    );

    if (db == NULL) {
        printf("Sorry, the database could not be opened.\n");
    }

    return db;
}

// Every event has its own ID, which is used as the database key.
static datum make_key(int *id) {
    datum key;
    key.dptr = (char *)id;
    key.dsize = sizeof(*id);
    return key;
}

// This finds an event using its ID.
static int find_event(GDBM_FILE db, int id, Event *event) {
    datum key = make_key(&id);
    datum data = gdbm_fetch(db, key);

    if (data.dptr == NULL) {
        return 0;
    }

    if (data.dsize != sizeof(Event)) {
        free(data.dptr);
        return 0;
    }

    memcpy(event, data.dptr, sizeof(Event));
    free(data.dptr);

    return 1;
}

// This saves an event or replaces one that was updated.
static int save_event(GDBM_FILE db, Event *event) {
    datum key = make_key(&event->id);
    datum data;

    data.dptr = (char *)event;
    data.dsize = sizeof(Event);

    return gdbm_store(db, key, data, GDBM_REPLACE) == 0;
}

// This gives each new event a unique number.
static int next_id(GDBM_FILE db) {
    int highest = 0;
    datum key = gdbm_firstkey(db);

    while (key.dptr != NULL) {
        datum next = gdbm_nextkey(db, key);

        if (key.dsize == sizeof(int)) {
            int id;
            memcpy(&id, key.dptr, sizeof(int));

            if (id > highest) {
                highest = id;
            }
        }

        free(key.dptr);
        key = next;
    }

    return highest + 1;
}

// Check the date format before saving an event.
static int valid_date(const char *date) {
    if (strlen(date) != 10) {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else if (!isdigit((unsigned char)date[i])) {
            return 0;
        }
    }

    int year, month, day;
    sscanf(date, "%d-%d-%d", &year, &month, &day);

    if (year < 1 || month < 1 || month > 12) {
        return 0;
    }

    int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    // February has an extra day during leap years.
    if (year % 400 == 0 ||
        (year % 4 == 0 && year % 100 != 0)) {
        days[1] = 29;
    }

    return day >= 1 && day <= days[month - 1];
}

// Check that the time is in 24-hour format.
static int valid_time(const char *time) {
    if (strlen(time) != 5 || time[2] != ':') {
        return 0;
    }

    for (int i = 0; i < 5; i++) {
        if (i != 2 && !isdigit((unsigned char)time[i])) {
            return 0;
        }
    }

    int hour, minute;
    sscanf(time, "%d:%d", &hour, &minute);

    return hour >= 0 && hour <= 23 &&
           minute >= 0 && minute <= 59;
}

// This checks if another event already has the same date and time.
static int has_conflict(GDBM_FILE db, Event *event, int skip_id) {
    datum key = gdbm_firstkey(db);

    while (key.dptr != NULL) {
        datum next = gdbm_nextkey(db, key);
        datum data = gdbm_fetch(db, key);

        if (data.dptr != NULL && data.dsize == sizeof(Event)) {
            Event saved;
            memcpy(&saved, data.dptr, sizeof(Event));

            if (saved.id != skip_id &&
                strcmp(saved.date, event->date) == 0 &&
                strcmp(saved.time, event->time) == 0) {

                free(data.dptr);
                free(key.dptr);
                free(next.dptr);
                return 1;
            }
        }

        free(data.dptr);
        free(key.dptr);
        key = next;
    }

    return 0;
}

// Make sure the event has a title, valid date, and valid time.
static int valid_event(Event *event) {
    if (strlen(event->title) == 0) {
        printf("The event needs a title.\n");
        return 0;
    }

    if (!valid_date(event->date)) {
        printf("Invalid date. Use YYYY-MM-DD.\n");
        return 0;
    }

    if (!valid_time(event->time)) {
        printf("Invalid time. Use HH:MM (24-hour format).\n");
        return 0;
    }

    return 1;
}

// CREATE: Add a new event to my calendar.
void add_event(void) {
    GDBM_FILE db = open_database();
    if (db == NULL) return;

    Event event = {0};
    event.id = next_id(db);

    printf("\n===== ADD EVENT =====\n");

    get_text("Event title: ", event.title, sizeof(event.title));
    get_text("Date (YYYY-MM-DD): ", event.date, sizeof(event.date));
    get_text("Time (HH:MM): ", event.time, sizeof(event.time));

    if (!valid_event(&event)) {
        gdbm_close(db);
        return;
    }

    if (has_conflict(db, &event, -1)) {
        printf("You already have an event at this time.\n");
        gdbm_close(db);
        return;
    }

    if (save_event(db, &event)) {
        printf("Event added successfully! Event ID: %d\n", event.id);
    } else {
        printf("Something went wrong while saving.\n");
    }

    gdbm_close(db);
}

// READ: Show all the events saved in my calendar.
void view_events(void) {
    GDBM_FILE db = open_database();
    if (db == NULL) return;

    printf("\n===== MY EVENTS =====\n");

    datum key = gdbm_firstkey(db);
    int count = 0;

    while (key.dptr != NULL) {
        datum next = gdbm_nextkey(db, key);
        datum data = gdbm_fetch(db, key);

        if (data.dptr != NULL && data.dsize == sizeof(Event)) {
            Event event;
            memcpy(&event, data.dptr, sizeof(Event));

            printf("\nEvent ID: %d\n", event.id);
            printf("Title: %s\n", event.title);
            printf("Date: %s\n", event.date);
            printf("Time: %s\n", event.time);
            printf("--------------------------\n");

            count++;
        }

        free(data.dptr);
        free(key.dptr);
        key = next;
    }

    if (count == 0) {
        printf("You don't have any events yet.\n");
    } else {
        printf("Total events: %d\n", count);
    }

    gdbm_close(db);
}

// READ: Search for a specific event.
void search_event(void) {
    GDBM_FILE db = open_database();
    if (db == NULL) return;

    printf("\n===== SEARCH EVENT =====\n");

    int id = get_number("Enter event ID: ");
    Event event;

    if (find_event(db, id, &event)) {
        printf("\nEvent found!\n");
        printf("ID: %d\n", event.id);
        printf("Title: %s\n", event.title);
        printf("Date: %s\n", event.date);
        printf("Time: %s\n", event.time);
    } else {
        printf("I couldn't find an event with that ID.\n");
    }

    gdbm_close(db);
}

// UPDATE: Change the details of an existing event.
void update_event(void) {
    GDBM_FILE db = open_database();
    if (db == NULL) return;

    printf("\n===== UPDATE EVENT =====\n");

    int id = get_number("Enter event ID to update: ");
    Event event;

    if (!find_event(db, id, &event)) {
        printf("Event not found.\n");
        gdbm_close(db);
        return;
    }

    printf("Currently updating: %s\n", event.title);

    get_text("New title: ", event.title, sizeof(event.title));
    get_text("New date (YYYY-MM-DD): ", event.date, sizeof(event.date));
    get_text("New time (HH:MM): ", event.time, sizeof(event.time));

    if (!valid_event(&event)) {
        printf("Update cancelled. Original event was not changed.\n");
        gdbm_close(db);
        return;
    }

    if (has_conflict(db, &event, id)) {
        printf("That time is already booked. Update cancelled.\n");
        gdbm_close(db);
        return;
    }

    if (save_event(db, &event)) {
        printf("Event updated successfully!\n");
    } else {
        printf("Could not update the event.\n");
    }

    gdbm_close(db);
}

// DELETE: Remove an event from my calendar.
void delete_event(void) {
    GDBM_FILE db = open_database();
    if (db == NULL) return;

    printf("\n===== DELETE EVENT =====\n");

    int id = get_number("Enter event ID to delete: ");
    Event event;

    if (!find_event(db, id, &event)) {
        printf("Event not found.\n");
        gdbm_close(db);
        return;
    }

    printf("Deleting event: %s\n", event.title);

    datum key = make_key(&id);

    if (gdbm_delete(db, key) == 0) {
        printf("Event deleted successfully!\n");
    } else {
        printf("Could not delete the event.\n");
    }

    gdbm_close(db);
}
