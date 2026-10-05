# Programming Assignment 4 - Colossus Airlines

## Problem Statement

The Colossus Airlines program lets users assign and delete seats for different flights. Before this assignment, the reservations would disappear whenever the program was closed.

The goal was to make the reservations save so they would still be there when the program was opened again.

## Describe the Solution

I updated the program to save the reservation information to a file called reservations.dat.

Now, when a customer is assigned to a seat or a reservation is deleted, the information is saved. When the program starts again, it loads the saved reservations.

I tested this by assigning Zeinab Hassan to seat 10 on flight 101, closing the program, and opening it again. The reservation was still there.

## Pros and Cons of My Solution

### Pros

- Reservations don't disappear when the program closes.
- Saved reservations load when the program starts.
- The original menu still works.
- It's pretty simple to use.

### Cons

- The file is only saved locally.
- If the file gets deleted, the reservations are gone.
- It's made specifically for this airline program.

## Screenshots

The screenshots are attached separately below.

- Screenshot 1 shows the customer being assigned to seat 10.
- Screenshot 2 shows the reservation still there after restarting the program.

## Important Notes

The reservation data is saved in reservations.dat.

The program loads the file when it starts and saves changes when a reservation is added or deleted.

I kept the original Module 3 version unchanged and made the changes in Module 4.






