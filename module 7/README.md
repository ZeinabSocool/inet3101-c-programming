INET 3101 Capstone Project

Calendar Management System

Problem Statement

For my capstone project, I decided to create a Calendar Management System using C. I chose this because keeping track of events, appointments, and deadlines can get overwhelming. I wanted to make something simple that helps people stay organized. My program allows users to add, view, search, update, and delete events.

Design and Architecture Details

I used C and the gdbm database library to build my program and save events. I separated my code into different files to make everything easier to manage.
- main.c: Displays the menu and lets users choose what they want to do.
- calendar.c: Handles adding, viewing, updating, searching, and deleting events.
- calendar.h: Stores the event structure and function declarations.
- Makefile: Helps compile and run my program.

Each event has an ID, title, date, and time. I also added a feature that checks if two events are scheduled for the exact same time. The program checks that dates and times are entered correctly.

Pros and Cons of My Solution

Pros

One thing I like about my program is that it's pretty straightforward. Users can easily navigate the menu without needing any technical experience. I also like that events stay saved even after closing the program, so you don't have to start over every time.

Cons

One thing I would improve is the design because right now everything runs through the terminal. I also wish I could add reminders and recurring events. The program only checks for events starting at the same time, so it doesn't catch every scheduling conflict. If I had more time, I would definitely add these features to make the calendar more useful.
