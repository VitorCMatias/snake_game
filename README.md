# Snake Game in C++

## Table of Contents
* [Introduction](#Introduction)
* [Libraries](#Libraries)
* [Colours](#Colours)
* [Compilation](#Compilation)
* [Observations](#Observations)

## Introduction
This project is a version of the classical snake game arcade that I developed to practice, and improve, my skills in  POO, data structures, file manipulation, C++, and its STL.

I've also used the Singleton design pattern, to have only a single instance of a class. And some native Windows features, to change text and console colours or some DOS commands. 

Here we have an image of the game running:

<p align="center">
   <img width="460" height="300" src= "https://github.com/VitorCMatias/snake_game/blob/readme_images/Screenshots/game%20play.png?raw=true">
</p>



## Libraries
- STL
- [Conio.h](https://bit.ly/2yTfPUe)

## Colours
To print coloured chars and change the background colour, I used the [ANSI escape code](https://bit.ly/3euJ1R5) I preferred to do such implementation to use a native function of Windows and C++, instead of import a external library,  making the final program a bit shorter.

 Moreover, its colour range fitted to the necessity of my project, and the scape code was an easy tool, the only thing I had to do was print my code in this format:


 
```cpp
cout << COLOUR_CODE << "Text" << RESET_COLOR_SCHEME;
```


## Compilation
If you wish to compile the code and run it on your computer, you need to use the following terminal command:
> g++ -std=c++17 -O2 Header.hpp Source.cpp Snake.cpp Main.cpp -o snake_game

## Observations
* This code uses the library ```<Windows.h>```, that only works on Windows platform.




