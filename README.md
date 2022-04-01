# Shell
This is a shell creating project in C language


## Introduction :

We recreated some of the basic commands in the shell to suit our own needs: </br>
`` DIR `` </br>
`` COPY 'SRC' 'DST'`` </br>
`` pwd `` </br>
`` DELETE 'FILE-LOCAION/NAME'`` </br>
`` ECHO 'SAYSOMETHING `` </br>
Adding to that, every other command you wish to enter will be supported by the system.
>
`` TCP PORT `` - this command only works when the ``./Server`` is running and is transfering the shell to function as a client and the Server as the new stdout. </br>
Every command you will enter in the Shell program, its output will be shown in the Server terminal. ( we used dup2 in order to make this work ) </br>
`` LOCAL `` - After running the command ``TCP PORT`` in order to return to the normal mode, enter this command. </br>


## How To Run:

- Clone the projet to a linux environment. </br>
- Open a terminal and navigate into the corresponding folder ``Shell``. </br>
- run the command ``make all`` in the terminal in order to create the Shell and the Server. </br>
- in two seperate terminals write the following (in order to run the program) : </br>
- 1. ``./Shell`` </br>
- 2. ``./Server`` </br>

We're adding a photo to explain in details : </br>
<img width="1402" alt="Screen Shot 2022-04-01 at 10 15 16" src="https://user-images.githubusercontent.com/73894107/161214410-a5ed4567-c82c-4e5b-ab07-c80fa41c2b0f.png">

## Reading Material:

- [Dup2](https://man7.org/linux/man-pages/man2/dup.2.html)
- [Basic Shell Commands](https://www.geeksforgeeks.org/basic-shell-commands-in-linux/)
- [Fork](https://man7.org/linux/man-pages/man2/fork.2.html)
