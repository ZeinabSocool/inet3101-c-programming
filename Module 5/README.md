Programming Assignment 5 

Problem Statement
For this assignment, I had to make a client and server using C. The main goal was to understand how networking works and how two programs can communicate with each other. Basically, the client asks the server for a file, and the server sends back what's inside it. The file can't be more than 2048 characters, and I also had to make sure the program could handle errors, like when a file doesn't exist, the name is wrong, or the file is too big.

Describe the Solution
For my solution, I created two files called server.c and client.c. The server basically waits for the client to connect and ask for a file. Once it gets the filename, it checks if the file is there and if it's not too big. If everything looks good, it sends the file back to the client. If there's an issue, it sends an error message instead.

For the client, I made it so the user can type in the name of the file they want. It sends that name to the server and waits for a response. Once it gets something back, it prints it out so the user can see it. I also added error messages because I wanted the program to actually tell the user what's wrong instead of just not working.

I tried to keep everything simple and easy to follow because I didn't want to overcomplicate the assignment. I also included a sample text file to help test if everything was working the way it should.

Pros and Cons of My Solution

Pros:
- My code is pretty simple and easy to follow.
- It does what it's supposed to do without being too complicated.
- It tells the user when something goes wrong instead of just stopping.
- The server can stay running and accept another request.
- It's a good way to understand how a client and server work together.
Cons:
- It only works with small text files.
- -Both programs are set up to run on the same computer.
- The server can only work with one client at a time.
It doesn't have extra security features.

Conclusion
Overall, I feel like this assignment gave me a better idea of how networking works in C. I knew that clients and servers communicated with each other, but actually seeing how that works through code helped me understand it more. I kept my solution pretty basic, but I think that's what made it easier for me to follow. I also got to practice working with files and handling errors, which was helpful because those are things I know I'll probably use again in other programming assignments.

