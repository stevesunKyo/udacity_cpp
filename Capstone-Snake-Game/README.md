# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## New Features

(1) one food were regularly generated each second, until the food on the board reach the maximum food number(initial value is 10).
(2) there are two special foods on the playground. 
   one green food that will get 5 points instead of one points in normal food. However, it will set the speed of snake to half.
   one green food that will have 50% probability to double the score and greatly increase the speed of snake,
   50% probability to half the score and half the speed.
   special foods are not restricted by amount of normal food, and special food will be generated automatically after being eated. 
(3) Player can input his or her name in the console before start the game.
(4) name of player will be recorded in record.txt after the game terminate.

## Rubic Points addressed 
1. The project demonstrates an understanding of C++ functions and control structures.
  The project code is clearly organized into functions.
2. The project accepts user input and processes the input. Player was required to input their name before entering the game.
3. The program writes data to a file. the player can type his or her name at the beginning, and a txt file will be created to record the player score.
4. The project uses Object Oriented Programming techniques. all functions were created in classes.
5. Classes abstract implementation details from their interfaces. All class member functions document their effects, either through function names, comments, or formal documentation. 
6. Classes use appropriate access specifiers for class members. All class data members are explicitly specified as public, protected, or private.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
