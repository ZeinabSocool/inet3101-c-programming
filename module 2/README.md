# Problem Statement

For this assignment, I had to create a C program that takes a decimal number and changes it into another base from 2 to 16. The tricky part was using the symbols `! @ # $ % ^` instead of letters for the higher values.

# Describe the Solution

I made a `to_base_n()` function that uses division and the remainder to figure out each digit. I put the remainders into an array and then printed them backwards. I also added the required `0` for octal and `0x` for hexadecimal.

# Pros and Cons of My Solution

One thing I like about my solution is that one function can handle multiple bases instead of just binary. It also checks for invalid bases. One limitation is that I focused on positive whole numbers, so negative numbers are not handled.
