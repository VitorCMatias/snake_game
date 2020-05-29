# Snake Game in C++



This project is a version of the classical snake game arcade that I developed to practice, and improve, my skills in  POO, 
data structures, file manipulation, C++, and its STL.

I've also used the Singleton design pattern, to have only a single instance of a class. 



## Libraries
- STL
- [Conio.h](https://bit.ly/2yTfPUe)
## Colours
To print coloured chars and change the background colour, I used the [ANSI escape code](https://bit.ly/3euJ1R5). I preferred to do such implementation to use a native function of Windows and C++, instead of import a external library.

## Compilation
If you wish to compile the code and run it on your computer, you need to use the following terminal command:
> g++ -std=c++17 -O2 head.h Source.cpp Snake.cpp Main.cpp -o snake_game

**Observations**
* This code uses the library ```<Windows.h>```, that only works on Windows platform.




