#ifndef CALENDAR_H
#define CALENDAR_H

// This stores the information for each calendar event.
typedef struct {
    int id;
    char title[100];
    char date[11];
    char time[6];
} Event;

// These are the main functions used in my calendar.
void add_event(void);
void view_events(void);
void search_event(void);
void update_event(void);
void delete_event(void);

#endif
