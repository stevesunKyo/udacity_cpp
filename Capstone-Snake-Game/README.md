# CPPND: Capstone Snake Game

This project is the capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
This project is based on the starter code from the udacity starter repo, a triditional snake game.
<img src="snake_game.gif"/>

## New Features

(1) one food were regularly generated each second, until the food on the board reach the maximum food number(initial value is 30).
   Five foods will be generated when there are no foods on the board. 
(2) instead of 1 snake in the ordinary game, there are 1 player snake and 1 AI snakes chasing for food automatically by using A* search algorithm.
(3) AI snake will choose a food as target randomly. After target food was eaten, AI will choose another target.


## Rubic Points addressed 
1. The project demonstrates an understanding of C++ functions and control structures.
2. The project reads data from a file and process the data, or the program writes data to a file. the player can type his or her name at the beginning, and a txt file will be created to record the player score.(and scores of AI, of course)
3. The project uses Object Oriented Programming techniques. all functions were created in classes.
4. Classes abstract implementation details from their interfaces. There are comments to describe functions of class member functions.
5. Classes use appropriate access specifiers for class members.
6. The project makes use of references in function declarations. the function "void Renderer::Render" in renderer.cpp and Asearch::expand in "snake.cpp" use pass-by-reference.



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







