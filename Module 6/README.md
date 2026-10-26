Programming Assignment 6 

1. Problem Statement
For this assignment, I had to work with two commands, ls and whoami, using C. The goal was to change how they normally show information. For ls, I needed it to show all the file details automatically instead of having to type ls -l every time. For whoami, I had to make it say "You are:" before showing the username. Basically, this assignment was about learning how terminal commands work and how we can change what they do using C.

2. Describe the Solution
For the first part, I made my ls.c program run the ls -l command automatically. This way, it shows the file permissions, sizes, owners, and dates without me having to type the extra -l. I kept it pretty simple because I just wanted the program to show the correct information without making things more complicated.
For the second part, I worked on whoami.c. I used C to get the current username from the system and changed the output so it says "You are:" before the username. This part was pretty straightforward, and I didn't have to change too much to get the result I wanted.
After finishing both programs, I compiled them using clang on my Mac and tested everything in Terminal. Both programs worked and gave me the output I was looking for. I also took screenshots to show that they were running correctly.

3. Pros and Cons of My Solution
Pros:
- I liked that the code was pretty simple and easy to understand.
- The ls program automatically shows more information, so I don't have to type the extra command every time.
- The whoami program makes the output a little more clear instead of only showing a username.
- I got more comfortable writing C code and actually testing it in Terminal.
Cons:
- Sometimes I just want to see the file names, so having all that extra information can be a little unnecessary.
- My ls program still depends on the computer's existing ls command to work.
- Every time I make changes to my code, I have to compile it again before testing.
- The changes were pretty basic, so they didn't really add a whole lot of new features.

4. How to Compile and Run
I used VS Code to write my code and Terminal on my Mac to compile and run everything.
First, I opened Terminal and went to my Module 6 folder.
cd ~/Desktop/inet3101/"Module 6"
Then I compiled both programs using these commands:
clang ls.c -o myls
clang whoami.c -o mywhoami
After compiling, I ran both programs:
./myls
./mywhoami
The first program shows a detailed list of files, and the second program displays "You are:" followed by the current username.

5. Testing
After compiling both programs, I tested them in Terminal to make sure everything was working. When I ran my ls program, it showed the long file listing with all the extra details like permissions, file sizes, owners, and dates.
When I ran my whoami program, it displayed "You are: zeinabhassan", which was exactly what I wanted. I took screenshots of both outputs as proof that the programs worked.

6. Conclusion
Overall, I think this assignment helped me get a better understanding of how C works with operating system commands. I've used ls and whoami before, but I never really thought about how they worked or how the output could be changed. It was interesting seeing how I could make my own versions of these commands and get them to display what I wanted. I also got more practice using Terminal, compiling my code, and figuring things out as I went.
