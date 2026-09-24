# Programming Assignment 3 - Colossus Airlines

## What This Assignment Was About

For this assignment, I made a seating reservation program for Colossus Airlines. The airline has 128 seats and 4 flights total, with 2 inbound and 2 outbound flights.

The main idea was to make a program where someone could choose a flight and manage the seats for that flight.

## How I Made It

I used a `struct` to keep track of each seat. Each seat has a seat number, whether it is assigned or not, and the customer's first and last name.

I also used arrays for the flights and the seats. The program has 3 different menus, so you first choose if you want an inbound or outbound flight, then choose the flight number, and then choose what you want to do with the seats.

You can check how many seats are empty, see which seat numbers are available, assign a customer, delete a reservation, or see the assigned customers in alphabetical order.

One thing I found interesting was getting the alphabetical list to work. I had to make a separate list of the assigned seats and then compare the last names to put them in order. I also liked seeing how the seat information stayed saved while I moved between the different menus.

I also added a cancel option for assigning and deleting seats so the user can back out without finishing the action.

## Pros

* keeps track of all 128 seats
* works with all 4 flights
* lets you assign customers to seats
* lets you delete reservations
* shows the available seats
* shows customers alphabetically
* has a cancel option

## Cons

* reservations reset when the program closes
* names with spaces aren't supported
* each flight only has the 128 seats needed for this assignment

## Screenshots

The screenshots showing my program running are included in this folder.

* Main menu
* Number of empty seats
* List of empty seats
* Customer assigned to a seat
* Alphabetical list
* Deleted reservation

## What I Learned

This assignment helped me understand `structs` and arrays a lot better. I also got more comfortable using functions, loops, and `switch` statements to build menus in C.

I think the part I found most interesting was seeing how all of these smaller pieces worked together to make an actual working reservation program.
